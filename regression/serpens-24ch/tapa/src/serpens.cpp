#include <ap_int.h>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <tapa.h>

#include "serpens.h"

//#include <iostream>
//using namespace std;

constexpr int FIFO_DEPTH = 2;

const int NUM_CH_SPARSE_div_8 = NUM_CH_SPARSE / 8;
const int NUM_CH_SPARSE_mult_16 = NUM_CH_SPARSE * 16;
const int NUM_CH_SPARSE_mult_2 = NUM_CH_SPARSE * 2;
const int WINDOW_SIZE_div_16 = WINDOW_SIZE >> 4;

using float_v8 = tapa::vec_t<float, 8>;
using float_v2 = tapa::vec_t<float, 2>;

struct MultXVec {
    tapa::vec_t<ap_uint<18>, 8> row;
    float_v8 axv;
};

template <typename T, typename R>
inline void async_read(tapa::async_mmap<T> & A,
                       tapa::ostream<T> & fifo_A,
                       const R A_len,
                       R & i_req,
                       R & i_resp) {
#pragma HLS inline
    if ((i_req < A_len) &
        !A.read_addr.full()) {
        A.read_addr.try_write(i_req);
        ++i_req;
    }
    if (!fifo_A.full() & !A.read_data.empty()) {
        T tmp;
        A.read_data.try_read(tmp);
        fifo_A.try_write(tmp);
        ++i_resp;
    }
}

void read_edge_list_ptr(const int num_ite,
                        const int M,
                        const int P_N,
                        const int K,
                        tapa::async_mmap<int> & edge_list_ptr,
                        tapa::ostream<int> & PE_inst
                        ) {
    const int rp_time = (P_N == 0)? 1 : P_N;
    
    PE_inst.write(num_ite);
    PE_inst.write(M);
    PE_inst.write(rp_time);
    PE_inst.write(K);
    
    const int num_ite_plus1 = num_ite + 1;
l_rp:
    for(int rp = 0; rp < rp_time; rp++) {
#pragma HLS loop_flatten off
#pragma HLS loop_tripcount min=1 max=16
    rd_ptr:
        for (int i_req = 0, i_resp = 0; i_resp < num_ite_plus1;) {
#pragma HLS loop_tripcount min=1 max=800
#pragma HLS pipeline II=1
            async_read(edge_list_ptr,
                       PE_inst,
                       num_ite_plus1,
                       i_req, i_resp);
        }
    }
}

void read_X(const int P_N,
            const int K,
            tapa::async_mmap<float_v16> & vec_X,
            tapa::ostream<float_v16> & fifo_X
            ) {
    const int rp_time = (P_N == 0)? 1 : P_N;
    const int num_ite_X = (K + 15) >> 4;
    
l_rp:
    for(int rp = 0; rp < rp_time; rp++) {
#pragma HLS loop_flatten off
#pragma HLS loop_tripcount min=1 max=16
    rd_X:
        for(int i_req = 0, i_resp = 0; i_resp < num_ite_X;) {
#pragma HLS loop_tripcount min=1 max=500000
#pragma HLS pipeline II=1
            async_read(vec_X,
                       fifo_X,
                       num_ite_X,
                       i_req, i_resp);
        }
    }
}

void read_A(const int P_N,
            const int A_len,
            tapa::async_mmap<ap_uint<512>> & A,
            tapa::ostream<ap_uint<512>> & fifo_A
            ) {
    const int rp_time = (P_N == 0)? 1 : P_N;
l_rp:
    for(int rp = 0; rp < rp_time; rp++) {
#pragma HLS loop_flatten off
#pragma HLS loop_tripcount min=1 max=16
    rd_A:
        for(int i_req = 0, i_resp = 0; i_resp < A_len;) {
#pragma HLS loop_tripcount min=1 max=10000
#pragma HLS pipeline II=1
            async_read(A,
                       fifo_A,
                       A_len,
                       i_req, i_resp);
        }
    }
}

void PEG_Xvec(tapa::istream<int> & fifo_inst_in,
              tapa::istream<ap_uint<512>> & fifo_A,
              tapa::istream<float_v16> & fifo_X_in,
              tapa::ostream<int> & fifo_inst_out,
              tapa::ostream<float_v16> & fifo_X_out,
              // to PEG_Yvec
              tapa::ostream<int> & fifo_inst_out_to_Yvec,
              tapa::ostream<MultXVec> & fifo_aXvec
              ) {
    const int NUM_ITE = fifo_inst_in.read();
    const int M = fifo_inst_in.read();
    const int rp_time = fifo_inst_in.read();
    const int K = fifo_inst_in.read();
    
    fifo_inst_out.write(NUM_ITE);
    fifo_inst_out.write(M);
    fifo_inst_out.write(rp_time);
    fifo_inst_out.write(K);
    
    fifo_inst_out_to_Yvec.write(NUM_ITE);
    fifo_inst_out_to_Yvec.write(M);
    fifo_inst_out_to_Yvec.write(rp_time);
    
l_rp:
    for(int rp = 0; rp < rp_time; rp++) {
#pragma HLS loop_flatten off
#pragma HLS loop_tripcount min=1 max=16
        
        float local_X[4][WINDOW_SIZE];
#pragma HLS bind_storage variable=local_X latency=2
#pragma HLS array_partition variable=local_X complete dim=1
#pragma HLS array_partition variable=local_X cyclic factor=X_PARTITION_FACTOR dim=2
        
        auto start_32 = fifo_inst_in.read();
        fifo_inst_out.write(start_32);
        fifo_inst_out_to_Yvec.write(start_32);
        
    main:
        for (int i = 0; i < NUM_ITE; ++i) {
#pragma HLS loop_tripcount min=1 max=49
            
            // fill onchip X
        read_X:
            for (int j = 0; (j < WINDOW_SIZE_div_16) & (j < ((K + 15) >> 4) - i * WINDOW_SIZE_div_16); ) {
#pragma HLS loop_tripcount min=1 max=512
#pragma HLS pipeline II = 1
                if (!fifo_X_in.empty() & !fifo_X_out.full()) {
                    float_v16 x; fifo_X_in.try_read(x);
                    fifo_X_out.try_write(x);
                    for (int kk = 0; kk < 16; ++kk) {
                        for (int l = 0; l < 4; ++l) {
                            local_X[l][(j << 4) + kk] = x[kk];
                        }
                    }
                    ++j;
                }
            }
            
            // computation
            const auto end_32 = fifo_inst_in.read();
            fifo_inst_out.write(end_32);
            fifo_inst_out_to_Yvec.write(end_32);
            
        computation:
            for (int j = start_32; j < end_32; ) {
#pragma HLS loop_tripcount min=1 max=200
#pragma HLS pipeline II=1
                if (!fifo_A.empty()) {
                    ap_uint<512> a_pes; fifo_A.try_read(a_pes);
                    MultXVec raxv;
                    
                    for (int p = 0; p < 8; ++p) {
                        ap_uint<64> a = a_pes(63 + p * 64, p * 64);
                        ap_uint<14> a_col = a(63, 50);
                        ap_uint<18> a_row = a(49, 32);
                        ap_uint<32> a_val = a(31,  0);
                        
                        raxv.row[p] = a_row;
                        if (a_row[17] == 0) {
                            float a_val_f = tapa::bit_cast<float>(a_val);
                            raxv.axv[p] = a_val_f * local_X[p/2][a_col];
                        }
                    }
                    fifo_aXvec.write(raxv);
                    ++j;
                }
            }
            start_32 = end_32;
        }
    }
}

inline void PUcore_Ymtx(ap_uint<18> addr_c,
                        float val_d0_f,
                        ap_uint<64> local_C_pe0[URAM_DEPTH]
                        ) {
#pragma HLS inline
    ap_uint<64> c_val_u64 = local_C_pe0[addr_c(17, 1)];
    
    ap_uint<32> c_val_d0_u = c_val_u64(31,  0);
    ap_uint<32> c_val_d1_u = c_val_u64(63, 32);
    
    ap_uint<32> c_val_u = (addr_c[0])? c_val_d1_u : c_val_d0_u;
    
    float c_val_plus_d0_f = tapa::bit_cast<float>(c_val_u) + val_d0_f;
    
    c_val_u = tapa::bit_cast<ap_uint<32>>(c_val_plus_d0_f);
    
    if (addr_c[0]) {
        c_val_d1_u = c_val_u;
    } else {
        c_val_d0_u = c_val_u;
    }
    
    c_val_u64(63, 32) = c_val_d1_u;
    c_val_u64(31,  0) = c_val_d0_u;
    local_C_pe0[addr_c(17, 1)] = c_val_u64;
}

void PEG_Yvec(tapa::istream<int> & fifo_inst_in,
              tapa::istream<MultXVec> & fifo_aXvec,
              tapa::ostream<float_v2> & fifo_Y_out
              ) {
    const int NUM_ITE = fifo_inst_in.read();
    const int M = fifo_inst_in.read();
    const int rp_time = fifo_inst_in.read();
    
    const int num_v_init = (M + NUM_CH_SPARSE_mult_16 - 1) / NUM_CH_SPARSE_mult_16;
    const int num_v_out = (M + NUM_CH_SPARSE_mult_2 - 1) / NUM_CH_SPARSE_mult_2;
    
    ap_uint<64> local_C[8][URAM_DEPTH];
#pragma HLS bind_storage variable=local_C type=RAM_2P impl=URAM latency=1
#pragma HLS array_partition complete variable=local_C dim=1
    
l_rp:
    for(int rp = 0; rp < rp_time; rp++) {
#pragma HLS loop_flatten off
#pragma HLS loop_tripcount min=1 max=16
        
        //init local C
    init_C:
        for (int i = 0; i < num_v_init; ++i) {
#pragma HLS loop_tripcount min=1 max=800
#pragma HLS pipeline II=1
            for (int p = 0; p < 8; ++p) {
                local_C[p][i] = 0;
            }
        }
        
        auto start_32 = fifo_inst_in.read();
        
    main:
        for (int i = 0; i < NUM_ITE; ++i) {
#pragma HLS loop_tripcount min=1 max=49
            
            // computation
            const auto end_32 = fifo_inst_in.read();
            
        computation:
            for (int j = start_32; j < end_32; ) {
#pragma HLS loop_tripcount min=1 max=200
#pragma HLS pipeline II=1
#pragma HLS dependence true variable=local_C distance=DEP_DIST_LOAD_STORE
                if (!fifo_aXvec.empty()) {
                    MultXVec raxv; fifo_aXvec.try_read(raxv);
                    for (int p = 0; p < 8; ++p) {
                        auto a_row = raxv.row[p];
                        if (a_row[17] == 0) {
                            PUcore_Ymtx(a_row,
                                        raxv.axv[p],
                                        local_C[p]);
                        }
                    }
                    ++j;
                }
            }
            start_32 = end_32;
        }
        
        //cout << "PE = " << pe_idx << endl;
    write_C_outer:
        for (int i = 0, c_idx = 0; i < num_v_out; ++i) {
#pragma HLS loop_tripcount min=1 max=1800
#pragma HLS pipeline II=1
            float_v2 out_v;
            ap_uint<64> u_64 = local_C[c_idx][i>>3];
            for (int d = 0; d < 2; ++d) {
                ap_uint<32> u_32_d = u_64(31 + 32 * d, 32 * d);
                out_v[d] = tapa::bit_cast<float>(u_32_d);
            }
            fifo_Y_out.write(out_v);
            ++c_idx;
            if (c_idx == 8) {c_idx = 0;}
        }
    }
}

void Arbiter_Y(const int P_N,
               const int M,
               tapa::istreams<float_v2, NUM_CH_SPARSE_div_8> & fifo_in,
               tapa::ostream<float_v2> & fifo_out
               ) {
    const int rp_time = (P_N == 0)? 1 : P_N;
    const int num_pe_output = ((M + NUM_CH_SPARSE_mult_2 - 1) / NUM_CH_SPARSE_mult_2) * NUM_CH_SPARSE_div_8;
    const int num_out = (M + 15) >> 4;
    const int num_ite_Y = num_pe_output * rp_time;
aby:
    for (int i = 0, c_idx = 0, o_idx = 0; i < num_ite_Y;) {
#pragma HLS loop_tripcount min=1 max=1800
#pragma HLS pipeline II=1
        if (!fifo_in[c_idx].empty() & !fifo_out.full()) {
            float_v2 tmp; fifo_in[c_idx].try_read(tmp);
            if (o_idx < num_out) {
                fifo_out.try_write(tmp);
            }
            ++i;
            c_idx++;
            o_idx++;
            if (c_idx == NUM_CH_SPARSE_div_8) {c_idx = 0;}
            if (o_idx == num_pe_output) {o_idx = 0;}
        }
    }
}

void Merger_Y(tapa::istreams<float_v2, 8> & fifo_in,
              tapa::ostream<float_v16> & fifo_out) {
    for (;;) {
#pragma HLS pipeline II=1
        bool flag_nop = fifo_out.full();
        for (int i = 0; i < 8; ++i) {
            flag_nop |= fifo_in[i].empty();
        }
        if (!flag_nop) {
            float_v16 tmpv16;
#pragma HLS aggregate variable=tmpv16
            for (int i = 0; i < 8; ++i) {
                float_v2 tmp; fifo_in[i].try_read(tmp);
                for (int d = 0; d < 2; ++d) {
                    tmpv16[i * 2 + d] = tmp[d];
                }
            }
            fifo_out.try_write(tmpv16);
        }
    }
}

void FloatvMultConst(const int P_N,
                     const int M,
                     const int alpha_u,
                     tapa::istream<float_v16> & fifo_in,
                     tapa::ostream<float_v16> & fifo_out
                     ) {
    const float alpha_f = tapa::bit_cast<float>(alpha_u);
    const int rp_time = (P_N == 0)? 1 : P_N;
    const int num_ite_Y = ((M + 15) >> 4) * rp_time;
cc:
    for (int i = 0; i < num_ite_Y;) {
#pragma HLS pipeline II=1
        float_v16 tmp;
        bool read_ready = fifo_in.try_read(tmp);
        if (read_ready) {
            float_v16 c_out = tmp * alpha_f;
            fifo_out.write(c_out);
            ++i;
        }
    }
}

void read_Y(const int P_N,
            const int M,
            tapa::async_mmap<float_v16> & Y,
            tapa::ostream<float_v16> & fifo_Y
            ) {
    const int rp_time = (P_N == 0)? 1 : P_N;
    const int num_ite_Y = (M + 15) >> 4;
    
l_rp:
    for(int rp = 0; rp < rp_time; rp++) {
#pragma HLS loop_flatten off
#pragma HLS loop_tripcount min=1 max=16
    rd_Y:
        for(int i_req = 0, i_resp = 0; i_resp < num_ite_Y;) {
#pragma HLS loop_tripcount min=1 max=500000
#pragma HLS pipeline II=1
            async_read(Y,
                       fifo_Y,
                       num_ite_Y,
                       i_req, i_resp);
        }
    }
}

void FloatvAddFloatv(tapa::istream<float_v16> & fifo_in0,
                     tapa::istream<float_v16> & fifo_in1,
                     tapa::ostream<float_v16> & fifo_out
                     ) {
cc:
    for (;;) {
#pragma HLS pipeline II=1
        bool flag_nop = fifo_in0.empty() | fifo_in1.empty();
        if (!flag_nop) {
            float_v16 tmp0; fifo_in0.try_read(tmp0);
            float_v16 tmp1; fifo_in1.try_read(tmp1);
            float_v16 c_out = tmp0 + tmp1;
            fifo_out.write(c_out);
        }
    }
}

void write_Y(const int P_N,
             const int M,
             tapa::istream<float_v16> & fifo_Y,
             tapa::async_mmap<float_v16> & Y_out
             ) {
    const int rp_time = (P_N == 0)? 1 : P_N;
    const int num_ite_Y = (M + 15) >> 4;
    
l_rp:
    for(int rp = 0; rp < rp_time; rp++) {
#pragma HLS loop_flatten off
#pragma HLS loop_tripcount min=1 max=16
    wr_C:
        for(int i_req = 0, i_resp = 0; i_resp < num_ite_Y;) {
#pragma HLS loop_tripcount min=1 max=500000
#pragma HLS pipeline II=1
            if ((i_req < num_ite_Y) &
                !fifo_Y.empty() &
                !Y_out.write_addr.full() &
                !Y_out.write_data.full() ) {
                Y_out.write_addr.try_write(i_req);
                float_v16 tmpv16;
                fifo_Y.try_read(tmpv16);
                Y_out.write_data.try_write(tmpv16);
                ++i_req;
            }
            uint8_t n_resp;
            if (Y_out.write_resp.try_read(n_resp)) {
                i_resp += int(n_resp) + 1;
            }
        }
    }
}

void black_hole_int(tapa::istream<int> & fifo_in) {
    for (;;) {
#pragma HLS pipeline II=1
        int tmp; fifo_in.try_read(tmp);
    }
}

void black_hole_float_v16(tapa::istream<float_v16> & fifo_in) {
    for (;;) {
#pragma HLS pipeline II=1
        float_v16 tmp; fifo_in.try_read(tmp);
    }
}
void Serpens(tapa::mmap<int> edge_list_ptr,
  
  tapa::mmaps<ap_uint<512>, NUM_CH_SPARSE> edge_list_ch,
  
  tapa::mmap<float_v16> vec_X,
  
  tapa::mmap<float_v16> vec_Y,
  
  tapa::mmap<float_v16> vec_Y_out,
  
  const int NUM_ITE,
  const int NUM_A_LEN,
  const int M,
  const int K,
  const int P_N,
  const int alpha_u,
  const int beta_u
  ) {
    tapa::streams<int, NUM_CH_SPARSE + 1, FIFO_DEPTH> PE_inst;
    
    tapa::streams<float_v16, NUM_CH_SPARSE + 1, FIFO_DEPTH> fifo_X_pe;
    
    tapa::streams<ap_uint<512>, NUM_CH_SPARSE, FIFO_DEPTH> fifo_A;
    
    tapa::streams<int, NUM_CH_SPARSE, FIFO_DEPTH> Yvec_inst;
    
    tapa::streams<MultXVec, NUM_CH_SPARSE, FIFO_DEPTH> fifo_aXvec;
    
    tapa::streams<float_v2, NUM_CH_SPARSE, FIFO_DEPTH> fifo_Y_pe;
    
    tapa::streams<float_v2, 8, FIFO_DEPTH> fifo_Y_pe_abd;
    
    tapa::stream<float_v16, FIFO_DEPTH> fifo_Y_AX;
    
    tapa::stream<float_v16, FIFO_DEPTH> fifo_Y_alpha_AX;
    
    tapa::stream<float_v16, FIFO_DEPTH> fifo_Y_in;
    
    tapa::stream<float_v16, FIFO_DEPTH> fifo_Y_in_beta;
    
    tapa::stream<float_v16, FIFO_DEPTH> fifo_Y_out;

    /* =========deploy modules======= */
    
    tapa::task()
        //
        .invoke(read_edge_list_ptr, NUM_ITE, M, P_N, K,edge_list_ptr,PE_inst)
    
        .invoke<tapa::join>(read_X, P_N, K, vec_X, fifo_X_pe )
    
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[0], fifo_A[0])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[1], fifo_A[1])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[2], fifo_A[2])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[3], fifo_A[3])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[4], fifo_A[4])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[5], fifo_A[5])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[6], fifo_A[6])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[7], fifo_A[7])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[8], fifo_A[8])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[9], fifo_A[9])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[10], fifo_A[10])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[11], fifo_A[11])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[12], fifo_A[12])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[13], fifo_A[13])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[14], fifo_A[14])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[15], fifo_A[15])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[16], fifo_A[16])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[17], fifo_A[17])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[18], fifo_A[18])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[19], fifo_A[19])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[20], fifo_A[20])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[21], fifo_A[21])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[22], fifo_A[22])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[23], fifo_A[23])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[24], fifo_A[24])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[25], fifo_A[25])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[26], fifo_A[26])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[27], fifo_A[27])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[28], fifo_A[28])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[29], fifo_A[29])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[30], fifo_A[30])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[31], fifo_A[31])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[32], fifo_A[32])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[33], fifo_A[33])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[34], fifo_A[34])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[35], fifo_A[35])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[36], fifo_A[36])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[37], fifo_A[37])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[38], fifo_A[38])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[39], fifo_A[39])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[40], fifo_A[40])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[41], fifo_A[41])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[42], fifo_A[42])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[43], fifo_A[43])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[44], fifo_A[44])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[45], fifo_A[45])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[46], fifo_A[46])
        .invoke<tapa::join>(read_A, P_N, NUM_A_LEN, edge_list_ch[47], fifo_A[47])
        .invoke<tapa::join>(PEG_Xvec, PE_inst[0], fifo_A[0], fifo_X_pe[0], PE_inst[1], fifo_X_pe[1], Yvec_inst[0], fifo_aXvec[0] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[1], fifo_A[1], fifo_X_pe[1], PE_inst[2], fifo_X_pe[2], Yvec_inst[1], fifo_aXvec[1] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[2], fifo_A[2], fifo_X_pe[2], PE_inst[3], fifo_X_pe[3], Yvec_inst[2], fifo_aXvec[2] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[3], fifo_A[3], fifo_X_pe[3], PE_inst[4], fifo_X_pe[4], Yvec_inst[3], fifo_aXvec[3] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[4], fifo_A[4], fifo_X_pe[4], PE_inst[5], fifo_X_pe[5], Yvec_inst[4], fifo_aXvec[4] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[5], fifo_A[5], fifo_X_pe[5], PE_inst[6], fifo_X_pe[6], Yvec_inst[5], fifo_aXvec[5] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[6], fifo_A[6], fifo_X_pe[6], PE_inst[7], fifo_X_pe[7], Yvec_inst[6], fifo_aXvec[6] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[7], fifo_A[7], fifo_X_pe[7], PE_inst[8], fifo_X_pe[8], Yvec_inst[7], fifo_aXvec[7] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[8], fifo_A[8], fifo_X_pe[8], PE_inst[9], fifo_X_pe[9], Yvec_inst[8], fifo_aXvec[8] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[9], fifo_A[9], fifo_X_pe[9], PE_inst[10], fifo_X_pe[10], Yvec_inst[9], fifo_aXvec[9] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[10], fifo_A[10], fifo_X_pe[10], PE_inst[11], fifo_X_pe[11], Yvec_inst[10], fifo_aXvec[10] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[11], fifo_A[11], fifo_X_pe[11], PE_inst[12], fifo_X_pe[12], Yvec_inst[11], fifo_aXvec[11] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[12], fifo_A[12], fifo_X_pe[12], PE_inst[13], fifo_X_pe[13], Yvec_inst[12], fifo_aXvec[12] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[13], fifo_A[13], fifo_X_pe[13], PE_inst[14], fifo_X_pe[14], Yvec_inst[13], fifo_aXvec[13] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[14], fifo_A[14], fifo_X_pe[14], PE_inst[15], fifo_X_pe[15], Yvec_inst[14], fifo_aXvec[14] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[15], fifo_A[15], fifo_X_pe[15], PE_inst[16], fifo_X_pe[16], Yvec_inst[15], fifo_aXvec[15] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[16], fifo_A[16], fifo_X_pe[16], PE_inst[17], fifo_X_pe[17], Yvec_inst[16], fifo_aXvec[16] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[17], fifo_A[17], fifo_X_pe[17], PE_inst[18], fifo_X_pe[18], Yvec_inst[17], fifo_aXvec[17] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[18], fifo_A[18], fifo_X_pe[18], PE_inst[19], fifo_X_pe[19], Yvec_inst[18], fifo_aXvec[18] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[19], fifo_A[19], fifo_X_pe[19], PE_inst[20], fifo_X_pe[20], Yvec_inst[19], fifo_aXvec[19] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[20], fifo_A[20], fifo_X_pe[20], PE_inst[21], fifo_X_pe[21], Yvec_inst[20], fifo_aXvec[20] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[21], fifo_A[21], fifo_X_pe[21], PE_inst[22], fifo_X_pe[22], Yvec_inst[21], fifo_aXvec[21] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[22], fifo_A[22], fifo_X_pe[22], PE_inst[23], fifo_X_pe[23], Yvec_inst[22], fifo_aXvec[22] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[23], fifo_A[23], fifo_X_pe[23], PE_inst[24], fifo_X_pe[24], Yvec_inst[23], fifo_aXvec[23] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[24], fifo_A[24], fifo_X_pe[24], PE_inst[25], fifo_X_pe[25], Yvec_inst[24], fifo_aXvec[24] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[25], fifo_A[25], fifo_X_pe[25], PE_inst[26], fifo_X_pe[26], Yvec_inst[25], fifo_aXvec[25] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[26], fifo_A[26], fifo_X_pe[26], PE_inst[27], fifo_X_pe[27], Yvec_inst[26], fifo_aXvec[26] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[27], fifo_A[27], fifo_X_pe[27], PE_inst[28], fifo_X_pe[28], Yvec_inst[27], fifo_aXvec[27] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[28], fifo_A[28], fifo_X_pe[28], PE_inst[29], fifo_X_pe[29], Yvec_inst[28], fifo_aXvec[28] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[29], fifo_A[29], fifo_X_pe[29], PE_inst[30], fifo_X_pe[30], Yvec_inst[29], fifo_aXvec[29] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[30], fifo_A[30], fifo_X_pe[30], PE_inst[31], fifo_X_pe[31], Yvec_inst[30], fifo_aXvec[30] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[31], fifo_A[31], fifo_X_pe[31], PE_inst[32], fifo_X_pe[32], Yvec_inst[31], fifo_aXvec[31] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[32], fifo_A[32], fifo_X_pe[32], PE_inst[33], fifo_X_pe[33], Yvec_inst[32], fifo_aXvec[32] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[33], fifo_A[33], fifo_X_pe[33], PE_inst[34], fifo_X_pe[34], Yvec_inst[33], fifo_aXvec[33] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[34], fifo_A[34], fifo_X_pe[34], PE_inst[35], fifo_X_pe[35], Yvec_inst[34], fifo_aXvec[34] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[35], fifo_A[35], fifo_X_pe[35], PE_inst[36], fifo_X_pe[36], Yvec_inst[35], fifo_aXvec[35] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[36], fifo_A[36], fifo_X_pe[36], PE_inst[37], fifo_X_pe[37], Yvec_inst[36], fifo_aXvec[36] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[37], fifo_A[37], fifo_X_pe[37], PE_inst[38], fifo_X_pe[38], Yvec_inst[37], fifo_aXvec[37] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[38], fifo_A[38], fifo_X_pe[38], PE_inst[39], fifo_X_pe[39], Yvec_inst[38], fifo_aXvec[38] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[39], fifo_A[39], fifo_X_pe[39], PE_inst[40], fifo_X_pe[40], Yvec_inst[39], fifo_aXvec[39] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[40], fifo_A[40], fifo_X_pe[40], PE_inst[41], fifo_X_pe[41], Yvec_inst[40], fifo_aXvec[40] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[41], fifo_A[41], fifo_X_pe[41], PE_inst[42], fifo_X_pe[42], Yvec_inst[41], fifo_aXvec[41] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[42], fifo_A[42], fifo_X_pe[42], PE_inst[43], fifo_X_pe[43], Yvec_inst[42], fifo_aXvec[42] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[43], fifo_A[43], fifo_X_pe[43], PE_inst[44], fifo_X_pe[44], Yvec_inst[43], fifo_aXvec[43] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[44], fifo_A[44], fifo_X_pe[44], PE_inst[45], fifo_X_pe[45], Yvec_inst[44], fifo_aXvec[44] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[45], fifo_A[45], fifo_X_pe[45], PE_inst[46], fifo_X_pe[46], Yvec_inst[45], fifo_aXvec[45] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[46], fifo_A[46], fifo_X_pe[46], PE_inst[47], fifo_X_pe[47], Yvec_inst[46], fifo_aXvec[46] )
        .invoke<tapa::join>(PEG_Xvec, PE_inst[47], fifo_A[47], fifo_X_pe[47], PE_inst[48], fifo_X_pe[48], Yvec_inst[47], fifo_aXvec[47] )
        .invoke<tapa::detach>(black_hole_int, PE_inst[48])
        .invoke<tapa::detach>(black_hole_float_v16, fifo_X_pe[48])        
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[0], fifo_aXvec[0], fifo_Y_pe[0] )
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[1], fifo_aXvec[1], fifo_Y_pe[1])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[2], fifo_aXvec[2], fifo_Y_pe[2])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[3], fifo_aXvec[3], fifo_Y_pe[3] )
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[4], fifo_aXvec[4], fifo_Y_pe[4])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[5], fifo_aXvec[5], fifo_Y_pe[5])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[6], fifo_aXvec[6], fifo_Y_pe[6])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[7], fifo_aXvec[7], fifo_Y_pe[7])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[8], fifo_aXvec[8], fifo_Y_pe[8])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[9], fifo_aXvec[9], fifo_Y_pe[9])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[10], fifo_aXvec[10], fifo_Y_pe[10])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[11], fifo_aXvec[11], fifo_Y_pe[11])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[12], fifo_aXvec[12], fifo_Y_pe[12])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[13], fifo_aXvec[13], fifo_Y_pe[13])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[14], fifo_aXvec[14], fifo_Y_pe[14])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[15], fifo_aXvec[15], fifo_Y_pe[15])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[16], fifo_aXvec[16], fifo_Y_pe[16])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[17], fifo_aXvec[17], fifo_Y_pe[17])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[18], fifo_aXvec[18], fifo_Y_pe[18])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[19], fifo_aXvec[19], fifo_Y_pe[19])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[20], fifo_aXvec[20], fifo_Y_pe[20])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[21], fifo_aXvec[21], fifo_Y_pe[21])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[22], fifo_aXvec[22], fifo_Y_pe[22])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[23], fifo_aXvec[23], fifo_Y_pe[23])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[24], fifo_aXvec[24], fifo_Y_pe[24])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[25], fifo_aXvec[25], fifo_Y_pe[25])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[26], fifo_aXvec[26], fifo_Y_pe[26])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[27], fifo_aXvec[27], fifo_Y_pe[27])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[28], fifo_aXvec[28], fifo_Y_pe[28])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[29], fifo_aXvec[29], fifo_Y_pe[29])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[30], fifo_aXvec[30], fifo_Y_pe[30])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[31], fifo_aXvec[31], fifo_Y_pe[31])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[32], fifo_aXvec[32], fifo_Y_pe[32])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[33], fifo_aXvec[33], fifo_Y_pe[33])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[34], fifo_aXvec[34], fifo_Y_pe[34])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[35], fifo_aXvec[35], fifo_Y_pe[35])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[36], fifo_aXvec[36], fifo_Y_pe[36])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[37], fifo_aXvec[37], fifo_Y_pe[37])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[38], fifo_aXvec[38], fifo_Y_pe[38])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[39], fifo_aXvec[39], fifo_Y_pe[39])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[40], fifo_aXvec[40], fifo_Y_pe[40])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[41], fifo_aXvec[41], fifo_Y_pe[41])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[42], fifo_aXvec[42], fifo_Y_pe[42])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[43], fifo_aXvec[43], fifo_Y_pe[43])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[44], fifo_aXvec[44], fifo_Y_pe[44])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[45], fifo_aXvec[45], fifo_Y_pe[45])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[46], fifo_aXvec[46], fifo_Y_pe[46])
        .invoke<tapa::join>(PEG_Yvec, Yvec_inst[47], fifo_aXvec[47], fifo_Y_pe[47])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[0])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[1])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[2])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[3])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[4])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[5])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[6])
        .invoke<tapa::join>(Arbiter_Y, P_N, M, fifo_Y_pe, fifo_Y_pe_abd[7])
        .invoke<tapa::detach>(Merger_Y,   fifo_Y_pe_abd,   fifo_Y_AX   )
        .invoke<tapa::join>(FloatvMultConst, P_N, M, alpha_u, fifo_Y_AX, fifo_Y_alpha_AX )
        .invoke<tapa::join>(read_Y, P_N, M, vec_Y, fifo_Y_in )
        .invoke<tapa::join>(FloatvMultConst, P_N, M, beta_u, fifo_Y_in, fifo_Y_in_beta )
        .invoke<tapa::detach>(FloatvAddFloatv,   fifo_Y_alpha_AX,   fifo_Y_in_beta,   fifo_Y_out   )
        .invoke<tapa::join>(write_Y, P_N, M, fifo_Y_out, vec_Y_out )
    ;
}
