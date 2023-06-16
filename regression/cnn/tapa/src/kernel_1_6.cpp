#include <ap_int.h>
#include <tapa.h>

typedef ap_uint<512> A_t16;
typedef ap_uint<256> A_t8;
typedef ap_uint<512> B_t16;
typedef ap_uint<256> B_t8;
typedef ap_uint<512> C_t16;
typedef ap_uint<64> C_t2;

void Stream2Mmap_final(tapa::istream<C_t2>& in_board, tapa::mmap<C_t2> itemp1, tapa::mmap<C_t2> itemp2,
tapa::mmap<C_t2> itemp3, tapa::mmap<C_t2> itemp4, tapa::mmap<C_t2> itemp5, tapa::mmap<C_t2> itemp6)
// tapa::mmap<C_t2> itemp7, tapa::mmap<C_t2> itemp8, tapa::mmap<C_t2> itemp9,
// tapa::mmap<C_t2> itemp10, tapa::mmap<C_t2> itemp11, tapa::mmap<C_t2> itemp12, tapa::mmap<C_t2> itemp13, tapa::mmap<C_t2> itemp14, tapa::mmap<C_t2> itemp15, tapa::mmap<C_t2> itemp16, tapa::mmap<C_t2> itemp17

{
    for(uint64_t i=0;i<256;++i)
    {
        in_board>>itemp1[i];
        in_board>>itemp2[i];
        in_board>>itemp3[i];
        in_board>>itemp4[i];
        in_board>>itemp5[i];
        in_board>>itemp6[i];
        // in_board>>itemp7[i];
        // in_board>>itemp8[i];
        // in_board>>itemp9[i];
        // in_board>>itemp10[i];
        // in_board>>itemp11[i];
        // in_board>>itemp12[i];
        // in_board>>itemp13[i];
        // in_board>>itemp14[i];
        // in_board>>itemp15[i];
        // in_board>>itemp16[i];
        // in_board>>itemp17[i];
    }
}

void Mmap2Stream_final(tapa::ostream<B_t8>& out_board, tapa::mmap<B_t8> temp1, tapa::mmap<B_t8> temp2, tapa::mmap<B_t8> temp3, tapa::mmap<B_t8> temp4, tapa::mmap<B_t8> temp5,tapa::mmap<B_t8> temp6, tapa::mmap<B_t8> temp7)
// tapa::mmap<B_t8> temp8, tapa::mmap<B_t8> temp9, tapa::mmap<B_t8> temp10, tapa::mmap<B_t8> temp11, tapa::mmap<B_t8> temp12, tapa::mmap<B_t8> temp13, 
// tapa::mmap<B_t8> temp14, tapa::mmap<B_t8> temp15, tapa::mmap<B_t8> temp16, tapa::mmap<B_t8> temp17

{
    for(uint64_t i=0;i<256;++i)
    {
        out_board<<temp1[i];
        out_board<<temp2[i];
        out_board<<temp3[i];
        out_board<<temp4[i];
        out_board<<temp5[i];
        out_board<<temp6[i];
        out_board<<temp7[i];
        // out_board<<temp8[i];
        // out_board<<temp9[i];
        // out_board<<temp10[i];
        // out_board<<temp11[i];
        // out_board<<temp12[i];
        // out_board<<temp13[i];
        // out_board<<temp14[i];
        // out_board<<temp15[i];
        // out_board<<temp16[i];
        // out_board<<temp17[i];
    }
    
}
void Mmap2Stream_a(tapa::mmap<A_t8> mmap, uint64_t n,
                 tapa::ostream<A_t8>& stream) {
#pragma HLS INLINE OFF
  for (uint64_t i = 0; i < n; ++i) {
    stream << mmap[i];
  }
}
void Stream2Mmap_a(tapa::istream<A_t8>& stream, tapa::mmap<A_t8> mmap,
                 uint64_t n) {
#pragma HLS INLINE OFF
  for (uint64_t i = 0; i < n; ++i) {
    stream >> mmap[i];
  }
}

void Mmap2Stream_b(tapa::mmap<B_t8> mmap, uint64_t n,
                 tapa::ostream<B_t8>& stream) {
#pragma HLS INLINE OFF
  for (uint64_t i = 0; i < n; ++i) {
    stream << mmap[i];
  }
}
void Stream2Mmap_b(tapa::istream<B_t8>& stream, tapa::mmap<B_t8> mmap,
                 uint64_t n) {
#pragma HLS INLINE OFF
  for (uint64_t i = 0; i < n; ++i) {
    stream >> mmap[i];
  }
}

void Mmap2Stream_c(tapa::mmap<C_t2> mmap, uint64_t n,
                 tapa::ostream<C_t2>& stream) {
#pragma HLS INLINE OFF
  for (uint64_t i = 0; i < n; ++i) {
    stream << mmap[i];
  }
}
void Stream2Mmap_c(tapa::istream<C_t2>& stream, tapa::mmap<C_t2> mmap,
                 uint64_t n) {
#pragma HLS INLINE OFF
  for (uint64_t i = 0; i < n; ++i) {
    stream >> mmap[i];
  }
}

void A_IO_L3_in( tapa::mmap<A_t16> A, tapa::ostream<A_t8>& fifo_A_local_out ) {
#pragma HLS INLINE OFF
    for( ap_uint<13> i = 0; i < 3328; i++ ) {
#pragma HLS PIPELINE II=1
        A_t16 mem_data;
        A_t8 fifo_data;
        mem_data = A[i];
        for( ap_uint<2> p = 0; p < 2; p++ ) {
            fifo_data = mem_data( 255, 0 );
            mem_data = mem_data >> 256;
            fifo_A_local_out.write( fifo_data );
        }
    }
}

void A_IO_L2_in_intra_trans( int idx, A_t8 local_A[16][32], tapa::ostream<A_t8>& fifo_A_local_out, bool intra_trans_en )
{
#pragma HLS INLINE OFF
    int p0 = idx;
    if( !intra_trans_en ) return;
    for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
        for( ap_uint<7> c6 = 0; c6 <= 63; c6 += 1 ) {
            for( ap_uint<5> c7 = 0; c7 <= 15; c7 += 1 ) {
#pragma HLS PIPELINE II=1
                A_t8 fifo_data;
                fifo_data = local_A[c7][c5];
                fifo_A_local_out.write( fifo_data );
            }
        }
    }
}

void A_IO_L2_in_inter_trans( int idx, A_t8 local_A[16][32], tapa::istream<A_t8>& fifo_A_in, tapa::ostream<A_t8>& fifo_A_out, bool inter_trans_en )
{
#pragma HLS INLINE OFF
    int p0 = idx;
    if( !inter_trans_en ) return;
    for( ap_uint<5> c3 = p0; c3 <= 12; c3 += 1 ) {
        for( ap_uint<5> c4 = 0; c4 <= 15; c4 += 1 ) {
            for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
#pragma HLS PIPELINE II=1
                A_t8 fifo_data;
                fifo_data = fifo_A_in.read();
                if( c3 == p0 ) {
                    local_A[c4][c5] = fifo_data;
                }
                else {
                    fifo_A_out.write( fifo_data );
                }
            }
        }
    }
}

void A_IO_L2_in_inter_trans_boundary( int idx, A_t8 local_A[16][32], tapa::istream<A_t8>& fifo_A_in, bool inter_trans_en )
{
#pragma HLS INLINE OFF
    int p0 = idx;
    if( !inter_trans_en ) return;
    for( ap_uint<5> c3 = p0; c3 <= 12; c3 += 1 ) {
        for( ap_uint<5> c4 = 0; c4 <= 15; c4 += 1 ) {
            for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
#pragma HLS PIPELINE II=1
                A_t8 fifo_data;
                fifo_data = fifo_A_in.read();
                local_A[c4][c5] = fifo_data;
            }
        }
    }
}

void A_IO_L2_in( int idx, tapa::istream<A_t8>& fifo_A_in, tapa::ostream<A_t8>& fifo_A_out, tapa::ostream<A_t8>& fifo_A_local_out ) {
#pragma HLS INLINE OFF
    int p0 = idx;
    A_t8 local_A_ping[16][32];
#pragma HLS ARRAY_MAP variable=local_A_ping instance=local_A horizontal
#pragma HLS RESOURCE variable=local_A_ping core=RAM_2P_BRAM
    A_t8 local_A_pong[16][32];
#pragma HLS ARRAY_MAP variable=local_A_pong instance=local_A horizontal
#pragma HLS RESOURCE variable=local_A_pong core=RAM_2P_BRAM
    bool arb = 0;
    bool inter_trans_en = 1;
    bool intra_trans_en = 0;
    {
        {
            if( arb == 0 ) {
                A_IO_L2_in_inter_trans(
                    idx,
                    local_A_pong,
                    fifo_A_in,
                    fifo_A_out,
                    inter_trans_en
                );
                A_IO_L2_in_intra_trans(
                    idx,
                    local_A_ping,
                    fifo_A_local_out,
                    intra_trans_en
                );
            }
            else {
                A_IO_L2_in_inter_trans(
                    idx,
                    local_A_ping,
                    fifo_A_in,
                    fifo_A_out,
                    inter_trans_en
                );
                A_IO_L2_in_intra_trans(
                    idx,
                    local_A_pong,
                    fifo_A_local_out,
                    intra_trans_en
                );
            }
            intra_trans_en = 1;
            arb = !arb;
        }
        if( arb == 0 ) {
            A_IO_L2_in_intra_trans(
                idx,
                local_A_ping,
                fifo_A_local_out,
                intra_trans_en
            );
        }
        else {
            A_IO_L2_in_intra_trans(
                idx,
                local_A_pong,
                fifo_A_local_out,
                intra_trans_en
            );
        }
    }
}

void A_IO_L2_in_boundary( int idx, tapa::istream<A_t8>& fifo_A_in, tapa::ostream<A_t8>& fifo_A_local_out ) {
#pragma HLS INLINE OFF
    int p0 = idx;
    A_t8 local_A_ping[16][32];
#pragma HLS ARRAY_MAP variable=local_A_ping instance=local_A horizontal
#pragma HLS RESOURCE variable=local_A_ping core=RAM_2P_BRAM
    A_t8 local_A_pong[16][32];
#pragma HLS ARRAY_MAP variable=local_A_pong instance=local_A horizontal
#pragma HLS RESOURCE variable=local_A_pong core=RAM_2P_BRAM
    bool arb = 0;
    bool inter_trans_en = 1;
    bool intra_trans_en = 0;
    {
        {
            if( arb == 0 ) {
                A_IO_L2_in_inter_trans_boundary(
                    idx,
                    local_A_pong,
                    fifo_A_in,
                    inter_trans_en
                );
                A_IO_L2_in_intra_trans(
                    idx,
                    local_A_ping,
                    fifo_A_local_out,
                    intra_trans_en
                );
            }
            else {
                A_IO_L2_in_inter_trans_boundary(
                    idx,
                    local_A_ping,
                    fifo_A_in,
                    inter_trans_en
                );
                A_IO_L2_in_intra_trans(
                    idx,
                    local_A_pong,
                    fifo_A_local_out,
                    intra_trans_en
                );
            }
            intra_trans_en = 1;
            arb = !arb;
        }
        if( arb == 0 ) {
            A_IO_L2_in_intra_trans(
                idx,
                local_A_ping,
                fifo_A_local_out,
                intra_trans_en
            );
        }
        else {
            A_IO_L2_in_intra_trans(
                idx,
                local_A_pong,
                fifo_A_local_out,
                intra_trans_en
            );
        }
    }
}

void B_IO_L3_in( tapa::mmap<B_t16> B, tapa::ostream<B_t8>& fifo_B_local_out ) {
#pragma HLS INLINE OFF
    for( ap_uint<15> i = 0; i < 16384; i++ ) {
#pragma HLS PIPELINE II=1
        B_t16 mem_data;
        B_t8 fifo_data;
        mem_data = B[i];
        for( ap_uint<2> p = 0; p < 2; p++ ) {
            fifo_data = mem_data( 255, 0 );
            mem_data = mem_data >> 256;
            fifo_B_local_out.write( fifo_data );
        }
    }
}

void B_IO_L2_in_intra_trans( int idx, B_t8 local_B[64][32], tapa::ostream<B_t8>& fifo_B_local_out, bool intra_trans_en )
{
#pragma HLS INLINE OFF
    int p0 = idx;
    if( !intra_trans_en ) return;
    for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
        for( ap_uint<7> c6 = 0; c6 <= 63; c6 += 1 ) {
            for( ap_uint<5> c7 = 0; c7 <= 15; c7 += 1 ) {
#pragma HLS PIPELINE II=1
                B_t8 fifo_data;
                fifo_data = local_B[c6][c5];
                fifo_B_local_out.write( fifo_data );
            }
        }
    }
}

void B_IO_L2_in_inter_trans( int idx, B_t8 local_B[64][32], tapa::istream<B_t8>& fifo_B_in, tapa::ostream<B_t8>& fifo_B_out, bool inter_trans_en )
{
#pragma HLS INLINE OFF
    int p0 = idx;
    if( !inter_trans_en ) return;
    for( ap_uint<5> c3 = p0; c3 <= 15; c3 += 1 ) {
        for( ap_uint<7> c4 = 0; c4 <= 63; c4 += 1 ) {
            for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
#pragma HLS PIPELINE II=1
                B_t8 fifo_data;
                fifo_data = fifo_B_in.read();
                if( c3 == p0 ) {
                    local_B[c4][c5] = fifo_data;
                }
                else {
                    fifo_B_out.write( fifo_data );
                }
            }
        }
    }
}

void B_IO_L2_in_inter_trans_boundary( int idx, B_t8 local_B[64][32], tapa::istream<B_t8>& fifo_B_in, bool inter_trans_en )
{
#pragma HLS INLINE OFF
    int p0 = idx;
    if( !inter_trans_en ) return;
    for( ap_uint<5> c3 = p0; c3 <= 15; c3 += 1 ) {
        for( ap_uint<7> c4 = 0; c4 <= 63; c4 += 1 ) {
            for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
#pragma HLS PIPELINE II=1
                B_t8 fifo_data;
                fifo_data = fifo_B_in.read();
                local_B[c4][c5] = fifo_data;
            }
        }
    }
}

void B_IO_L2_in( int idx, tapa::istream<B_t8>& fifo_B_in, tapa::ostream<B_t8>& fifo_B_out, tapa::ostream<B_t8>& fifo_B_local_out ) {
#pragma HLS INLINE OFF
    int p0 = idx;
    B_t8 local_B_ping[64][32];
#pragma HLS ARRAY_MAP variable=local_B_ping instance=local_B horizontal
#pragma HLS RESOURCE variable=local_B_ping core=RAM_2P_BRAM
    B_t8 local_B_pong[64][32];
#pragma HLS ARRAY_MAP variable=local_B_pong instance=local_B horizontal
#pragma HLS RESOURCE variable=local_B_pong core=RAM_2P_BRAM
    bool arb = 0;
    bool inter_trans_en = 1;
    bool intra_trans_en = 0;
    {
        {
            if( arb == 0 ) {
                B_IO_L2_in_inter_trans(
                    idx,
                    local_B_pong,
                    fifo_B_in,
                    fifo_B_out,
                    inter_trans_en
                );
                B_IO_L2_in_intra_trans(
                    idx,
                    local_B_ping,
                    fifo_B_local_out,
                    intra_trans_en
                );
            }
            else {
                B_IO_L2_in_inter_trans(
                    idx,
                    local_B_ping,
                    fifo_B_in,
                    fifo_B_out,
                    inter_trans_en
                );
                B_IO_L2_in_intra_trans(
                    idx,
                    local_B_pong,
                    fifo_B_local_out,
                    intra_trans_en
                );
            }
            intra_trans_en = 1;
            arb = !arb;
        }
        if( arb == 0 ) {
            B_IO_L2_in_intra_trans(
                idx,
                local_B_ping,
                fifo_B_local_out,
                intra_trans_en
            );
        }
        else {
            B_IO_L2_in_intra_trans(
                idx,
                local_B_pong,
                fifo_B_local_out,
                intra_trans_en
            );
        }
    }
}

void B_IO_L2_in_boundary( int idx, tapa::istream<B_t8>& fifo_B_in, tapa::ostream<B_t8>& fifo_B_local_out ) {
#pragma HLS INLINE OFF
    int p0 = idx;
    B_t8 local_B_ping[64][32];
#pragma HLS ARRAY_MAP variable=local_B_ping instance=local_B horizontal
#pragma HLS RESOURCE variable=local_B_ping core=RAM_2P_BRAM
    B_t8 local_B_pong[64][32];
#pragma HLS ARRAY_MAP variable=local_B_pong instance=local_B horizontal
#pragma HLS RESOURCE variable=local_B_pong core=RAM_2P_BRAM
    bool arb = 0;
    bool inter_trans_en = 1;
    bool intra_trans_en = 0;
    {
        {
            if( arb == 0 ) {
                B_IO_L2_in_inter_trans_boundary(
                    idx,
                    local_B_pong,
                    fifo_B_in,
                    inter_trans_en
                );
                B_IO_L2_in_intra_trans(
                    idx,
                    local_B_ping,
                    fifo_B_local_out,
                    intra_trans_en
                );
            }
            else {
                B_IO_L2_in_inter_trans_boundary(
                    idx,
                    local_B_ping,
                    fifo_B_in,
                    inter_trans_en
                );
                B_IO_L2_in_intra_trans(
                    idx,
                    local_B_pong,
                    fifo_B_local_out,
                    intra_trans_en
                );
            }
            intra_trans_en = 1;
            arb = !arb;
        }
        if( arb == 0 ) {
            B_IO_L2_in_intra_trans(
                idx,
                local_B_ping,
                fifo_B_local_out,
                intra_trans_en
            );
        }
        else {
            B_IO_L2_in_intra_trans(
                idx,
                local_B_pong,
                fifo_B_local_out,
                intra_trans_en
            );
        }
    }
}

void PE( int idx, int idy, tapa::istream<A_t8>& fifo_A_in, tapa::ostream<A_t8>& fifo_A_out, tapa::istream<B_t8>& fifo_B_in, tapa::ostream<B_t8>& fifo_B_out, tapa::ostream<float>& fifo_C_drain_out ) {
#pragma HLS INLINE OFF
    int p0 = idx, p1 = idy;
    float local_A[1][8];
    float local_B[1][8];
    float local_C[16][64];
#pragma HLS RESOURCE variable=local_C core=RAM_2P_BRAM
    {
        for( ap_uint<7> c6 = 0; c6 <= 63; c6 += 1 ) {
            for( ap_uint<5> c7 = 0; c7 <= 15; c7 += 1 ) {
#pragma HLS PIPELINE II=1
                local_C[c7][c6] = 0;
            }
        }
        for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
            for( ap_uint<7> c6 = 0; c6 <= 63; c6 += 1 ) {
                for( ap_uint<5> c7 = 0; c7 <= 15; c7 += 1 ) {
#pragma HLS PIPELINE II=1
                    {

                        {

                            A_t8 fifo_data;
                            fifo_data = fifo_A_in.read();
                            for( ap_uint<4> n = 0; n < 8; n++ ) {
#pragma HLS UNROLL
                                union {
                                    unsigned int ui;
                                    float ut;
                                }
                                u;
                                u.ui = ( unsigned int )fifo_data( 31, 0 );
                                local_A[0][n] = u.ut;
                                fifo_data = fifo_data >> 32;
                            }

                        }

                        {

                            B_t8 fifo_data;
                            fifo_data = fifo_B_in.read();
                            for( ap_uint<4> n = 0; n < 8; n++ ) {
#pragma HLS UNROLL
                                union {
                                    unsigned int ui;
                                    float ut;
                                }
                                u;
                                u.ui = ( unsigned int )fifo_data( 31, 0 );
                                local_B[0][n] = u.ut;
                                fifo_data = fifo_data >> 32;
                            }

                        }

                        for( ap_uint<4> c8 = 0; c8 <= 7; c8 += 1 ) {
#pragma HLS UNROLL
                            local_C[c7][c6] = ( local_C[c7][c6] + ( local_A[0][c8] * local_B[0][c8] ) );
                        }

                        if( c5 == 31 )
                            fifo_C_drain_out.write( local_C[c7][c6] );
                        {

                            B_t8 fifo_data;
                            union {
                                unsigned int ui;
                                float ut;
                            }
                            u7, u6, u5, u4, u3, u2, u1, u0;
                            u7.ut = local_B[0][7];
                            u6.ut = local_B[0][6];
                            u5.ut = local_B[0][5];
                            u4.ut = local_B[0][4];
                            u3.ut = local_B[0][3];
                            u2.ut = local_B[0][2];
                            u1.ut = local_B[0][1];
                            u0.ut = local_B[0][0];
                            fifo_data = ( ap_uint<32>( u7.ui ), ap_uint<32>( u6.ui ), ap_uint<32>( u5.ui ), ap_uint<32>( u4.ui ), ap_uint<32>( u3.ui ), ap_uint<32>( u2.ui ), ap_uint<32>( u1.ui ), ap_uint<32>( u0.ui ) );
                            fifo_B_out.write( fifo_data );
                        }

                        {

                            A_t8 fifo_data;
                            union {
                                unsigned int ui;
                                float ut;
                            }
                            u7, u6, u5, u4, u3, u2, u1, u0;
                            u7.ut = local_A[0][7];
                            u6.ut = local_A[0][6];
                            u5.ut = local_A[0][5];
                            u4.ut = local_A[0][4];
                            u3.ut = local_A[0][3];
                            u2.ut = local_A[0][2];
                            u1.ut = local_A[0][1];
                            u0.ut = local_A[0][0];
                            fifo_data = ( ap_uint<32>( u7.ui ), ap_uint<32>( u6.ui ), ap_uint<32>( u5.ui ), ap_uint<32>( u4.ui ), ap_uint<32>( u3.ui ), ap_uint<32>( u2.ui ), ap_uint<32>( u1.ui ), ap_uint<32>( u0.ui ) );
                            fifo_A_out.write( fifo_data );
                        }

                    }
                }
            }
        }
    }
}

void PE_wrapper( int idx, int idy, tapa::istream<A_t8>& fifo_A_in, tapa::ostream<A_t8>& fifo_A_out, tapa::istream<B_t8>& fifo_B_in, tapa::ostream<B_t8>& fifo_B_out, tapa::ostream<float>& fifo_C_drain_out )
{
    PE( idx,
        idy,
        fifo_A_in,
        fifo_A_out,
        fifo_B_in,
        fifo_B_out,
        fifo_C_drain_out );
}

void A_PE_dummy( int idx, int idy, tapa::istream<A_t8>& fifo_A_in ) {
    int p0 = idx, p1 = idy;
    {
        {
        }
        for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
            for( ap_uint<7> c6 = 0; c6 <= 63; c6 += 1 ) {
                for( ap_uint<5> c7 = 0; c7 <= 15; c7 += 1 ) {
#pragma HLS PIPELINE II=1
                    A_t8 fifo_data;
                    fifo_data = fifo_A_in.read();
                }
            }
        }
    }
}

void B_PE_dummy( int idx, int idy, tapa::istream<B_t8>& fifo_B_in ) {
    int p0 = idx, p1 = idy;
    {
        {
        }
        for( ap_uint<6> c5 = 0; c5 <= 31; c5 += 1 ) {
            for( ap_uint<7> c6 = 0; c6 <= 63; c6 += 1 ) {
                for( ap_uint<5> c7 = 0; c7 <= 15; c7 += 1 ) {
#pragma HLS PIPELINE II=1
                    B_t8 fifo_data;
                    fifo_data = fifo_B_in.read();
                }
            }
        }
    }
}

void C_drain_IO_L1_out_intra_trans( int idx, int idy, C_t2 local_C[16][32], tapa::istream<float>& fifo_C_drain_local_in )
{
#pragma HLS INLINE
    int p0 = idx, p1 = idy;
    ap_uint<32> buf_data_split[2];
#pragma HLS ARRAY_PARTITION variable=buf_data_split complete
    for( ap_uint<7> c6 = 0; c6 <= 63; c6 += 1 ) {
        for( ap_uint<5> c7 = 0; c7 <= 15; c7 += 1 ) {
#pragma HLS PIPELINE II=1
            float fifo_data;
            C_t2 buf_data;
            buf_data = local_C[c7][c6 / 2];
            for( ap_uint<2> n = 0; n < 2; n++ ) {
#pragma HLS UNROLL
                buf_data_split[n] = buf_data( 31, 0 );
                buf_data = buf_data >> 32;
            }
            int split_i = ( c6 ) % 2;
            fifo_data = fifo_C_drain_local_in.read();
            union {
                unsigned int ui;
                float ut;
            }
            u;
            u.ut = fifo_data;
            buf_data_split[split_i] = ap_uint<32>( u.ui );
            buf_data = ( buf_data_split[1], buf_data_split[0] );
            local_C[c7][c6 / 2] = buf_data;
        }
    }
}

void C_drain_IO_L1_out_inter_trans( int idx, int idy, C_t2 local_C[16][32], tapa::istream<C_t2>& fifo_C_drain_in, tapa::ostream<C_t2>& fifo_C_drain_out )
{
#pragma HLS INLINE
    int p0 = idx, p1 = idy;
    for( ap_uint<5> c4 = p1; c4 <= 12; c4 += 1 ) {
        for( ap_uint<5> c5 = 0; c5 <= 15; c5 += 1 ) {
            for( ap_uint<6> c6 = 0; c6 <= 31; c6 += 1 ) {
#pragma HLS PIPELINE II=1
                C_t2 fifo_data;
                if( c4 == p1 ) {
                    fifo_data = local_C[c5][c6];
                }
                else {
                    fifo_data = fifo_C_drain_in.read();
                }
                fifo_C_drain_out.write( fifo_data );
            }
        }
    }
}

void C_drain_IO_L1_out_inter_trans_boundary( int idx, int idy, C_t2 local_C[16][32], tapa::ostream<C_t2>& fifo_C_drain_out )
{
#pragma HLS INLINE
    int p0 = idx, p1 = idy;
    for( ap_uint<5> c4 = p1; c4 <= 12; c4 += 1 ) {
        for( ap_uint<5> c5 = 0; c5 <= 15; c5 += 1 ) {
            for( ap_uint<6> c6 = 0; c6 <= 31; c6 += 1 ) {
#pragma HLS PIPELINE II=1
                C_t2 fifo_data;
                fifo_data = local_C[c5][c6];
                fifo_C_drain_out.write( fifo_data );
            }
        }
    }
}

void C_drain_IO_L1_out( int idx, int idy, tapa::istream<C_t2>& fifo_C_drain_in, tapa::ostream<C_t2>& fifo_C_drain_out, tapa::istream<float>& fifo_C_drain_local_in ) {
#pragma HLS INLINE OFF
    int p0 = idx, p1 = idy;
    C_t2 local_C[16][32];
#pragma HLS RESOURCE variable=local_C core=RAM_2P_BRAM
    C_drain_IO_L1_out_intra_trans(
        idx,
        idy,
        local_C,
        fifo_C_drain_local_in
    );
    C_drain_IO_L1_out_inter_trans(
        idx,
        idy,
        local_C,
        fifo_C_drain_in,
        fifo_C_drain_out
    );
}

void C_drain_IO_L1_out_boundary( int idx, int idy, tapa::ostream<C_t2>& fifo_C_drain_out, tapa::istream<float>& fifo_C_drain_local_in ) {
#pragma HLS INLINE OFF
    int p0 = idx, p1 = idy;
    C_t2 local_C[16][32];
#pragma HLS RESOURCE variable=local_C core=RAM_2P_BRAM
    C_drain_IO_L1_out_intra_trans(
        idx,
        idy,
        local_C,
        fifo_C_drain_local_in
    );
    C_drain_IO_L1_out_inter_trans_boundary(
        idx,
        idy,
        local_C,
        fifo_C_drain_out
    );
}

void C_drain_IO_L2_out( int idx, tapa::istream<C_t2>& fifo_C_drain_in, tapa::ostream<C_t2>& fifo_C_drain_out, tapa::istream<C_t2>& fifo_C_drain_local_in ) {
#pragma HLS INLINE OFF
    int p0 = idx;
    for( ap_uint<5> c3 = p0; c3 <= 15; c3 += 1 ) {
        for( ap_uint<5> c4 = 0; c4 <= 12; c4 += 1 ) {
            for( ap_uint<5> c5 = 0; c5 <= 15; c5 += 1 ) {
                for( ap_uint<6> c6 = 0; c6 <= 31; c6 += 1 ) {
#pragma HLS PIPELINE II=1
                    C_t2 fifo_data;
                    if( c3 == p0 ) {
                        fifo_data = fifo_C_drain_local_in.read();
                    }
                    else {
                        fifo_data = fifo_C_drain_in.read();
                    }
                    fifo_C_drain_out.write( fifo_data );
                }
            }
        }
    }
}

void C_drain_IO_L2_out_boundary( int idx, tapa::ostream<C_t2>& fifo_C_drain_out, tapa::istream<C_t2>& fifo_C_drain_local_in ) {
#pragma HLS INLINE OFF
    int p0 = idx;
    for( ap_uint<5> c3 = p0; c3 <= 15; c3 += 1 ) {
        for( ap_uint<5> c4 = 0; c4 <= 12; c4 += 1 ) {
            for( ap_uint<5> c5 = 0; c5 <= 15; c5 += 1 ) {
                for( ap_uint<6> c6 = 0; c6 <= 31; c6 += 1 ) {
#pragma HLS PIPELINE II=1
                    C_t2 fifo_data;
                    fifo_data = fifo_C_drain_local_in.read();
                    fifo_C_drain_out.write( fifo_data );
                }
            }
        }
    }
}

void C_drain_IO_L3_out( tapa::mmap<C_t16> C, tapa::istream<C_t2>& fifo_C_drain_local_in ) {
#pragma HLS INLINE OFF
    for( ap_uint<15> i = 0; i < 13312; i++ ) {
#pragma HLS PIPELINE II=1
        C_t16 mem_data;
        C_t2 fifo_data;
        C_t2 mem_data_split[8];
#pragma HLS ARRAY_PARTITION variable=mem_data_split complete
        for( ap_uint<4> p = 0; p < 8; p++ ) {
            fifo_data = fifo_C_drain_local_in.read();
            mem_data_split[p] = fifo_data;
        }
        mem_data = ( mem_data_split[7], mem_data_split[6], mem_data_split[5], mem_data_split[4], mem_data_split[3], mem_data_split[2], mem_data_split[1], mem_data_split[0] );
        C[i] = mem_data;
    }
}

// extern "C" {
void kernel3_1(tapa::mmap<A_t16> A,
tapa::mmap<B_t16> B,
tapa::mmap<C_t16> C,
tapa::ostream<B_t8> &out_board,
tapa::mmap<A_t8> &temp1,
tapa::mmap<B_t8> &temp2,
tapa::mmap<B_t8> &temp3,
tapa::mmap<B_t8> &temp4,
tapa::mmap<B_t8> &temp5,
tapa::mmap<B_t8> &temp6,
tapa::mmap<B_t8> &temp7,
// tapa::mmap<B_t8> &temp8,
// tapa::mmap<B_t8> &temp9,
// tapa::mmap<B_t8> &temp10,
// tapa::mmap<B_t8> &temp11,
// tapa::mmap<B_t8> &temp12,
// tapa::mmap<B_t8> &temp13,
// tapa::mmap<B_t8> &temp14,
// tapa::mmap<B_t8> &temp15,
// tapa::mmap<B_t8> &temp16,
// tapa::mmap<B_t8> &temp17,
tapa::mmap<C_t2> &itemp1,
tapa::mmap<C_t2> &itemp2,
tapa::mmap<C_t2> &itemp3,
tapa::mmap<C_t2> &itemp4,
tapa::mmap<C_t2> &itemp5,
tapa::mmap<C_t2> &itemp6,
// tapa::mmap<C_t2> &itemp7,
// tapa::mmap<C_t2> &itemp8,
// tapa::mmap<C_t2> &itemp9,
// tapa::mmap<C_t2> &itemp10,
// tapa::mmap<C_t2> &itemp11,
// tapa::mmap<C_t2> &itemp12,
// tapa::mmap<C_t2> &itemp13,
// tapa::mmap<C_t2> &itemp14,
// tapa::mmap<C_t2> &itemp15,
// tapa::mmap<C_t2> &itemp16,
// tapa::mmap<C_t2> &itemp17,
tapa::istream<C_t2> &in_board){
        tapa::stream<C_t2> in_board_1;
        tapa::stream<C_t2> in_board_2;
        tapa::stream<C_t2> in_board_3;
        tapa::stream<C_t2> in_board_4;
        tapa::stream<C_t2> in_board_5;
        tapa::stream<C_t2> in_board_6;
        tapa::stream<C_t2> in_board_7;
        tapa::stream<C_t2> in_board_8;
        tapa::stream<C_t2> in_board_9;
        tapa::stream<C_t2> in_board_10;
        tapa::stream<C_t2> in_board_11;
        tapa::stream<C_t2> in_board_12;
        tapa::stream<C_t2> in_board_13;
        tapa::stream<C_t2> in_board_14;
        tapa::stream<C_t2> in_board_15;
        tapa::stream<C_t2> in_board_16;
        // tapa::stream<C_t2> in_board_17;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_0;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_1;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_2;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_3;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_4;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_5;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_6;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_7;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_8;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_9;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_10;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_11;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_12;
        tapa::stream<A_t8, 2> fifo_A_A_IO_L2_in_13;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_0;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_1;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_2;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_3;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_4;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_5;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_6;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_7;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_8;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_9;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_10;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_11;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_12;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_13;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_14;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_15;
        tapa::stream<B_t8, 2> fifo_B_B_IO_L2_in_16;
        tapa::stream<A_t8, 2> fifo_A_PE_0_0;
        tapa::stream<A_t8, 2> fifo_A_PE_0_1;
        tapa::stream<A_t8, 2> fifo_A_PE_0_2;
        tapa::stream<A_t8, 2> fifo_A_PE_0_3;
        tapa::stream<A_t8, 2> fifo_A_PE_0_4;
        tapa::stream<A_t8, 2> fifo_A_PE_0_5;
        tapa::stream<A_t8, 2> fifo_A_PE_0_6;
        tapa::stream<A_t8, 2> fifo_A_PE_0_7;
        tapa::stream<A_t8, 2> fifo_A_PE_0_8;
        tapa::stream<A_t8, 2> fifo_A_PE_0_9;
        tapa::stream<A_t8, 2> fifo_A_PE_0_10;
        tapa::stream<A_t8, 2> fifo_A_PE_0_11;
        tapa::stream<A_t8, 2> fifo_A_PE_0_12;
        tapa::stream<A_t8, 2> fifo_A_PE_0_13;
        tapa::stream<A_t8, 2> fifo_A_PE_0_14;
        tapa::stream<A_t8, 2> fifo_A_PE_0_15;
        tapa::stream<A_t8, 2> fifo_A_PE_0_16;
        tapa::stream<A_t8, 2> fifo_A_PE_1_0;
        tapa::stream<A_t8, 2> fifo_A_PE_1_1;
        tapa::stream<A_t8, 2> fifo_A_PE_1_2;
        tapa::stream<A_t8, 2> fifo_A_PE_1_3;
        tapa::stream<A_t8, 2> fifo_A_PE_1_4;
        tapa::stream<A_t8, 2> fifo_A_PE_1_5;
        tapa::stream<A_t8, 2> fifo_A_PE_1_6;
        tapa::stream<A_t8, 2> fifo_A_PE_1_7;
        tapa::stream<A_t8, 2> fifo_A_PE_1_8;
        tapa::stream<A_t8, 2> fifo_A_PE_1_9;
        tapa::stream<A_t8, 2> fifo_A_PE_1_10;
        tapa::stream<A_t8, 2> fifo_A_PE_1_11;
        tapa::stream<A_t8, 2> fifo_A_PE_1_12;
        tapa::stream<A_t8, 2> fifo_A_PE_1_13;
        tapa::stream<A_t8, 2> fifo_A_PE_1_14;
        tapa::stream<A_t8, 2> fifo_A_PE_1_15;
        tapa::stream<A_t8, 2> fifo_A_PE_1_16;
        tapa::stream<A_t8, 2> fifo_A_PE_2_0;
        tapa::stream<A_t8, 2> fifo_A_PE_2_1;
        tapa::stream<A_t8, 2> fifo_A_PE_2_2;
        tapa::stream<A_t8, 2> fifo_A_PE_2_3;
        tapa::stream<A_t8, 2> fifo_A_PE_2_4;
        tapa::stream<A_t8, 2> fifo_A_PE_2_5;
        tapa::stream<A_t8, 2> fifo_A_PE_2_6;
        tapa::stream<A_t8, 2> fifo_A_PE_2_7;
        tapa::stream<A_t8, 2> fifo_A_PE_2_8;
        tapa::stream<A_t8, 2> fifo_A_PE_2_9;
        tapa::stream<A_t8, 2> fifo_A_PE_2_10;
        tapa::stream<A_t8, 2> fifo_A_PE_2_11;
        tapa::stream<A_t8, 2> fifo_A_PE_2_12;
        tapa::stream<A_t8, 2> fifo_A_PE_2_13;
        tapa::stream<A_t8, 2> fifo_A_PE_2_14;
        tapa::stream<A_t8, 2> fifo_A_PE_2_15;
        tapa::stream<A_t8, 2> fifo_A_PE_2_16;
        tapa::stream<A_t8, 2> fifo_A_PE_3_0;
        tapa::stream<A_t8, 2> fifo_A_PE_3_1;
        tapa::stream<A_t8, 2> fifo_A_PE_3_2;
        tapa::stream<A_t8, 2> fifo_A_PE_3_3;
        tapa::stream<A_t8, 2> fifo_A_PE_3_4;
        tapa::stream<A_t8, 2> fifo_A_PE_3_5;
        tapa::stream<A_t8, 2> fifo_A_PE_3_6;
        tapa::stream<A_t8, 2> fifo_A_PE_3_7;
        tapa::stream<A_t8, 2> fifo_A_PE_3_8;
        tapa::stream<A_t8, 2> fifo_A_PE_3_9;
        tapa::stream<A_t8, 2> fifo_A_PE_3_10;
        tapa::stream<A_t8, 2> fifo_A_PE_3_11;
        tapa::stream<A_t8, 2> fifo_A_PE_3_12;
        tapa::stream<A_t8, 2> fifo_A_PE_3_13;
        tapa::stream<A_t8, 2> fifo_A_PE_3_14;
        tapa::stream<A_t8, 2> fifo_A_PE_3_15;
        tapa::stream<A_t8, 2> fifo_A_PE_3_16;
        tapa::stream<A_t8, 2> fifo_A_PE_4_0;
        tapa::stream<A_t8, 2> fifo_A_PE_4_1;
        tapa::stream<A_t8, 2> fifo_A_PE_4_2;
        tapa::stream<A_t8, 2> fifo_A_PE_4_3;
        tapa::stream<A_t8, 2> fifo_A_PE_4_4;
        tapa::stream<A_t8, 2> fifo_A_PE_4_5;
        tapa::stream<A_t8, 2> fifo_A_PE_4_6;
        tapa::stream<A_t8, 2> fifo_A_PE_4_7;
        tapa::stream<A_t8, 2> fifo_A_PE_4_8;
        tapa::stream<A_t8, 2> fifo_A_PE_4_9;
        tapa::stream<A_t8, 2> fifo_A_PE_4_10;
        tapa::stream<A_t8, 2> fifo_A_PE_4_11;
        tapa::stream<A_t8, 2> fifo_A_PE_4_12;
        tapa::stream<A_t8, 2> fifo_A_PE_4_13;
        tapa::stream<A_t8, 2> fifo_A_PE_4_14;
        tapa::stream<A_t8, 2> fifo_A_PE_4_15;
        tapa::stream<A_t8, 2> fifo_A_PE_4_16;
        tapa::stream<A_t8, 2> fifo_A_PE_5_0;
        tapa::stream<A_t8, 2> fifo_A_PE_5_1;
        tapa::stream<A_t8, 2> fifo_A_PE_5_2;
        tapa::stream<A_t8, 2> fifo_A_PE_5_3;
        tapa::stream<A_t8, 2> fifo_A_PE_5_4;
        tapa::stream<A_t8, 2> fifo_A_PE_5_5;
        tapa::stream<A_t8, 2> fifo_A_PE_5_6;
        tapa::stream<A_t8, 2> fifo_A_PE_5_7;
        tapa::stream<A_t8, 2> fifo_A_PE_5_8;
        tapa::stream<A_t8, 2> fifo_A_PE_5_9;
        tapa::stream<A_t8, 2> fifo_A_PE_5_10;
        tapa::stream<A_t8, 2> fifo_A_PE_5_11;
        tapa::stream<A_t8, 2> fifo_A_PE_5_12;
        tapa::stream<A_t8, 2> fifo_A_PE_5_13;
        tapa::stream<A_t8, 2> fifo_A_PE_5_14;
        tapa::stream<A_t8, 2> fifo_A_PE_5_15;
        tapa::stream<A_t8, 2> fifo_A_PE_5_16;
        tapa::stream<A_t8, 2> fifo_A_PE_6_0;
        tapa::stream<A_t8, 2> fifo_A_PE_6_1;
        tapa::stream<A_t8, 2> fifo_A_PE_6_2;
        tapa::stream<A_t8, 2> fifo_A_PE_6_3;
        tapa::stream<A_t8, 2> fifo_A_PE_6_4;
        tapa::stream<A_t8, 2> fifo_A_PE_6_5;
        tapa::stream<A_t8, 2> fifo_A_PE_6_6;
        tapa::stream<A_t8, 2> fifo_A_PE_6_7;
        tapa::stream<A_t8, 2> fifo_A_PE_6_8;
        tapa::stream<A_t8, 2> fifo_A_PE_6_9;
        tapa::stream<A_t8, 2> fifo_A_PE_6_10;
        tapa::stream<A_t8, 2> fifo_A_PE_6_11;
        tapa::stream<A_t8, 2> fifo_A_PE_6_12;
        tapa::stream<A_t8, 2> fifo_A_PE_6_13;
        tapa::stream<A_t8, 2> fifo_A_PE_6_14;
        tapa::stream<A_t8, 2> fifo_A_PE_6_15;
        tapa::stream<A_t8, 2> fifo_A_PE_6_16;
        tapa::stream<A_t8, 2> fifo_A_PE_7_0;
        tapa::stream<A_t8, 2> fifo_A_PE_7_1;
        tapa::stream<A_t8, 2> fifo_A_PE_7_2;
        tapa::stream<A_t8, 2> fifo_A_PE_7_3;
        tapa::stream<A_t8, 2> fifo_A_PE_7_4;
        tapa::stream<A_t8, 2> fifo_A_PE_7_5;
        tapa::stream<A_t8, 2> fifo_A_PE_7_6;
        tapa::stream<A_t8, 2> fifo_A_PE_7_7;
        tapa::stream<A_t8, 2> fifo_A_PE_7_8;
        tapa::stream<A_t8, 2> fifo_A_PE_7_9;
        tapa::stream<A_t8, 2> fifo_A_PE_7_10;
        tapa::stream<A_t8, 2> fifo_A_PE_7_11;
        tapa::stream<A_t8, 2> fifo_A_PE_7_12;
        tapa::stream<A_t8, 2> fifo_A_PE_7_13;
        tapa::stream<A_t8, 2> fifo_A_PE_7_14;
        tapa::stream<A_t8, 2> fifo_A_PE_7_15;
        tapa::stream<A_t8, 2> fifo_A_PE_7_16;
        tapa::stream<A_t8, 2> fifo_A_PE_8_0;
        tapa::stream<A_t8, 2> fifo_A_PE_8_1;
        tapa::stream<A_t8, 2> fifo_A_PE_8_2;
        tapa::stream<A_t8, 2> fifo_A_PE_8_3;
        tapa::stream<A_t8, 2> fifo_A_PE_8_4;
        tapa::stream<A_t8, 2> fifo_A_PE_8_5;
        tapa::stream<A_t8, 2> fifo_A_PE_8_6;
        tapa::stream<A_t8, 2> fifo_A_PE_8_7;
        tapa::stream<A_t8, 2> fifo_A_PE_8_8;
        tapa::stream<A_t8, 2> fifo_A_PE_8_9;
        tapa::stream<A_t8, 2> fifo_A_PE_8_10;
        tapa::stream<A_t8, 2> fifo_A_PE_8_11;
        tapa::stream<A_t8, 2> fifo_A_PE_8_12;
        tapa::stream<A_t8, 2> fifo_A_PE_8_13;
        tapa::stream<A_t8, 2> fifo_A_PE_8_14;
        tapa::stream<A_t8, 2> fifo_A_PE_8_15;
        tapa::stream<A_t8, 2> fifo_A_PE_8_16;
        tapa::stream<A_t8, 2> fifo_A_PE_9_0;
        tapa::stream<A_t8, 2> fifo_A_PE_9_1;
        tapa::stream<A_t8, 2> fifo_A_PE_9_2;
        tapa::stream<A_t8, 2> fifo_A_PE_9_3;
        tapa::stream<A_t8, 2> fifo_A_PE_9_4;
        tapa::stream<A_t8, 2> fifo_A_PE_9_5;
        tapa::stream<A_t8, 2> fifo_A_PE_9_6;
        tapa::stream<A_t8, 2> fifo_A_PE_9_7;
        tapa::stream<A_t8, 2> fifo_A_PE_9_8;
        tapa::stream<A_t8, 2> fifo_A_PE_9_9;
        tapa::stream<A_t8, 2> fifo_A_PE_9_10;
        tapa::stream<A_t8, 2> fifo_A_PE_9_11;
        tapa::stream<A_t8, 2> fifo_A_PE_9_12;
        tapa::stream<A_t8, 2> fifo_A_PE_9_13;
        tapa::stream<A_t8, 2> fifo_A_PE_9_14;
        tapa::stream<A_t8, 2> fifo_A_PE_9_15;
        tapa::stream<A_t8, 2> fifo_A_PE_9_16;
        tapa::stream<A_t8, 2> fifo_A_PE_10_0;
        tapa::stream<A_t8, 2> fifo_A_PE_10_1;
        tapa::stream<A_t8, 2> fifo_A_PE_10_2;
        tapa::stream<A_t8, 2> fifo_A_PE_10_3;
        tapa::stream<A_t8, 2> fifo_A_PE_10_4;
        tapa::stream<A_t8, 2> fifo_A_PE_10_5;
        tapa::stream<A_t8, 2> fifo_A_PE_10_6;
        tapa::stream<A_t8, 2> fifo_A_PE_10_7;
        tapa::stream<A_t8, 2> fifo_A_PE_10_8;
        tapa::stream<A_t8, 2> fifo_A_PE_10_9;
        tapa::stream<A_t8, 2> fifo_A_PE_10_10;
        tapa::stream<A_t8, 2> fifo_A_PE_10_11;
        tapa::stream<A_t8, 2> fifo_A_PE_10_12;
        tapa::stream<A_t8, 2> fifo_A_PE_10_13;
        tapa::stream<A_t8, 2> fifo_A_PE_10_14;
        tapa::stream<A_t8, 2> fifo_A_PE_10_15;
        tapa::stream<A_t8, 2> fifo_A_PE_10_16;
        tapa::stream<A_t8, 2> fifo_A_PE_11_0;
        tapa::stream<A_t8, 2> fifo_A_PE_11_1;
        tapa::stream<A_t8, 2> fifo_A_PE_11_2;
        tapa::stream<A_t8, 2> fifo_A_PE_11_3;
        tapa::stream<A_t8, 2> fifo_A_PE_11_4;
        tapa::stream<A_t8, 2> fifo_A_PE_11_5;
        tapa::stream<A_t8, 2> fifo_A_PE_11_6;
        tapa::stream<A_t8, 2> fifo_A_PE_11_7;
        tapa::stream<A_t8, 2> fifo_A_PE_11_8;
        tapa::stream<A_t8, 2> fifo_A_PE_11_9;
        tapa::stream<A_t8, 2> fifo_A_PE_11_10;
        tapa::stream<A_t8, 2> fifo_A_PE_11_11;
        tapa::stream<A_t8, 2> fifo_A_PE_11_12;
        tapa::stream<A_t8, 2> fifo_A_PE_11_13;
        tapa::stream<A_t8, 2> fifo_A_PE_11_14;
        tapa::stream<A_t8, 2> fifo_A_PE_11_15;
        tapa::stream<A_t8, 2> fifo_A_PE_11_16;
        tapa::stream<A_t8, 2> fifo_A_PE_12_0;
        tapa::stream<A_t8, 2> fifo_A_PE_12_1;
        tapa::stream<A_t8, 2> fifo_A_PE_12_2;
        tapa::stream<A_t8, 2> fifo_A_PE_12_3;
        tapa::stream<A_t8, 2> fifo_A_PE_12_4;
        tapa::stream<A_t8, 2> fifo_A_PE_12_5;
        tapa::stream<A_t8, 2> fifo_A_PE_12_6;
        tapa::stream<A_t8, 2> fifo_A_PE_12_7;
        tapa::stream<A_t8, 2> fifo_A_PE_12_8;
        tapa::stream<A_t8, 2> fifo_A_PE_12_9;
        tapa::stream<A_t8, 2> fifo_A_PE_12_10;
        tapa::stream<A_t8, 2> fifo_A_PE_12_11;
        tapa::stream<A_t8, 2> fifo_A_PE_12_12;
        tapa::stream<A_t8, 2> fifo_A_PE_12_13;
        tapa::stream<A_t8, 2> fifo_A_PE_12_14;
        tapa::stream<A_t8, 2> fifo_A_PE_12_15;
        tapa::stream<A_t8, 2> fifo_A_PE_12_16;
        tapa::stream<B_t8, 2> fifo_B_PE_0_0;
        tapa::stream<B_t8, 2> fifo_B_PE_1_0;
        tapa::stream<B_t8, 2> fifo_B_PE_2_0;
        tapa::stream<B_t8, 2> fifo_B_PE_3_0;
        tapa::stream<B_t8, 2> fifo_B_PE_4_0;
        tapa::stream<B_t8, 2> fifo_B_PE_5_0;
        tapa::stream<B_t8, 2> fifo_B_PE_6_0;
        tapa::stream<B_t8, 2> fifo_B_PE_7_0;
        tapa::stream<B_t8, 2> fifo_B_PE_8_0;
        tapa::stream<B_t8, 2> fifo_B_PE_9_0;
        tapa::stream<B_t8, 2> fifo_B_PE_10_0;
        tapa::stream<B_t8, 2> fifo_B_PE_11_0;
        tapa::stream<B_t8, 2> fifo_B_PE_12_0;
        tapa::stream<B_t8, 2> fifo_B_PE_13_0;
        tapa::stream<B_t8, 2> fifo_B_PE_0_1;
        tapa::stream<B_t8, 2> fifo_B_PE_1_1;
        tapa::stream<B_t8, 2> fifo_B_PE_2_1;
        tapa::stream<B_t8, 2> fifo_B_PE_3_1;
        tapa::stream<B_t8, 2> fifo_B_PE_4_1;
        tapa::stream<B_t8, 2> fifo_B_PE_5_1;
        tapa::stream<B_t8, 2> fifo_B_PE_6_1;
        tapa::stream<B_t8, 2> fifo_B_PE_7_1;
        tapa::stream<B_t8, 2> fifo_B_PE_8_1;
        tapa::stream<B_t8, 2> fifo_B_PE_9_1;
        tapa::stream<B_t8, 2> fifo_B_PE_10_1;
        tapa::stream<B_t8, 2> fifo_B_PE_11_1;
        tapa::stream<B_t8, 2> fifo_B_PE_12_1;
        tapa::stream<B_t8, 2> fifo_B_PE_13_1;
        tapa::stream<B_t8, 2> fifo_B_PE_0_2;
        tapa::stream<B_t8, 2> fifo_B_PE_1_2;
        tapa::stream<B_t8, 2> fifo_B_PE_2_2;
        tapa::stream<B_t8, 2> fifo_B_PE_3_2;
        tapa::stream<B_t8, 2> fifo_B_PE_4_2;
        tapa::stream<B_t8, 2> fifo_B_PE_5_2;
        tapa::stream<B_t8, 2> fifo_B_PE_6_2;
        tapa::stream<B_t8, 2> fifo_B_PE_7_2;
        tapa::stream<B_t8, 2> fifo_B_PE_8_2;
        tapa::stream<B_t8, 2> fifo_B_PE_9_2;
        tapa::stream<B_t8, 2> fifo_B_PE_10_2;
        tapa::stream<B_t8, 2> fifo_B_PE_11_2;
        tapa::stream<B_t8, 2> fifo_B_PE_12_2;
        tapa::stream<B_t8, 2> fifo_B_PE_13_2;
        tapa::stream<B_t8, 2> fifo_B_PE_0_3;
        tapa::stream<B_t8, 2> fifo_B_PE_1_3;
        tapa::stream<B_t8, 2> fifo_B_PE_2_3;
        tapa::stream<B_t8, 2> fifo_B_PE_3_3;
        tapa::stream<B_t8, 2> fifo_B_PE_4_3;
        tapa::stream<B_t8, 2> fifo_B_PE_5_3;
        tapa::stream<B_t8, 2> fifo_B_PE_6_3;
        tapa::stream<B_t8, 2> fifo_B_PE_7_3;
        tapa::stream<B_t8, 2> fifo_B_PE_8_3;
        tapa::stream<B_t8, 2> fifo_B_PE_9_3;
        tapa::stream<B_t8, 2> fifo_B_PE_10_3;
        tapa::stream<B_t8, 2> fifo_B_PE_11_3;
        tapa::stream<B_t8, 2> fifo_B_PE_12_3;
        tapa::stream<B_t8, 2> fifo_B_PE_13_3;
        tapa::stream<B_t8, 2> fifo_B_PE_0_4;
        tapa::stream<B_t8, 2> fifo_B_PE_1_4;
        tapa::stream<B_t8, 2> fifo_B_PE_2_4;
        tapa::stream<B_t8, 2> fifo_B_PE_3_4;
        tapa::stream<B_t8, 2> fifo_B_PE_4_4;
        tapa::stream<B_t8, 2> fifo_B_PE_5_4;
        tapa::stream<B_t8, 2> fifo_B_PE_6_4;
        tapa::stream<B_t8, 2> fifo_B_PE_7_4;
        tapa::stream<B_t8, 2> fifo_B_PE_8_4;
        tapa::stream<B_t8, 2> fifo_B_PE_9_4;
        tapa::stream<B_t8, 2> fifo_B_PE_10_4;
        tapa::stream<B_t8, 2> fifo_B_PE_11_4;
        tapa::stream<B_t8, 2> fifo_B_PE_12_4;
        tapa::stream<B_t8, 2> fifo_B_PE_13_4;
        tapa::stream<B_t8, 2> fifo_B_PE_0_5;
        tapa::stream<B_t8, 2> fifo_B_PE_1_5;
        tapa::stream<B_t8, 2> fifo_B_PE_2_5;
        tapa::stream<B_t8, 2> fifo_B_PE_3_5;
        tapa::stream<B_t8, 2> fifo_B_PE_4_5;
        tapa::stream<B_t8, 2> fifo_B_PE_5_5;
        tapa::stream<B_t8, 2> fifo_B_PE_6_5;
        tapa::stream<B_t8, 2> fifo_B_PE_7_5;
        tapa::stream<B_t8, 2> fifo_B_PE_8_5;
        tapa::stream<B_t8, 2> fifo_B_PE_9_5;
        tapa::stream<B_t8, 2> fifo_B_PE_10_5;
        tapa::stream<B_t8, 2> fifo_B_PE_11_5;
        tapa::stream<B_t8, 2> fifo_B_PE_12_5;
        tapa::stream<B_t8, 2> fifo_B_PE_13_5;
        tapa::stream<B_t8, 2> fifo_B_PE_0_6;
        tapa::stream<B_t8, 2> fifo_B_PE_1_6;
        tapa::stream<B_t8, 2> fifo_B_PE_2_6;
        tapa::stream<B_t8, 2> fifo_B_PE_3_6;
        tapa::stream<B_t8, 2> fifo_B_PE_4_6;
        tapa::stream<B_t8, 2> fifo_B_PE_5_6;
        tapa::stream<B_t8, 2> fifo_B_PE_6_6;
        tapa::stream<B_t8, 2> fifo_B_PE_7_6;
        tapa::stream<B_t8, 2> fifo_B_PE_8_6;
        tapa::stream<B_t8, 2> fifo_B_PE_9_6;
        tapa::stream<B_t8, 2> fifo_B_PE_10_6;
        tapa::stream<B_t8, 2> fifo_B_PE_11_6;
        tapa::stream<B_t8, 2> fifo_B_PE_12_6;
        tapa::stream<B_t8, 2> fifo_B_PE_13_6;
        tapa::stream<B_t8, 2> fifo_B_PE_0_7;
        tapa::stream<B_t8, 2> fifo_B_PE_1_7;
        tapa::stream<B_t8, 2> fifo_B_PE_2_7;
        tapa::stream<B_t8, 2> fifo_B_PE_3_7;
        tapa::stream<B_t8, 2> fifo_B_PE_4_7;
        tapa::stream<B_t8, 2> fifo_B_PE_5_7;
        tapa::stream<B_t8, 2> fifo_B_PE_6_7;
        tapa::stream<B_t8, 2> fifo_B_PE_7_7;
        tapa::stream<B_t8, 2> fifo_B_PE_8_7;
        tapa::stream<B_t8, 2> fifo_B_PE_9_7;
        tapa::stream<B_t8, 2> fifo_B_PE_10_7;
        tapa::stream<B_t8, 2> fifo_B_PE_11_7;
        tapa::stream<B_t8, 2> fifo_B_PE_12_7;
        tapa::stream<B_t8, 2> fifo_B_PE_13_7;
        tapa::stream<B_t8, 2> fifo_B_PE_0_8;
        tapa::stream<B_t8, 2> fifo_B_PE_1_8;
        tapa::stream<B_t8, 2> fifo_B_PE_2_8;
        tapa::stream<B_t8, 2> fifo_B_PE_3_8;
        tapa::stream<B_t8, 2> fifo_B_PE_4_8;
        tapa::stream<B_t8, 2> fifo_B_PE_5_8;
        tapa::stream<B_t8, 2> fifo_B_PE_6_8;
        tapa::stream<B_t8, 2> fifo_B_PE_7_8;
        tapa::stream<B_t8, 2> fifo_B_PE_8_8;
        tapa::stream<B_t8, 2> fifo_B_PE_9_8;
        tapa::stream<B_t8, 2> fifo_B_PE_10_8;
        tapa::stream<B_t8, 2> fifo_B_PE_11_8;
        tapa::stream<B_t8, 2> fifo_B_PE_12_8;
        tapa::stream<B_t8, 2> fifo_B_PE_13_8;
        tapa::stream<B_t8, 2> fifo_B_PE_0_9;
        tapa::stream<B_t8, 2> fifo_B_PE_1_9;
        tapa::stream<B_t8, 2> fifo_B_PE_2_9;
        tapa::stream<B_t8, 2> fifo_B_PE_3_9;
        tapa::stream<B_t8, 2> fifo_B_PE_4_9;
        tapa::stream<B_t8, 2> fifo_B_PE_5_9;
        tapa::stream<B_t8, 2> fifo_B_PE_6_9;
        tapa::stream<B_t8, 2> fifo_B_PE_7_9;
        tapa::stream<B_t8, 2> fifo_B_PE_8_9;
        tapa::stream<B_t8, 2> fifo_B_PE_9_9;
        tapa::stream<B_t8, 2> fifo_B_PE_10_9;
        tapa::stream<B_t8, 2> fifo_B_PE_11_9;
        tapa::stream<B_t8, 2> fifo_B_PE_12_9;
        tapa::stream<B_t8, 2> fifo_B_PE_13_9;
        tapa::stream<B_t8, 2> fifo_B_PE_0_10;
        tapa::stream<B_t8, 2> fifo_B_PE_1_10;
        tapa::stream<B_t8, 2> fifo_B_PE_2_10;
        tapa::stream<B_t8, 2> fifo_B_PE_3_10;
        tapa::stream<B_t8, 2> fifo_B_PE_4_10;
        tapa::stream<B_t8, 2> fifo_B_PE_5_10;
        tapa::stream<B_t8, 2> fifo_B_PE_6_10;
        tapa::stream<B_t8, 2> fifo_B_PE_7_10;
        tapa::stream<B_t8, 2> fifo_B_PE_8_10;
        tapa::stream<B_t8, 2> fifo_B_PE_9_10;
        tapa::stream<B_t8, 2> fifo_B_PE_10_10;
        tapa::stream<B_t8, 2> fifo_B_PE_11_10;
        tapa::stream<B_t8, 2> fifo_B_PE_12_10;
        tapa::stream<B_t8, 2> fifo_B_PE_13_10;
        tapa::stream<B_t8, 2> fifo_B_PE_0_11;
        tapa::stream<B_t8, 2> fifo_B_PE_1_11;
        tapa::stream<B_t8, 2> fifo_B_PE_2_11;
        tapa::stream<B_t8, 2> fifo_B_PE_3_11;
        tapa::stream<B_t8, 2> fifo_B_PE_4_11;
        tapa::stream<B_t8, 2> fifo_B_PE_5_11;
        tapa::stream<B_t8, 2> fifo_B_PE_6_11;
        tapa::stream<B_t8, 2> fifo_B_PE_7_11;
        tapa::stream<B_t8, 2> fifo_B_PE_8_11;
        tapa::stream<B_t8, 2> fifo_B_PE_9_11;
        tapa::stream<B_t8, 2> fifo_B_PE_10_11;
        tapa::stream<B_t8, 2> fifo_B_PE_11_11;
        tapa::stream<B_t8, 2> fifo_B_PE_12_11;
        tapa::stream<B_t8, 2> fifo_B_PE_13_11;
        tapa::stream<B_t8, 2> fifo_B_PE_0_12;
        tapa::stream<B_t8, 2> fifo_B_PE_1_12;
        tapa::stream<B_t8, 2> fifo_B_PE_2_12;
        tapa::stream<B_t8, 2> fifo_B_PE_3_12;
        tapa::stream<B_t8, 2> fifo_B_PE_4_12;
        tapa::stream<B_t8, 2> fifo_B_PE_5_12;
        tapa::stream<B_t8, 2> fifo_B_PE_6_12;
        tapa::stream<B_t8, 2> fifo_B_PE_7_12;
        tapa::stream<B_t8, 2> fifo_B_PE_8_12;
        tapa::stream<B_t8, 2> fifo_B_PE_9_12;
        tapa::stream<B_t8, 2> fifo_B_PE_10_12;
        tapa::stream<B_t8, 2> fifo_B_PE_11_12;
        tapa::stream<B_t8, 2> fifo_B_PE_12_12;
        tapa::stream<B_t8, 2> fifo_B_PE_13_12;
        tapa::stream<B_t8, 2> fifo_B_PE_0_13;
        tapa::stream<B_t8, 2> fifo_B_PE_1_13;
        tapa::stream<B_t8, 2> fifo_B_PE_2_13;
        tapa::stream<B_t8, 2> fifo_B_PE_3_13;
        tapa::stream<B_t8, 2> fifo_B_PE_4_13;
        tapa::stream<B_t8, 2> fifo_B_PE_5_13;
        tapa::stream<B_t8, 2> fifo_B_PE_6_13;
        tapa::stream<B_t8, 2> fifo_B_PE_7_13;
        tapa::stream<B_t8, 2> fifo_B_PE_8_13;
        tapa::stream<B_t8, 2> fifo_B_PE_9_13;
        tapa::stream<B_t8, 2> fifo_B_PE_10_13;
        tapa::stream<B_t8, 2> fifo_B_PE_11_13;
        tapa::stream<B_t8, 2> fifo_B_PE_12_13;
        tapa::stream<B_t8, 2> fifo_B_PE_13_13;
        tapa::stream<B_t8, 2> fifo_B_PE_0_14;
        tapa::stream<B_t8, 2> fifo_B_PE_1_14;
        tapa::stream<B_t8, 2> fifo_B_PE_2_14;
        tapa::stream<B_t8, 2> fifo_B_PE_3_14;
        tapa::stream<B_t8, 2> fifo_B_PE_4_14;
        tapa::stream<B_t8, 2> fifo_B_PE_5_14;
        tapa::stream<B_t8, 2> fifo_B_PE_6_14;
        tapa::stream<B_t8, 2> fifo_B_PE_7_14;
        tapa::stream<B_t8, 2> fifo_B_PE_8_14;
        tapa::stream<B_t8, 2> fifo_B_PE_9_14;
        tapa::stream<B_t8, 2> fifo_B_PE_10_14;
        tapa::stream<B_t8, 2> fifo_B_PE_11_14;
        tapa::stream<B_t8, 2> fifo_B_PE_12_14;
        tapa::stream<B_t8, 2> fifo_B_PE_13_14;
        tapa::stream<B_t8, 2> fifo_B_PE_0_15;
        tapa::stream<B_t8, 2> fifo_B_PE_1_15;
        tapa::stream<B_t8, 2> fifo_B_PE_2_15;
        tapa::stream<B_t8, 2> fifo_B_PE_3_15;
        tapa::stream<B_t8, 2> fifo_B_PE_4_15;
        tapa::stream<B_t8, 2> fifo_B_PE_5_15;
        tapa::stream<B_t8, 2> fifo_B_PE_6_15;
        tapa::stream<B_t8, 2> fifo_B_PE_7_15;
        tapa::stream<B_t8, 2> fifo_B_PE_8_15;
        tapa::stream<B_t8, 2> fifo_B_PE_9_15;
        tapa::stream<B_t8, 2> fifo_B_PE_10_15;
        tapa::stream<B_t8, 2> fifo_B_PE_11_15;
        tapa::stream<B_t8, 2> fifo_B_PE_12_15;
        tapa::stream<B_t8, 2> fifo_B_PE_13_15;
        tapa::stream<float, 2> fifo_C_drain_PE_0_0;
        tapa::stream<float, 2> fifo_C_drain_PE_1_0;
        tapa::stream<float, 2> fifo_C_drain_PE_2_0;
        tapa::stream<float, 2> fifo_C_drain_PE_3_0;
        tapa::stream<float, 2> fifo_C_drain_PE_4_0;
        tapa::stream<float, 2> fifo_C_drain_PE_5_0;
        tapa::stream<float, 2> fifo_C_drain_PE_6_0;
        tapa::stream<float, 2> fifo_C_drain_PE_7_0;
        tapa::stream<float, 2> fifo_C_drain_PE_8_0;
        tapa::stream<float, 2> fifo_C_drain_PE_9_0;
        tapa::stream<float, 2> fifo_C_drain_PE_10_0;
        tapa::stream<float, 2> fifo_C_drain_PE_11_0;
        tapa::stream<float, 2> fifo_C_drain_PE_12_0;
        tapa::stream<float, 2> fifo_C_drain_PE_0_1;
        tapa::stream<float, 2> fifo_C_drain_PE_1_1;
        tapa::stream<float, 2> fifo_C_drain_PE_2_1;
        tapa::stream<float, 2> fifo_C_drain_PE_3_1;
        tapa::stream<float, 2> fifo_C_drain_PE_4_1;
        tapa::stream<float, 2> fifo_C_drain_PE_5_1;
        tapa::stream<float, 2> fifo_C_drain_PE_6_1;
        tapa::stream<float, 2> fifo_C_drain_PE_7_1;
        tapa::stream<float, 2> fifo_C_drain_PE_8_1;
        tapa::stream<float, 2> fifo_C_drain_PE_9_1;
        tapa::stream<float, 2> fifo_C_drain_PE_10_1;
        tapa::stream<float, 2> fifo_C_drain_PE_11_1;
        tapa::stream<float, 2> fifo_C_drain_PE_12_1;
        tapa::stream<float, 2> fifo_C_drain_PE_0_2;
        tapa::stream<float, 2> fifo_C_drain_PE_1_2;
        tapa::stream<float, 2> fifo_C_drain_PE_2_2;
        tapa::stream<float, 2> fifo_C_drain_PE_3_2;
        tapa::stream<float, 2> fifo_C_drain_PE_4_2;
        tapa::stream<float, 2> fifo_C_drain_PE_5_2;
        tapa::stream<float, 2> fifo_C_drain_PE_6_2;
        tapa::stream<float, 2> fifo_C_drain_PE_7_2;
        tapa::stream<float, 2> fifo_C_drain_PE_8_2;
        tapa::stream<float, 2> fifo_C_drain_PE_9_2;
        tapa::stream<float, 2> fifo_C_drain_PE_10_2;
        tapa::stream<float, 2> fifo_C_drain_PE_11_2;
        tapa::stream<float, 2> fifo_C_drain_PE_12_2;
        tapa::stream<float, 2> fifo_C_drain_PE_0_3;
        tapa::stream<float, 2> fifo_C_drain_PE_1_3;
        tapa::stream<float, 2> fifo_C_drain_PE_2_3;
        tapa::stream<float, 2> fifo_C_drain_PE_3_3;
        tapa::stream<float, 2> fifo_C_drain_PE_4_3;
        tapa::stream<float, 2> fifo_C_drain_PE_5_3;
        tapa::stream<float, 2> fifo_C_drain_PE_6_3;
        tapa::stream<float, 2> fifo_C_drain_PE_7_3;
        tapa::stream<float, 2> fifo_C_drain_PE_8_3;
        tapa::stream<float, 2> fifo_C_drain_PE_9_3;
        tapa::stream<float, 2> fifo_C_drain_PE_10_3;
        tapa::stream<float, 2> fifo_C_drain_PE_11_3;
        tapa::stream<float, 2> fifo_C_drain_PE_12_3;
        tapa::stream<float, 2> fifo_C_drain_PE_0_4;
        tapa::stream<float, 2> fifo_C_drain_PE_1_4;
        tapa::stream<float, 2> fifo_C_drain_PE_2_4;
        tapa::stream<float, 2> fifo_C_drain_PE_3_4;
        tapa::stream<float, 2> fifo_C_drain_PE_4_4;
        tapa::stream<float, 2> fifo_C_drain_PE_5_4;
        tapa::stream<float, 2> fifo_C_drain_PE_6_4;
        tapa::stream<float, 2> fifo_C_drain_PE_7_4;
        tapa::stream<float, 2> fifo_C_drain_PE_8_4;
        tapa::stream<float, 2> fifo_C_drain_PE_9_4;
        tapa::stream<float, 2> fifo_C_drain_PE_10_4;
        tapa::stream<float, 2> fifo_C_drain_PE_11_4;
        tapa::stream<float, 2> fifo_C_drain_PE_12_4;
        tapa::stream<float, 2> fifo_C_drain_PE_0_5;
        tapa::stream<float, 2> fifo_C_drain_PE_1_5;
        tapa::stream<float, 2> fifo_C_drain_PE_2_5;
        tapa::stream<float, 2> fifo_C_drain_PE_3_5;
        tapa::stream<float, 2> fifo_C_drain_PE_4_5;
        tapa::stream<float, 2> fifo_C_drain_PE_5_5;
        tapa::stream<float, 2> fifo_C_drain_PE_6_5;
        tapa::stream<float, 2> fifo_C_drain_PE_7_5;
        tapa::stream<float, 2> fifo_C_drain_PE_8_5;
        tapa::stream<float, 2> fifo_C_drain_PE_9_5;
        tapa::stream<float, 2> fifo_C_drain_PE_10_5;
        tapa::stream<float, 2> fifo_C_drain_PE_11_5;
        tapa::stream<float, 2> fifo_C_drain_PE_12_5;
        tapa::stream<float, 2> fifo_C_drain_PE_0_6;
        tapa::stream<float, 2> fifo_C_drain_PE_1_6;
        tapa::stream<float, 2> fifo_C_drain_PE_2_6;
        tapa::stream<float, 2> fifo_C_drain_PE_3_6;
        tapa::stream<float, 2> fifo_C_drain_PE_4_6;
        tapa::stream<float, 2> fifo_C_drain_PE_5_6;
        tapa::stream<float, 2> fifo_C_drain_PE_6_6;
        tapa::stream<float, 2> fifo_C_drain_PE_7_6;
        tapa::stream<float, 2> fifo_C_drain_PE_8_6;
        tapa::stream<float, 2> fifo_C_drain_PE_9_6;
        tapa::stream<float, 2> fifo_C_drain_PE_10_6;
        tapa::stream<float, 2> fifo_C_drain_PE_11_6;
        tapa::stream<float, 2> fifo_C_drain_PE_12_6;
        tapa::stream<float, 2> fifo_C_drain_PE_0_7;
        tapa::stream<float, 2> fifo_C_drain_PE_1_7;
        tapa::stream<float, 2> fifo_C_drain_PE_2_7;
        tapa::stream<float, 2> fifo_C_drain_PE_3_7;
        tapa::stream<float, 2> fifo_C_drain_PE_4_7;
        tapa::stream<float, 2> fifo_C_drain_PE_5_7;
        tapa::stream<float, 2> fifo_C_drain_PE_6_7;
        tapa::stream<float, 2> fifo_C_drain_PE_7_7;
        tapa::stream<float, 2> fifo_C_drain_PE_8_7;
        tapa::stream<float, 2> fifo_C_drain_PE_9_7;
        tapa::stream<float, 2> fifo_C_drain_PE_10_7;
        tapa::stream<float, 2> fifo_C_drain_PE_11_7;
        tapa::stream<float, 2> fifo_C_drain_PE_12_7;
        tapa::stream<float, 2> fifo_C_drain_PE_0_8;
        tapa::stream<float, 2> fifo_C_drain_PE_1_8;
        tapa::stream<float, 2> fifo_C_drain_PE_2_8;
        tapa::stream<float, 2> fifo_C_drain_PE_3_8;
        tapa::stream<float, 2> fifo_C_drain_PE_4_8;
        tapa::stream<float, 2> fifo_C_drain_PE_5_8;
        tapa::stream<float, 2> fifo_C_drain_PE_6_8;
        tapa::stream<float, 2> fifo_C_drain_PE_7_8;
        tapa::stream<float, 2> fifo_C_drain_PE_8_8;
        tapa::stream<float, 2> fifo_C_drain_PE_9_8;
        tapa::stream<float, 2> fifo_C_drain_PE_10_8;
        tapa::stream<float, 2> fifo_C_drain_PE_11_8;
        tapa::stream<float, 2> fifo_C_drain_PE_12_8;
        tapa::stream<float, 2> fifo_C_drain_PE_0_9;
        tapa::stream<float, 2> fifo_C_drain_PE_1_9;
        tapa::stream<float, 2> fifo_C_drain_PE_2_9;
        tapa::stream<float, 2> fifo_C_drain_PE_3_9;
        tapa::stream<float, 2> fifo_C_drain_PE_4_9;
        tapa::stream<float, 2> fifo_C_drain_PE_5_9;
        tapa::stream<float, 2> fifo_C_drain_PE_6_9;
        tapa::stream<float, 2> fifo_C_drain_PE_7_9;
        tapa::stream<float, 2> fifo_C_drain_PE_8_9;
        tapa::stream<float, 2> fifo_C_drain_PE_9_9;
        tapa::stream<float, 2> fifo_C_drain_PE_10_9;
        tapa::stream<float, 2> fifo_C_drain_PE_11_9;
        tapa::stream<float, 2> fifo_C_drain_PE_12_9;
        tapa::stream<float, 2> fifo_C_drain_PE_0_10;
        tapa::stream<float, 2> fifo_C_drain_PE_1_10;
        tapa::stream<float, 2> fifo_C_drain_PE_2_10;
        tapa::stream<float, 2> fifo_C_drain_PE_3_10;
        tapa::stream<float, 2> fifo_C_drain_PE_4_10;
        tapa::stream<float, 2> fifo_C_drain_PE_5_10;
        tapa::stream<float, 2> fifo_C_drain_PE_6_10;
        tapa::stream<float, 2> fifo_C_drain_PE_7_10;
        tapa::stream<float, 2> fifo_C_drain_PE_8_10;
        tapa::stream<float, 2> fifo_C_drain_PE_9_10;
        tapa::stream<float, 2> fifo_C_drain_PE_10_10;
        tapa::stream<float, 2> fifo_C_drain_PE_11_10;
        tapa::stream<float, 2> fifo_C_drain_PE_12_10;
        tapa::stream<float, 2> fifo_C_drain_PE_0_11;
        tapa::stream<float, 2> fifo_C_drain_PE_1_11;
        tapa::stream<float, 2> fifo_C_drain_PE_2_11;
        tapa::stream<float, 2> fifo_C_drain_PE_3_11;
        tapa::stream<float, 2> fifo_C_drain_PE_4_11;
        tapa::stream<float, 2> fifo_C_drain_PE_5_11;
        tapa::stream<float, 2> fifo_C_drain_PE_6_11;
        tapa::stream<float, 2> fifo_C_drain_PE_7_11;
        tapa::stream<float, 2> fifo_C_drain_PE_8_11;
        tapa::stream<float, 2> fifo_C_drain_PE_9_11;
        tapa::stream<float, 2> fifo_C_drain_PE_10_11;
        tapa::stream<float, 2> fifo_C_drain_PE_11_11;
        tapa::stream<float, 2> fifo_C_drain_PE_12_11;
        tapa::stream<float, 2> fifo_C_drain_PE_0_12;
        tapa::stream<float, 2> fifo_C_drain_PE_1_12;
        tapa::stream<float, 2> fifo_C_drain_PE_2_12;
        tapa::stream<float, 2> fifo_C_drain_PE_3_12;
        tapa::stream<float, 2> fifo_C_drain_PE_4_12;
        tapa::stream<float, 2> fifo_C_drain_PE_5_12;
        tapa::stream<float, 2> fifo_C_drain_PE_6_12;
        tapa::stream<float, 2> fifo_C_drain_PE_7_12;
        tapa::stream<float, 2> fifo_C_drain_PE_8_12;
        tapa::stream<float, 2> fifo_C_drain_PE_9_12;
        tapa::stream<float, 2> fifo_C_drain_PE_10_12;
        tapa::stream<float, 2> fifo_C_drain_PE_11_12;
        tapa::stream<float, 2> fifo_C_drain_PE_12_12;
        tapa::stream<float, 2> fifo_C_drain_PE_0_13;
        tapa::stream<float, 2> fifo_C_drain_PE_1_13;
        tapa::stream<float, 2> fifo_C_drain_PE_2_13;
        tapa::stream<float, 2> fifo_C_drain_PE_3_13;
        tapa::stream<float, 2> fifo_C_drain_PE_4_13;
        tapa::stream<float, 2> fifo_C_drain_PE_5_13;
        tapa::stream<float, 2> fifo_C_drain_PE_6_13;
        tapa::stream<float, 2> fifo_C_drain_PE_7_13;
        tapa::stream<float, 2> fifo_C_drain_PE_8_13;
        tapa::stream<float, 2> fifo_C_drain_PE_9_13;
        tapa::stream<float, 2> fifo_C_drain_PE_10_13;
        tapa::stream<float, 2> fifo_C_drain_PE_11_13;
        tapa::stream<float, 2> fifo_C_drain_PE_12_13;
        tapa::stream<float, 2> fifo_C_drain_PE_0_14;
        tapa::stream<float, 2> fifo_C_drain_PE_1_14;
        tapa::stream<float, 2> fifo_C_drain_PE_2_14;
        tapa::stream<float, 2> fifo_C_drain_PE_3_14;
        tapa::stream<float, 2> fifo_C_drain_PE_4_14;
        tapa::stream<float, 2> fifo_C_drain_PE_5_14;
        tapa::stream<float, 2> fifo_C_drain_PE_6_14;
        tapa::stream<float, 2> fifo_C_drain_PE_7_14;
        tapa::stream<float, 2> fifo_C_drain_PE_8_14;
        tapa::stream<float, 2> fifo_C_drain_PE_9_14;
        tapa::stream<float, 2> fifo_C_drain_PE_10_14;
        tapa::stream<float, 2> fifo_C_drain_PE_11_14;
        tapa::stream<float, 2> fifo_C_drain_PE_12_14;
        tapa::stream<float, 2> fifo_C_drain_PE_0_15;
        tapa::stream<float, 2> fifo_C_drain_PE_1_15;
        tapa::stream<float, 2> fifo_C_drain_PE_2_15;
        tapa::stream<float, 2> fifo_C_drain_PE_3_15;
        tapa::stream<float, 2> fifo_C_drain_PE_4_15;
        tapa::stream<float, 2> fifo_C_drain_PE_5_15;
        tapa::stream<float, 2> fifo_C_drain_PE_6_15;
        tapa::stream<float, 2> fifo_C_drain_PE_7_15;
        tapa::stream<float, 2> fifo_C_drain_PE_8_15;
        tapa::stream<float, 2> fifo_C_drain_PE_9_15;
        tapa::stream<float, 2> fifo_C_drain_PE_10_15;
        tapa::stream<float, 2> fifo_C_drain_PE_11_15;
        tapa::stream<float, 2> fifo_C_drain_PE_12_15;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_0_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_1_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_2_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_3_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_4_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_5_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_6_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_7_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_8_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_9_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_10_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_11_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_12_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_13_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_14_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L1_out_15_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_0;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_1;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_2;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_3;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_4;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_5;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_6;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_7;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_8;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_9;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_10;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_11;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_12;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_13;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_14;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_15;
        tapa::stream<C_t2, 2> fifo_C_drain_C_drain_IO_L2_out_16;
tapa::task()
.invoke( A_IO_L3_in, A, fifo_A_A_IO_L2_in_0 )
.invoke( A_IO_L2_in, 0, fifo_A_A_IO_L2_in_0, fifo_A_A_IO_L2_in_1, fifo_A_PE_0_0 )
.invoke( A_IO_L2_in, 1, fifo_A_A_IO_L2_in_1, fifo_A_A_IO_L2_in_2, fifo_A_PE_1_0 )
.invoke( A_IO_L2_in, 2, fifo_A_A_IO_L2_in_2, fifo_A_A_IO_L2_in_3, fifo_A_PE_2_0 )
.invoke( A_IO_L2_in, 3, fifo_A_A_IO_L2_in_3, fifo_A_A_IO_L2_in_4, fifo_A_PE_3_0 )
.invoke( A_IO_L2_in, 4, fifo_A_A_IO_L2_in_4, fifo_A_A_IO_L2_in_5, fifo_A_PE_4_0 )
.invoke( A_IO_L2_in, 5, fifo_A_A_IO_L2_in_5, fifo_A_A_IO_L2_in_6, fifo_A_PE_5_0 )
.invoke( A_IO_L2_in, 6, fifo_A_A_IO_L2_in_6, fifo_A_A_IO_L2_in_7, fifo_A_PE_6_0 )
.invoke( A_IO_L2_in, 7, fifo_A_A_IO_L2_in_7, fifo_A_A_IO_L2_in_8, fifo_A_PE_7_0 )
.invoke(Stream2Mmap_a, fifo_A_A_IO_L2_in_8, temp1, 256)
// .invoke(Mmap2Stream_a, temp1, 256, out_board_1)
.invoke( B_IO_L3_in, B, fifo_B_B_IO_L2_in_0 )
.invoke( B_IO_L2_in, 0, fifo_B_B_IO_L2_in_0, fifo_B_B_IO_L2_in_1, fifo_B_PE_0_0 )
.invoke( B_IO_L2_in,1,fifo_B_B_IO_L2_in_1,fifo_B_B_IO_L2_in_2,fifo_B_PE_0_1 )
.invoke( B_IO_L2_in, 2, fifo_B_B_IO_L2_in_2, fifo_B_B_IO_L2_in_3, fifo_B_PE_0_2 )
.invoke( B_IO_L2_in, 3, fifo_B_B_IO_L2_in_3, fifo_B_B_IO_L2_in_4, fifo_B_PE_0_3 )
.invoke( B_IO_L2_in, 4, fifo_B_B_IO_L2_in_4, fifo_B_B_IO_L2_in_5, fifo_B_PE_0_4 )
.invoke( B_IO_L2_in_boundary, 5, fifo_B_B_IO_L2_in_5, fifo_B_PE_0_5 )
// .invoke( B_IO_L2_in, 6, fifo_B_B_IO_L2_in_6, fifo_B_B_IO_L2_in_7, fifo_B_PE_0_6 )
// .invoke( B_IO_L2_in, 7, fifo_B_B_IO_L2_in_7, fifo_B_B_IO_L2_in_8, fifo_B_PE_0_7 )
// .invoke( B_IO_L2_in, 8, fifo_B_B_IO_L2_in_8, fifo_B_B_IO_L2_in_9, fifo_B_PE_0_8 )
// .invoke( B_IO_L2_in, 9, fifo_B_B_IO_L2_in_9, fifo_B_B_IO_L2_in_10, fifo_B_PE_0_9 )
// .invoke( B_IO_L2_in, 10, fifo_B_B_IO_L2_in_10, fifo_B_B_IO_L2_in_11, fifo_B_PE_0_10 )
// .invoke( B_IO_L2_in, 11, fifo_B_B_IO_L2_in_11, fifo_B_B_IO_L2_in_12, fifo_B_PE_0_11 )
// .invoke( B_IO_L2_in, 12, fifo_B_B_IO_L2_in_12, fifo_B_B_IO_L2_in_13, fifo_B_PE_0_12 )
// .invoke( B_IO_L2_in, 13, fifo_B_B_IO_L2_in_13, fifo_B_B_IO_L2_in_14, fifo_B_PE_0_13 )
// .invoke( B_IO_L2_in, 14, fifo_B_B_IO_L2_in_14, fifo_B_B_IO_L2_in_15, fifo_B_PE_0_14 )
// .invoke( B_IO_L2_in_boundary, 15, fifo_B_B_IO_L2_in_15, fifo_B_PE_0_15 )
.invoke( PE_wrapper, 0, 0, fifo_A_PE_0_0, fifo_A_PE_0_1, fifo_B_PE_0_0, fifo_B_PE_1_0, fifo_C_drain_PE_0_0 )
.invoke( PE_wrapper, 0, 1, fifo_A_PE_0_1, fifo_A_PE_0_2, fifo_B_PE_0_1, fifo_B_PE_1_1, fifo_C_drain_PE_0_1 )
.invoke( PE_wrapper, 0, 2, fifo_A_PE_0_2, fifo_A_PE_0_3, fifo_B_PE_0_2, fifo_B_PE_1_2, fifo_C_drain_PE_0_2 )
.invoke( PE_wrapper, 0, 3, fifo_A_PE_0_3, fifo_A_PE_0_4, fifo_B_PE_0_3, fifo_B_PE_1_3, fifo_C_drain_PE_0_3 )
.invoke( PE_wrapper, 0, 4, fifo_A_PE_0_4, fifo_A_PE_0_5, fifo_B_PE_0_4, fifo_B_PE_1_4, fifo_C_drain_PE_0_4 )
.invoke( PE_wrapper, 0, 5, fifo_A_PE_0_5, fifo_A_PE_0_6, fifo_B_PE_0_5, fifo_B_PE_1_5, fifo_C_drain_PE_0_5 )
// .invoke( PE_wrapper, 0, 6, fifo_A_PE_0_6, fifo_A_PE_0_7, fifo_B_PE_0_6, fifo_B_PE_1_6, fifo_C_drain_PE_0_6 )
// .invoke( PE_wrapper, 0, 7, fifo_A_PE_0_7, fifo_A_PE_0_8, fifo_B_PE_0_7, fifo_B_PE_1_7, fifo_C_drain_PE_0_7 )
// .invoke( PE_wrapper, 0, 8, fifo_A_PE_0_8, fifo_A_PE_0_9, fifo_B_PE_0_8, fifo_B_PE_1_8, fifo_C_drain_PE_0_8 )
// .invoke( PE_wrapper, 0, 9, fifo_A_PE_0_9, fifo_A_PE_0_10, fifo_B_PE_0_9, fifo_B_PE_1_9, fifo_C_drain_PE_0_9 )
// .invoke( PE_wrapper, 0, 10, fifo_A_PE_0_10, fifo_A_PE_0_11, fifo_B_PE_0_10, fifo_B_PE_1_10, fifo_C_drain_PE_0_10 )
// .invoke( PE_wrapper, 0, 11, fifo_A_PE_0_11, fifo_A_PE_0_12, fifo_B_PE_0_11, fifo_B_PE_1_11, fifo_C_drain_PE_0_11 )
// .invoke( PE_wrapper, 0, 12, fifo_A_PE_0_12, fifo_A_PE_0_13, fifo_B_PE_0_12, fifo_B_PE_1_12, fifo_C_drain_PE_0_12 )
// .invoke( PE_wrapper, 0, 13, fifo_A_PE_0_13, fifo_A_PE_0_14, fifo_B_PE_0_13, fifo_B_PE_1_13, fifo_C_drain_PE_0_13 )
// .invoke( PE_wrapper, 0, 14, fifo_A_PE_0_14, fifo_A_PE_0_15, fifo_B_PE_0_14, fifo_B_PE_1_14, fifo_C_drain_PE_0_14 )
// .invoke( PE_wrapper, 0, 15, fifo_A_PE_0_15, fifo_A_PE_0_16, fifo_B_PE_0_15, fifo_B_PE_1_15, fifo_C_drain_PE_0_15 )
.invoke( PE_wrapper, 1, 0, fifo_A_PE_1_0, fifo_A_PE_1_1, fifo_B_PE_1_0, fifo_B_PE_2_0, fifo_C_drain_PE_1_0 )
.invoke( PE_wrapper, 1, 1, fifo_A_PE_1_1, fifo_A_PE_1_2, fifo_B_PE_1_1, fifo_B_PE_2_1, fifo_C_drain_PE_1_1 )
.invoke( PE_wrapper, 1, 2, fifo_A_PE_1_2, fifo_A_PE_1_3, fifo_B_PE_1_2, fifo_B_PE_2_2, fifo_C_drain_PE_1_2 )
.invoke( PE_wrapper, 1, 3, fifo_A_PE_1_3, fifo_A_PE_1_4, fifo_B_PE_1_3, fifo_B_PE_2_3, fifo_C_drain_PE_1_3 )
.invoke( PE_wrapper, 1, 4, fifo_A_PE_1_4, fifo_A_PE_1_5, fifo_B_PE_1_4, fifo_B_PE_2_4, fifo_C_drain_PE_1_4 )
.invoke( PE_wrapper, 1, 5, fifo_A_PE_1_5, fifo_A_PE_1_6, fifo_B_PE_1_5, fifo_B_PE_2_5, fifo_C_drain_PE_1_5 )
// .invoke( PE_wrapper, 1, 6, fifo_A_PE_1_6, fifo_A_PE_1_7, fifo_B_PE_1_6, fifo_B_PE_2_6, fifo_C_drain_PE_1_6 )
// .invoke( PE_wrapper, 1, 7, fifo_A_PE_1_7, fifo_A_PE_1_8, fifo_B_PE_1_7, fifo_B_PE_2_7, fifo_C_drain_PE_1_7 )
// .invoke( PE_wrapper, 1, 8, fifo_A_PE_1_8, fifo_A_PE_1_9, fifo_B_PE_1_8, fifo_B_PE_2_8, fifo_C_drain_PE_1_8 )
// .invoke( PE_wrapper, 1, 9, fifo_A_PE_1_9, fifo_A_PE_1_10, fifo_B_PE_1_9, fifo_B_PE_2_9, fifo_C_drain_PE_1_9 )
// .invoke( PE_wrapper, 1, 10, fifo_A_PE_1_10, fifo_A_PE_1_11, fifo_B_PE_1_10, fifo_B_PE_2_10, fifo_C_drain_PE_1_10 )
// .invoke( PE_wrapper, 1, 11, fifo_A_PE_1_11, fifo_A_PE_1_12, fifo_B_PE_1_11, fifo_B_PE_2_11, fifo_C_drain_PE_1_11 )
// .invoke( PE_wrapper, 1, 12, fifo_A_PE_1_12, fifo_A_PE_1_13, fifo_B_PE_1_12, fifo_B_PE_2_12, fifo_C_drain_PE_1_12 )
// .invoke( PE_wrapper, 1, 13, fifo_A_PE_1_13, fifo_A_PE_1_14, fifo_B_PE_1_13, fifo_B_PE_2_13, fifo_C_drain_PE_1_13 )
// .invoke( PE_wrapper, 1, 14, fifo_A_PE_1_14, fifo_A_PE_1_15, fifo_B_PE_1_14, fifo_B_PE_2_14, fifo_C_drain_PE_1_14 )
// .invoke( PE_wrapper, 1, 15, fifo_A_PE_1_15, fifo_A_PE_1_16, fifo_B_PE_1_15, fifo_B_PE_2_15, fifo_C_drain_PE_1_15 )
.invoke( PE_wrapper, 2, 0, fifo_A_PE_2_0, fifo_A_PE_2_1, fifo_B_PE_2_0, fifo_B_PE_3_0, fifo_C_drain_PE_2_0 )
.invoke( PE_wrapper, 2, 1, fifo_A_PE_2_1, fifo_A_PE_2_2, fifo_B_PE_2_1, fifo_B_PE_3_1, fifo_C_drain_PE_2_1 )
.invoke( PE_wrapper, 2, 2, fifo_A_PE_2_2, fifo_A_PE_2_3, fifo_B_PE_2_2, fifo_B_PE_3_2, fifo_C_drain_PE_2_2 )
.invoke( PE_wrapper, 2, 3, fifo_A_PE_2_3, fifo_A_PE_2_4, fifo_B_PE_2_3, fifo_B_PE_3_3, fifo_C_drain_PE_2_3 )
.invoke( PE_wrapper, 2, 4, fifo_A_PE_2_4, fifo_A_PE_2_5, fifo_B_PE_2_4, fifo_B_PE_3_4, fifo_C_drain_PE_2_4 )
.invoke( PE_wrapper, 2, 5, fifo_A_PE_2_5, fifo_A_PE_2_6, fifo_B_PE_2_5, fifo_B_PE_3_5, fifo_C_drain_PE_2_5 )
// .invoke( PE_wrapper, 2, 6, fifo_A_PE_2_6, fifo_A_PE_2_7, fifo_B_PE_2_6, fifo_B_PE_3_6, fifo_C_drain_PE_2_6 )
// .invoke( PE_wrapper, 2, 7, fifo_A_PE_2_7, fifo_A_PE_2_8, fifo_B_PE_2_7, fifo_B_PE_3_7, fifo_C_drain_PE_2_7 )
// .invoke( PE_wrapper, 2, 8, fifo_A_PE_2_8, fifo_A_PE_2_9, fifo_B_PE_2_8, fifo_B_PE_3_8, fifo_C_drain_PE_2_8 )
// .invoke( PE_wrapper, 2, 9, fifo_A_PE_2_9, fifo_A_PE_2_10, fifo_B_PE_2_9, fifo_B_PE_3_9, fifo_C_drain_PE_2_9 )
// .invoke( PE_wrapper, 2, 10, fifo_A_PE_2_10, fifo_A_PE_2_11, fifo_B_PE_2_10, fifo_B_PE_3_10, fifo_C_drain_PE_2_10 )
// .invoke( PE_wrapper, 2, 11, fifo_A_PE_2_11, fifo_A_PE_2_12, fifo_B_PE_2_11, fifo_B_PE_3_11, fifo_C_drain_PE_2_11 )
// .invoke( PE_wrapper, 2, 12, fifo_A_PE_2_12, fifo_A_PE_2_13, fifo_B_PE_2_12, fifo_B_PE_3_12, fifo_C_drain_PE_2_12 )
// .invoke( PE_wrapper, 2, 13, fifo_A_PE_2_13, fifo_A_PE_2_14, fifo_B_PE_2_13, fifo_B_PE_3_13, fifo_C_drain_PE_2_13 )
// .invoke( PE_wrapper, 2, 14, fifo_A_PE_2_14, fifo_A_PE_2_15, fifo_B_PE_2_14, fifo_B_PE_3_14, fifo_C_drain_PE_2_14 )
// .invoke( PE_wrapper, 2, 15, fifo_A_PE_2_15, fifo_A_PE_2_16, fifo_B_PE_2_15, fifo_B_PE_3_15, fifo_C_drain_PE_2_15 )
.invoke( PE_wrapper, 3, 0, fifo_A_PE_3_0, fifo_A_PE_3_1, fifo_B_PE_3_0, fifo_B_PE_4_0, fifo_C_drain_PE_3_0 )
.invoke( PE_wrapper, 3, 1, fifo_A_PE_3_1, fifo_A_PE_3_2, fifo_B_PE_3_1, fifo_B_PE_4_1, fifo_C_drain_PE_3_1 )
.invoke( PE_wrapper, 3, 2, fifo_A_PE_3_2, fifo_A_PE_3_3, fifo_B_PE_3_2, fifo_B_PE_4_2, fifo_C_drain_PE_3_2 )
.invoke( PE_wrapper, 3, 3, fifo_A_PE_3_3, fifo_A_PE_3_4, fifo_B_PE_3_3, fifo_B_PE_4_3, fifo_C_drain_PE_3_3 )
.invoke( PE_wrapper, 3, 4, fifo_A_PE_3_4, fifo_A_PE_3_5, fifo_B_PE_3_4, fifo_B_PE_4_4, fifo_C_drain_PE_3_4 )
.invoke( PE_wrapper, 3, 5, fifo_A_PE_3_5, fifo_A_PE_3_6, fifo_B_PE_3_5, fifo_B_PE_4_5, fifo_C_drain_PE_3_5 )
// .invoke( PE_wrapper, 3, 6, fifo_A_PE_3_6, fifo_A_PE_3_7, fifo_B_PE_3_6, fifo_B_PE_4_6, fifo_C_drain_PE_3_6 )
// .invoke( PE_wrapper, 3, 7, fifo_A_PE_3_7, fifo_A_PE_3_8, fifo_B_PE_3_7, fifo_B_PE_4_7, fifo_C_drain_PE_3_7 )
// .invoke( PE_wrapper, 3, 8, fifo_A_PE_3_8, fifo_A_PE_3_9, fifo_B_PE_3_8, fifo_B_PE_4_8, fifo_C_drain_PE_3_8 )
// .invoke( PE_wrapper, 3, 9, fifo_A_PE_3_9, fifo_A_PE_3_10, fifo_B_PE_3_9, fifo_B_PE_4_9, fifo_C_drain_PE_3_9 )
// .invoke( PE_wrapper, 3, 10, fifo_A_PE_3_10, fifo_A_PE_3_11, fifo_B_PE_3_10, fifo_B_PE_4_10, fifo_C_drain_PE_3_10 )
// .invoke( PE_wrapper, 3, 11, fifo_A_PE_3_11, fifo_A_PE_3_12, fifo_B_PE_3_11, fifo_B_PE_4_11, fifo_C_drain_PE_3_11 )
// .invoke( PE_wrapper, 3, 12, fifo_A_PE_3_12, fifo_A_PE_3_13, fifo_B_PE_3_12, fifo_B_PE_4_12, fifo_C_drain_PE_3_12 )
// .invoke( PE_wrapper, 3, 13, fifo_A_PE_3_13, fifo_A_PE_3_14, fifo_B_PE_3_13, fifo_B_PE_4_13, fifo_C_drain_PE_3_13 )
// .invoke( PE_wrapper, 3, 14, fifo_A_PE_3_14, fifo_A_PE_3_15, fifo_B_PE_3_14, fifo_B_PE_4_14, fifo_C_drain_PE_3_14 )
// .invoke( PE_wrapper, 3, 15, fifo_A_PE_3_15, fifo_A_PE_3_16, fifo_B_PE_3_15, fifo_B_PE_4_15, fifo_C_drain_PE_3_15 )
.invoke( PE_wrapper, 4, 0, fifo_A_PE_4_0, fifo_A_PE_4_1, fifo_B_PE_4_0, fifo_B_PE_5_0, fifo_C_drain_PE_4_0 )
.invoke( PE_wrapper, 4, 1, fifo_A_PE_4_1, fifo_A_PE_4_2, fifo_B_PE_4_1, fifo_B_PE_5_1, fifo_C_drain_PE_4_1 )
.invoke( PE_wrapper, 4, 2, fifo_A_PE_4_2, fifo_A_PE_4_3, fifo_B_PE_4_2, fifo_B_PE_5_2, fifo_C_drain_PE_4_2 )
.invoke( PE_wrapper, 4, 3, fifo_A_PE_4_3, fifo_A_PE_4_4, fifo_B_PE_4_3, fifo_B_PE_5_3, fifo_C_drain_PE_4_3 )
.invoke( PE_wrapper, 4, 4, fifo_A_PE_4_4, fifo_A_PE_4_5, fifo_B_PE_4_4, fifo_B_PE_5_4, fifo_C_drain_PE_4_4 )
.invoke( PE_wrapper, 4, 5, fifo_A_PE_4_5, fifo_A_PE_4_6, fifo_B_PE_4_5, fifo_B_PE_5_5, fifo_C_drain_PE_4_5 )
// .invoke( PE_wrapper, 4, 6, fifo_A_PE_4_6, fifo_A_PE_4_7, fifo_B_PE_4_6, fifo_B_PE_5_6, fifo_C_drain_PE_4_6 )
// .invoke( PE_wrapper, 4, 7, fifo_A_PE_4_7, fifo_A_PE_4_8, fifo_B_PE_4_7, fifo_B_PE_5_7, fifo_C_drain_PE_4_7 )
// .invoke( PE_wrapper, 4, 8, fifo_A_PE_4_8, fifo_A_PE_4_9, fifo_B_PE_4_8, fifo_B_PE_5_8, fifo_C_drain_PE_4_8 )
// .invoke( PE_wrapper, 4, 9, fifo_A_PE_4_9, fifo_A_PE_4_10, fifo_B_PE_4_9, fifo_B_PE_5_9, fifo_C_drain_PE_4_9 )
// .invoke( PE_wrapper, 4, 10, fifo_A_PE_4_10, fifo_A_PE_4_11, fifo_B_PE_4_10, fifo_B_PE_5_10, fifo_C_drain_PE_4_10 )
// .invoke( PE_wrapper, 4, 11, fifo_A_PE_4_11, fifo_A_PE_4_12, fifo_B_PE_4_11, fifo_B_PE_5_11, fifo_C_drain_PE_4_11 )
// .invoke( PE_wrapper, 4, 12, fifo_A_PE_4_12, fifo_A_PE_4_13, fifo_B_PE_4_12, fifo_B_PE_5_12, fifo_C_drain_PE_4_12 )
// .invoke( PE_wrapper, 4, 13, fifo_A_PE_4_13, fifo_A_PE_4_14, fifo_B_PE_4_13, fifo_B_PE_5_13, fifo_C_drain_PE_4_13 )
// .invoke( PE_wrapper, 4, 14, fifo_A_PE_4_14, fifo_A_PE_4_15, fifo_B_PE_4_14, fifo_B_PE_5_14, fifo_C_drain_PE_4_14 )
// .invoke( PE_wrapper, 4, 15, fifo_A_PE_4_15, fifo_A_PE_4_16, fifo_B_PE_4_15, fifo_B_PE_5_15, fifo_C_drain_PE_4_15 )
.invoke( PE_wrapper, 5, 0, fifo_A_PE_5_0, fifo_A_PE_5_1, fifo_B_PE_5_0, fifo_B_PE_6_0, fifo_C_drain_PE_5_0 )
.invoke( PE_wrapper, 5, 1, fifo_A_PE_5_1, fifo_A_PE_5_2, fifo_B_PE_5_1, fifo_B_PE_6_1, fifo_C_drain_PE_5_1 )
.invoke( PE_wrapper, 5, 2, fifo_A_PE_5_2, fifo_A_PE_5_3, fifo_B_PE_5_2, fifo_B_PE_6_2, fifo_C_drain_PE_5_2 )
.invoke( PE_wrapper, 5, 3, fifo_A_PE_5_3, fifo_A_PE_5_4, fifo_B_PE_5_3, fifo_B_PE_6_3, fifo_C_drain_PE_5_3 )
.invoke( PE_wrapper, 5, 4, fifo_A_PE_5_4, fifo_A_PE_5_5, fifo_B_PE_5_4, fifo_B_PE_6_4, fifo_C_drain_PE_5_4 )
.invoke( PE_wrapper, 5, 5, fifo_A_PE_5_5, fifo_A_PE_5_6, fifo_B_PE_5_5, fifo_B_PE_6_5, fifo_C_drain_PE_5_5 )
// .invoke( PE_wrapper, 5, 6, fifo_A_PE_5_6, fifo_A_PE_5_7, fifo_B_PE_5_6, fifo_B_PE_6_6, fifo_C_drain_PE_5_6 )
// .invoke( PE_wrapper, 5, 7, fifo_A_PE_5_7, fifo_A_PE_5_8, fifo_B_PE_5_7, fifo_B_PE_6_7, fifo_C_drain_PE_5_7 )
// .invoke( PE_wrapper, 5, 8, fifo_A_PE_5_8, fifo_A_PE_5_9, fifo_B_PE_5_8, fifo_B_PE_6_8, fifo_C_drain_PE_5_8 )
// .invoke( PE_wrapper, 5, 9, fifo_A_PE_5_9, fifo_A_PE_5_10, fifo_B_PE_5_9, fifo_B_PE_6_9, fifo_C_drain_PE_5_9 )
// .invoke( PE_wrapper, 5, 10, fifo_A_PE_5_10, fifo_A_PE_5_11, fifo_B_PE_5_10, fifo_B_PE_6_10, fifo_C_drain_PE_5_10 )
// .invoke( PE_wrapper, 5, 11, fifo_A_PE_5_11, fifo_A_PE_5_12, fifo_B_PE_5_11, fifo_B_PE_6_11, fifo_C_drain_PE_5_11 )
// .invoke( PE_wrapper, 5, 12, fifo_A_PE_5_12, fifo_A_PE_5_13, fifo_B_PE_5_12, fifo_B_PE_6_12, fifo_C_drain_PE_5_12 )
// .invoke( PE_wrapper, 5, 13, fifo_A_PE_5_13, fifo_A_PE_5_14, fifo_B_PE_5_13, fifo_B_PE_6_13, fifo_C_drain_PE_5_13 )
// .invoke( PE_wrapper, 5, 14, fifo_A_PE_5_14, fifo_A_PE_5_15, fifo_B_PE_5_14, fifo_B_PE_6_14, fifo_C_drain_PE_5_14 )
// .invoke( PE_wrapper, 5, 15, fifo_A_PE_5_15, fifo_A_PE_5_16, fifo_B_PE_5_15, fifo_B_PE_6_15, fifo_C_drain_PE_5_15 )
.invoke( PE_wrapper, 6, 0, fifo_A_PE_6_0, fifo_A_PE_6_1, fifo_B_PE_6_0, fifo_B_PE_7_0, fifo_C_drain_PE_6_0 )
.invoke( PE_wrapper, 6, 1, fifo_A_PE_6_1, fifo_A_PE_6_2, fifo_B_PE_6_1, fifo_B_PE_7_1, fifo_C_drain_PE_6_1 )
.invoke( PE_wrapper, 6, 2, fifo_A_PE_6_2, fifo_A_PE_6_3, fifo_B_PE_6_2, fifo_B_PE_7_2, fifo_C_drain_PE_6_2 )
.invoke( PE_wrapper, 6, 3, fifo_A_PE_6_3, fifo_A_PE_6_4, fifo_B_PE_6_3, fifo_B_PE_7_3, fifo_C_drain_PE_6_3 )
.invoke( PE_wrapper, 6, 4, fifo_A_PE_6_4, fifo_A_PE_6_5, fifo_B_PE_6_4, fifo_B_PE_7_4, fifo_C_drain_PE_6_4 )
.invoke( PE_wrapper, 6, 5, fifo_A_PE_6_5, fifo_A_PE_6_6, fifo_B_PE_6_5, fifo_B_PE_7_5, fifo_C_drain_PE_6_5 )
// .invoke( PE_wrapper, 6, 6, fifo_A_PE_6_6, fifo_A_PE_6_7, fifo_B_PE_6_6, fifo_B_PE_7_6, fifo_C_drain_PE_6_6 )
// .invoke( PE_wrapper, 6, 7, fifo_A_PE_6_7, fifo_A_PE_6_8, fifo_B_PE_6_7, fifo_B_PE_7_7, fifo_C_drain_PE_6_7 )
// .invoke( PE_wrapper, 6, 8, fifo_A_PE_6_8, fifo_A_PE_6_9, fifo_B_PE_6_8, fifo_B_PE_7_8, fifo_C_drain_PE_6_8 )
// .invoke( PE_wrapper, 6, 9, fifo_A_PE_6_9, fifo_A_PE_6_10, fifo_B_PE_6_9, fifo_B_PE_7_9, fifo_C_drain_PE_6_9 )
// .invoke( PE_wrapper, 6, 10, fifo_A_PE_6_10, fifo_A_PE_6_11, fifo_B_PE_6_10, fifo_B_PE_7_10, fifo_C_drain_PE_6_10 )
// .invoke( PE_wrapper, 6, 11, fifo_A_PE_6_11, fifo_A_PE_6_12, fifo_B_PE_6_11, fifo_B_PE_7_11, fifo_C_drain_PE_6_11 )
// .invoke( PE_wrapper, 6, 12, fifo_A_PE_6_12, fifo_A_PE_6_13, fifo_B_PE_6_12, fifo_B_PE_7_12, fifo_C_drain_PE_6_12 )
// .invoke( PE_wrapper, 6, 13, fifo_A_PE_6_13, fifo_A_PE_6_14, fifo_B_PE_6_13, fifo_B_PE_7_13, fifo_C_drain_PE_6_13 )
// .invoke( PE_wrapper, 6, 14, fifo_A_PE_6_14, fifo_A_PE_6_15, fifo_B_PE_6_14, fifo_B_PE_7_14, fifo_C_drain_PE_6_14 )
// .invoke( PE_wrapper, 6, 15, fifo_A_PE_6_15, fifo_A_PE_6_16, fifo_B_PE_6_15, fifo_B_PE_7_15, fifo_C_drain_PE_6_15 )
.invoke( PE_wrapper, 7, 0, fifo_A_PE_7_0, fifo_A_PE_7_1, fifo_B_PE_7_0, fifo_B_PE_8_0, fifo_C_drain_PE_7_0 )
.invoke(Stream2Mmap_b, fifo_B_PE_8_0, temp2, 256)
// .invoke(Mmap2Stream_b, temp2, 256, out_board_2)
.invoke( PE_wrapper, 7, 1, fifo_A_PE_7_1, fifo_A_PE_7_2, fifo_B_PE_7_1, fifo_B_PE_8_1, fifo_C_drain_PE_7_1 )
.invoke(Stream2Mmap_b, fifo_B_PE_8_1, temp3, 256)
// .invoke(Mmap2Stream_b, temp3, 256, out_board_3)
.invoke( PE_wrapper, 7, 2, fifo_A_PE_7_2, fifo_A_PE_7_3, fifo_B_PE_7_2, fifo_B_PE_8_2, fifo_C_drain_PE_7_2 )
.invoke(Stream2Mmap_b, fifo_B_PE_8_2, temp4, 256)
// // .invoke(Mmap2Stream_b, temp4, 256, out_board_4)
.invoke( PE_wrapper, 7, 3, fifo_A_PE_7_3, fifo_A_PE_7_4, fifo_B_PE_7_3, fifo_B_PE_8_3, fifo_C_drain_PE_7_3 )
.invoke(Stream2Mmap_b, fifo_B_PE_8_3, temp5, 256)
// // .invoke(Mmap2Stream_b, temp5, 256, out_board_5)
.invoke( PE_wrapper, 7, 4, fifo_A_PE_7_4, fifo_A_PE_7_5, fifo_B_PE_7_4, fifo_B_PE_8_4, fifo_C_drain_PE_7_4 )
.invoke(Stream2Mmap_b, fifo_B_PE_8_4, temp6, 256)
// // .invoke(Mmap2Stream_b, temp6, 256, out_board_6)
.invoke( PE_wrapper, 7, 5, fifo_A_PE_7_5, fifo_A_PE_7_6, fifo_B_PE_7_5, fifo_B_PE_8_5, fifo_C_drain_PE_7_5 )
.invoke(Stream2Mmap_b, fifo_B_PE_8_5, temp7, 256)
// // .invoke(Mmap2Stream_b, temp7, 256, out_board_7)
// .invoke( PE_wrapper, 7, 6, fifo_A_PE_7_6, fifo_A_PE_7_7, fifo_B_PE_7_6, fifo_B_PE_8_6, fifo_C_drain_PE_7_6 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_6, temp8, 256)
// // .invoke(Mmap2Stream_b, temp8, 256, out_board_8)
// .invoke( PE_wrapper, 7, 7, fifo_A_PE_7_7, fifo_A_PE_7_8, fifo_B_PE_7_7, fifo_B_PE_8_7, fifo_C_drain_PE_7_7 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_7, temp9, 256)
// // .invoke(Mmap2Stream_b, temp9, 256, out_board_9)
// .invoke( PE_wrapper, 7, 8, fifo_A_PE_7_8, fifo_A_PE_7_9, fifo_B_PE_7_8, fifo_B_PE_8_8, fifo_C_drain_PE_7_8 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_8, temp10, 256)
// // .invoke(Mmap2Stream_b, temp10, 256, out_board_10)
// .invoke( PE_wrapper, 7, 9, fifo_A_PE_7_9, fifo_A_PE_7_10, fifo_B_PE_7_9, fifo_B_PE_8_9, fifo_C_drain_PE_7_9 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_9, temp11, 256)
// // .invoke(Mmap2Stream_b, temp11, 256, out_board_11)
// // .invoke(B_PE_dummy, 8, 9, out_board_11)
// .invoke( PE_wrapper, 7, 10, fifo_A_PE_7_10, fifo_A_PE_7_11, fifo_B_PE_7_10, fifo_B_PE_8_10, fifo_C_drain_PE_7_10 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_10, temp12, 256)
// // .invoke(Mmap2Stream_b, temp12, 256, out_board_12)
// .invoke( PE_wrapper, 7, 11, fifo_A_PE_7_11, fifo_A_PE_7_12, fifo_B_PE_7_11, fifo_B_PE_8_11, fifo_C_drain_PE_7_11 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_11, temp13, 256)
// // .invoke(Mmap2Stream_b, temp13, 256, out_board_13)
// .invoke( PE_wrapper, 7, 12, fifo_A_PE_7_12, fifo_A_PE_7_13, fifo_B_PE_7_12, fifo_B_PE_8_12, fifo_C_drain_PE_7_12 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_12, temp14, 256)
// // .invoke(Mmap2Stream_b, temp14, 256, out_board_14)
// .invoke( PE_wrapper, 7, 13, fifo_A_PE_7_13, fifo_A_PE_7_14, fifo_B_PE_7_13, fifo_B_PE_8_13, fifo_C_drain_PE_7_13 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_13, temp15, 256)
// // .invoke(Mmap2Stream_b, temp15, 256, out_board_15)
// .invoke( PE_wrapper, 7, 14, fifo_A_PE_7_14, fifo_A_PE_7_15, fifo_B_PE_7_14, fifo_B_PE_8_14, fifo_C_drain_PE_7_14 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_14, temp16, 256)
// // .invoke(Mmap2Stream_b, temp16, 256, out_board_16)
// .invoke( PE_wrapper, 7, 15, fifo_A_PE_7_15, fifo_A_PE_7_16, fifo_B_PE_7_15, fifo_B_PE_8_15, fifo_C_drain_PE_7_15 )
// .invoke(Stream2Mmap_b, fifo_B_PE_8_15, temp17, 256)
// .invoke(Mmap2Stream_b, temp17, 256, out_board_17)
// .invoke(Mmap2Stream_final, out_board, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17)
.invoke(Mmap2Stream_final, out_board, temp1, temp2, temp3, temp4, temp5, temp6, temp7)
.invoke( A_PE_dummy, 0, 5, fifo_A_PE_0_6 )
.invoke( A_PE_dummy, 1, 5, fifo_A_PE_1_6 )
.invoke( A_PE_dummy, 2, 5, fifo_A_PE_2_6 )
.invoke( A_PE_dummy, 3, 5, fifo_A_PE_3_6 )
.invoke( A_PE_dummy, 4, 5, fifo_A_PE_4_6 )
.invoke( A_PE_dummy, 5, 5, fifo_A_PE_5_6 )
.invoke( A_PE_dummy, 6, 5, fifo_A_PE_6_6 )
.invoke( A_PE_dummy, 7, 5, fifo_A_PE_7_6 )
.invoke(Stream2Mmap_final, in_board, itemp1, itemp2, itemp3, itemp4, itemp5, itemp6)
.invoke(Mmap2Stream_c, itemp1, 256, in_board_1)
// .invoke(Mmap2Stream_c, itemp2, 256, in_board_2)
// .invoke(Mmap2Stream_c, itemp3, 256, in_board_3)
// .invoke(Mmap2Stream_c, itemp4, 256, in_board_4)
// .invoke(Mmap2Stream_c, itemp5, 256, in_board_5)
// .invoke(Mmap2Stream_c, itemp6, 256, in_board_6)
// .invoke(Mmap2Stream_c, itemp7, 256, in_board_7)
.invoke(Mmap2Stream_c, itemp2, 256, in_board_8)
.invoke(Mmap2Stream_c, itemp3, 256, in_board_9)
.invoke(Mmap2Stream_c, itemp4, 256, in_board_10)
.invoke(Mmap2Stream_c, itemp5, 256, in_board_11)
.invoke(Mmap2Stream_c, itemp6, 256, in_board_12)
// .invoke(Mmap2Stream_c, itemp13, 256, in_board_13)
// .invoke(Mmap2Stream_c, itemp14, 256, in_board_14)
// .invoke(Mmap2Stream_c, itemp15, 256, in_board_15)
// .invoke(Mmap2Stream_c, itemp16, 256, in_board_16)
.invoke( C_drain_IO_L1_out,0,7,in_board_1,fifo_C_drain_C_drain_IO_L1_out_0_7,fifo_C_drain_PE_7_0 )
        .invoke( C_drain_IO_L1_out,0,6,fifo_C_drain_C_drain_IO_L1_out_0_7,fifo_C_drain_C_drain_IO_L1_out_0_6,fifo_C_drain_PE_6_0 )
        .invoke( C_drain_IO_L1_out,0,5,fifo_C_drain_C_drain_IO_L1_out_0_6,fifo_C_drain_C_drain_IO_L1_out_0_5,fifo_C_drain_PE_5_0 )
        .invoke( C_drain_IO_L1_out,0,4,fifo_C_drain_C_drain_IO_L1_out_0_5,fifo_C_drain_C_drain_IO_L1_out_0_4,fifo_C_drain_PE_4_0 )
        .invoke( C_drain_IO_L1_out,0,3,fifo_C_drain_C_drain_IO_L1_out_0_4,fifo_C_drain_C_drain_IO_L1_out_0_3,fifo_C_drain_PE_3_0 )
        .invoke( C_drain_IO_L1_out,0,2,fifo_C_drain_C_drain_IO_L1_out_0_3,fifo_C_drain_C_drain_IO_L1_out_0_2,fifo_C_drain_PE_2_0 )
        .invoke( C_drain_IO_L1_out,0,1,fifo_C_drain_C_drain_IO_L1_out_0_2,fifo_C_drain_C_drain_IO_L1_out_0_1,fifo_C_drain_PE_1_0 )
        .invoke( C_drain_IO_L1_out,0,0,fifo_C_drain_C_drain_IO_L1_out_0_1,fifo_C_drain_C_drain_IO_L1_out_0_0,fifo_C_drain_PE_0_0 )
        .invoke( C_drain_IO_L1_out,1,7,in_board_8,fifo_C_drain_C_drain_IO_L1_out_1_7,fifo_C_drain_PE_7_1 )
        .invoke( C_drain_IO_L1_out,1,6,fifo_C_drain_C_drain_IO_L1_out_1_7,fifo_C_drain_C_drain_IO_L1_out_1_6,fifo_C_drain_PE_6_1 )
        .invoke( C_drain_IO_L1_out,1,5,fifo_C_drain_C_drain_IO_L1_out_1_6,fifo_C_drain_C_drain_IO_L1_out_1_5,fifo_C_drain_PE_5_1 )
        .invoke( C_drain_IO_L1_out,1,4,fifo_C_drain_C_drain_IO_L1_out_1_5,fifo_C_drain_C_drain_IO_L1_out_1_4,fifo_C_drain_PE_4_1 )
        .invoke( C_drain_IO_L1_out,1,3,fifo_C_drain_C_drain_IO_L1_out_1_4,fifo_C_drain_C_drain_IO_L1_out_1_3,fifo_C_drain_PE_3_1 )
        .invoke( C_drain_IO_L1_out,1,2,fifo_C_drain_C_drain_IO_L1_out_1_3,fifo_C_drain_C_drain_IO_L1_out_1_2,fifo_C_drain_PE_2_1 )
        .invoke( C_drain_IO_L1_out,1,1,fifo_C_drain_C_drain_IO_L1_out_1_2,fifo_C_drain_C_drain_IO_L1_out_1_1,fifo_C_drain_PE_1_1 )
        .invoke( C_drain_IO_L1_out,1,0,fifo_C_drain_C_drain_IO_L1_out_1_1,fifo_C_drain_C_drain_IO_L1_out_1_0,fifo_C_drain_PE_0_1 )
        .invoke( C_drain_IO_L1_out,2,7,in_board_9,fifo_C_drain_C_drain_IO_L1_out_2_7,fifo_C_drain_PE_7_2 )
        .invoke( C_drain_IO_L1_out,2,6,fifo_C_drain_C_drain_IO_L1_out_2_7,fifo_C_drain_C_drain_IO_L1_out_2_6,fifo_C_drain_PE_6_2 )
        .invoke( C_drain_IO_L1_out,2,5,fifo_C_drain_C_drain_IO_L1_out_2_6,fifo_C_drain_C_drain_IO_L1_out_2_5,fifo_C_drain_PE_5_2 )
        .invoke( C_drain_IO_L1_out,2,4,fifo_C_drain_C_drain_IO_L1_out_2_5,fifo_C_drain_C_drain_IO_L1_out_2_4,fifo_C_drain_PE_4_2 )
        .invoke( C_drain_IO_L1_out,2,3,fifo_C_drain_C_drain_IO_L1_out_2_4,fifo_C_drain_C_drain_IO_L1_out_2_3,fifo_C_drain_PE_3_2 )
        .invoke( C_drain_IO_L1_out,2,2,fifo_C_drain_C_drain_IO_L1_out_2_3,fifo_C_drain_C_drain_IO_L1_out_2_2,fifo_C_drain_PE_2_2 )
        .invoke( C_drain_IO_L1_out,2,1,fifo_C_drain_C_drain_IO_L1_out_2_2,fifo_C_drain_C_drain_IO_L1_out_2_1,fifo_C_drain_PE_1_2 )
        .invoke( C_drain_IO_L1_out,2,0,fifo_C_drain_C_drain_IO_L1_out_2_1,fifo_C_drain_C_drain_IO_L1_out_2_0,fifo_C_drain_PE_0_2 )
        .invoke( C_drain_IO_L1_out,3,7,in_board_10,fifo_C_drain_C_drain_IO_L1_out_3_7,fifo_C_drain_PE_7_3 )
        .invoke( C_drain_IO_L1_out,3,6,fifo_C_drain_C_drain_IO_L1_out_3_7,fifo_C_drain_C_drain_IO_L1_out_3_6,fifo_C_drain_PE_6_3 )
        .invoke( C_drain_IO_L1_out,3,5,fifo_C_drain_C_drain_IO_L1_out_3_6,fifo_C_drain_C_drain_IO_L1_out_3_5,fifo_C_drain_PE_5_3 )
        .invoke( C_drain_IO_L1_out,3,4,fifo_C_drain_C_drain_IO_L1_out_3_5,fifo_C_drain_C_drain_IO_L1_out_3_4,fifo_C_drain_PE_4_3 )
        .invoke( C_drain_IO_L1_out,3,3,fifo_C_drain_C_drain_IO_L1_out_3_4,fifo_C_drain_C_drain_IO_L1_out_3_3,fifo_C_drain_PE_3_3 )
        .invoke( C_drain_IO_L1_out,3,2,fifo_C_drain_C_drain_IO_L1_out_3_3,fifo_C_drain_C_drain_IO_L1_out_3_2,fifo_C_drain_PE_2_3 )
        .invoke( C_drain_IO_L1_out,3,1,fifo_C_drain_C_drain_IO_L1_out_3_2,fifo_C_drain_C_drain_IO_L1_out_3_1,fifo_C_drain_PE_1_3 )
        .invoke( C_drain_IO_L1_out,3,0,fifo_C_drain_C_drain_IO_L1_out_3_1,fifo_C_drain_C_drain_IO_L1_out_3_0,fifo_C_drain_PE_0_3 )
         .invoke( C_drain_IO_L1_out,4,7,in_board_11,fifo_C_drain_C_drain_IO_L1_out_4_7,fifo_C_drain_PE_7_4 )
        .invoke( C_drain_IO_L1_out,4,6,fifo_C_drain_C_drain_IO_L1_out_4_7,fifo_C_drain_C_drain_IO_L1_out_4_6,fifo_C_drain_PE_6_4 )
        .invoke( C_drain_IO_L1_out,4,5,fifo_C_drain_C_drain_IO_L1_out_4_6,fifo_C_drain_C_drain_IO_L1_out_4_5,fifo_C_drain_PE_5_4 )
        .invoke( C_drain_IO_L1_out,4,4,fifo_C_drain_C_drain_IO_L1_out_4_5,fifo_C_drain_C_drain_IO_L1_out_4_4,fifo_C_drain_PE_4_4 )
        .invoke( C_drain_IO_L1_out,4,3,fifo_C_drain_C_drain_IO_L1_out_4_4,fifo_C_drain_C_drain_IO_L1_out_4_3,fifo_C_drain_PE_3_4 )
        .invoke( C_drain_IO_L1_out,4,2,fifo_C_drain_C_drain_IO_L1_out_4_3,fifo_C_drain_C_drain_IO_L1_out_4_2,fifo_C_drain_PE_2_4 )
        .invoke( C_drain_IO_L1_out,4,1,fifo_C_drain_C_drain_IO_L1_out_4_2,fifo_C_drain_C_drain_IO_L1_out_4_1,fifo_C_drain_PE_1_4 )
        .invoke( C_drain_IO_L1_out,4,0,fifo_C_drain_C_drain_IO_L1_out_4_1,fifo_C_drain_C_drain_IO_L1_out_4_0,fifo_C_drain_PE_0_4 )
        .invoke( C_drain_IO_L1_out,5,7,in_board_12,fifo_C_drain_C_drain_IO_L1_out_5_7,fifo_C_drain_PE_7_5 )
        .invoke( C_drain_IO_L1_out,5,6,fifo_C_drain_C_drain_IO_L1_out_5_7,fifo_C_drain_C_drain_IO_L1_out_5_6,fifo_C_drain_PE_6_5 )
        .invoke( C_drain_IO_L1_out,5,5,fifo_C_drain_C_drain_IO_L1_out_5_6,fifo_C_drain_C_drain_IO_L1_out_5_5,fifo_C_drain_PE_5_5 )
        .invoke( C_drain_IO_L1_out,5,4,fifo_C_drain_C_drain_IO_L1_out_5_5,fifo_C_drain_C_drain_IO_L1_out_5_4,fifo_C_drain_PE_4_5 )
        .invoke( C_drain_IO_L1_out,5,3,fifo_C_drain_C_drain_IO_L1_out_5_4,fifo_C_drain_C_drain_IO_L1_out_5_3,fifo_C_drain_PE_3_5 )
        .invoke( C_drain_IO_L1_out,5,2,fifo_C_drain_C_drain_IO_L1_out_5_3,fifo_C_drain_C_drain_IO_L1_out_5_2,fifo_C_drain_PE_2_5 )
        .invoke( C_drain_IO_L1_out,5,1,fifo_C_drain_C_drain_IO_L1_out_5_2,fifo_C_drain_C_drain_IO_L1_out_5_1,fifo_C_drain_PE_1_5 )
        .invoke( C_drain_IO_L1_out,5,0,fifo_C_drain_C_drain_IO_L1_out_5_1,fifo_C_drain_C_drain_IO_L1_out_5_0,fifo_C_drain_PE_0_5 )
        // .invoke( C_drain_IO_L1_out,6,7,in_board_13,fifo_C_drain_C_drain_IO_L1_out_6_7,fifo_C_drain_PE_7_6 )
        // .invoke( C_drain_IO_L1_out,6,6,fifo_C_drain_C_drain_IO_L1_out_6_7,fifo_C_drain_C_drain_IO_L1_out_6_6,fifo_C_drain_PE_6_6 )
        // .invoke( C_drain_IO_L1_out,6,5,fifo_C_drain_C_drain_IO_L1_out_6_6,fifo_C_drain_C_drain_IO_L1_out_6_5,fifo_C_drain_PE_5_6 )
        // .invoke( C_drain_IO_L1_out,6,4,fifo_C_drain_C_drain_IO_L1_out_6_5,fifo_C_drain_C_drain_IO_L1_out_6_4,fifo_C_drain_PE_4_6 )
        // .invoke( C_drain_IO_L1_out,6,3,fifo_C_drain_C_drain_IO_L1_out_6_4,fifo_C_drain_C_drain_IO_L1_out_6_3,fifo_C_drain_PE_3_6 )
        // .invoke( C_drain_IO_L1_out,6,2,fifo_C_drain_C_drain_IO_L1_out_6_3,fifo_C_drain_C_drain_IO_L1_out_6_2,fifo_C_drain_PE_2_6 )
        // .invoke( C_drain_IO_L1_out,6,1,fifo_C_drain_C_drain_IO_L1_out_6_2,fifo_C_drain_C_drain_IO_L1_out_6_1,fifo_C_drain_PE_1_6 )
        // .invoke( C_drain_IO_L1_out,6,0,fifo_C_drain_C_drain_IO_L1_out_6_1,fifo_C_drain_C_drain_IO_L1_out_6_0,fifo_C_drain_PE_0_6 )
        // .invoke( C_drain_IO_L1_out,7,7,in_board_14,fifo_C_drain_C_drain_IO_L1_out_7_7,fifo_C_drain_PE_7_7 )
        // .invoke( C_drain_IO_L1_out,7,6,fifo_C_drain_C_drain_IO_L1_out_7_7,fifo_C_drain_C_drain_IO_L1_out_7_6,fifo_C_drain_PE_6_7 )
        // .invoke( C_drain_IO_L1_out,7,5,fifo_C_drain_C_drain_IO_L1_out_7_6,fifo_C_drain_C_drain_IO_L1_out_7_5,fifo_C_drain_PE_5_7 )
        // .invoke( C_drain_IO_L1_out,7,4,fifo_C_drain_C_drain_IO_L1_out_7_5,fifo_C_drain_C_drain_IO_L1_out_7_4,fifo_C_drain_PE_4_7 )
        // .invoke( C_drain_IO_L1_out,7,3,fifo_C_drain_C_drain_IO_L1_out_7_4,fifo_C_drain_C_drain_IO_L1_out_7_3,fifo_C_drain_PE_3_7 )
        // .invoke( C_drain_IO_L1_out,7,2,fifo_C_drain_C_drain_IO_L1_out_7_3,fifo_C_drain_C_drain_IO_L1_out_7_2,fifo_C_drain_PE_2_7 )
        // .invoke( C_drain_IO_L1_out,7,1,fifo_C_drain_C_drain_IO_L1_out_7_2,fifo_C_drain_C_drain_IO_L1_out_7_1,fifo_C_drain_PE_1_7 )
        // .invoke( C_drain_IO_L1_out,7,0,fifo_C_drain_C_drain_IO_L1_out_7_1,fifo_C_drain_C_drain_IO_L1_out_7_0,fifo_C_drain_PE_0_7 )
        // .invoke( C_drain_IO_L1_out,8,7,in_board_15,fifo_C_drain_C_drain_IO_L1_out_8_7,fifo_C_drain_PE_7_8 )
        // .invoke( C_drain_IO_L1_out,8,6,fifo_C_drain_C_drain_IO_L1_out_8_7,fifo_C_drain_C_drain_IO_L1_out_8_6,fifo_C_drain_PE_6_8 )
        // .invoke( C_drain_IO_L1_out,8,5,fifo_C_drain_C_drain_IO_L1_out_8_6,fifo_C_drain_C_drain_IO_L1_out_8_5,fifo_C_drain_PE_5_8 )
        // .invoke( C_drain_IO_L1_out,8,4,fifo_C_drain_C_drain_IO_L1_out_8_5,fifo_C_drain_C_drain_IO_L1_out_8_4,fifo_C_drain_PE_4_8 )
        // .invoke( C_drain_IO_L1_out,8,3,fifo_C_drain_C_drain_IO_L1_out_8_4,fifo_C_drain_C_drain_IO_L1_out_8_3,fifo_C_drain_PE_3_8 )
        // .invoke( C_drain_IO_L1_out,8,2,fifo_C_drain_C_drain_IO_L1_out_8_3,fifo_C_drain_C_drain_IO_L1_out_8_2,fifo_C_drain_PE_2_8 )
        // .invoke( C_drain_IO_L1_out,8,1,fifo_C_drain_C_drain_IO_L1_out_8_2,fifo_C_drain_C_drain_IO_L1_out_8_1,fifo_C_drain_PE_1_8 )
        // .invoke( C_drain_IO_L1_out,8,0,fifo_C_drain_C_drain_IO_L1_out_8_1,fifo_C_drain_C_drain_IO_L1_out_8_0,fifo_C_drain_PE_0_8 )
        // .invoke( C_drain_IO_L1_out,9,7,in_board_16,fifo_C_drain_C_drain_IO_L1_out_9_7,fifo_C_drain_PE_7_9 )
        // .invoke( C_drain_IO_L1_out,9,6,fifo_C_drain_C_drain_IO_L1_out_9_7,fifo_C_drain_C_drain_IO_L1_out_9_6,fifo_C_drain_PE_6_9 )
        // .invoke( C_drain_IO_L1_out,9,5,fifo_C_drain_C_drain_IO_L1_out_9_6,fifo_C_drain_C_drain_IO_L1_out_9_5,fifo_C_drain_PE_5_9 )
        // .invoke( C_drain_IO_L1_out,9,4,fifo_C_drain_C_drain_IO_L1_out_9_5,fifo_C_drain_C_drain_IO_L1_out_9_4,fifo_C_drain_PE_4_9 )
        // .invoke( C_drain_IO_L1_out,9,3,fifo_C_drain_C_drain_IO_L1_out_9_4,fifo_C_drain_C_drain_IO_L1_out_9_3,fifo_C_drain_PE_3_9 )
        // .invoke( C_drain_IO_L1_out,9,2,fifo_C_drain_C_drain_IO_L1_out_9_3,fifo_C_drain_C_drain_IO_L1_out_9_2,fifo_C_drain_PE_2_9 )
        // .invoke( C_drain_IO_L1_out,9,1,fifo_C_drain_C_drain_IO_L1_out_9_2,fifo_C_drain_C_drain_IO_L1_out_9_1,fifo_C_drain_PE_1_9 )
        // .invoke( C_drain_IO_L1_out,9,0,fifo_C_drain_C_drain_IO_L1_out_9_1,fifo_C_drain_C_drain_IO_L1_out_9_0,fifo_C_drain_PE_0_9 )
        // .invoke( C_drain_IO_L1_out,10,7,in_board_2,fifo_C_drain_C_drain_IO_L1_out_10_7,fifo_C_drain_PE_7_10 )
        // .invoke( C_drain_IO_L1_out,10,6,fifo_C_drain_C_drain_IO_L1_out_10_7,fifo_C_drain_C_drain_IO_L1_out_10_6,fifo_C_drain_PE_6_10 )
        // .invoke( C_drain_IO_L1_out,10,5,fifo_C_drain_C_drain_IO_L1_out_10_6,fifo_C_drain_C_drain_IO_L1_out_10_5,fifo_C_drain_PE_5_10 )
        // .invoke( C_drain_IO_L1_out,10,4,fifo_C_drain_C_drain_IO_L1_out_10_5,fifo_C_drain_C_drain_IO_L1_out_10_4,fifo_C_drain_PE_4_10 )
        // .invoke( C_drain_IO_L1_out,10,3,fifo_C_drain_C_drain_IO_L1_out_10_4,fifo_C_drain_C_drain_IO_L1_out_10_3,fifo_C_drain_PE_3_10 )
        // .invoke( C_drain_IO_L1_out,10,2,fifo_C_drain_C_drain_IO_L1_out_10_3,fifo_C_drain_C_drain_IO_L1_out_10_2,fifo_C_drain_PE_2_10 )
        // .invoke( C_drain_IO_L1_out,10,1,fifo_C_drain_C_drain_IO_L1_out_10_2,fifo_C_drain_C_drain_IO_L1_out_10_1,fifo_C_drain_PE_1_10 )
        // .invoke( C_drain_IO_L1_out,10,0,fifo_C_drain_C_drain_IO_L1_out_10_1,fifo_C_drain_C_drain_IO_L1_out_10_0,fifo_C_drain_PE_0_10 )
        //  .invoke( C_drain_IO_L1_out,11,7,in_board_3,fifo_C_drain_C_drain_IO_L1_out_11_7,fifo_C_drain_PE_7_11 )
        // .invoke( C_drain_IO_L1_out,11,6,fifo_C_drain_C_drain_IO_L1_out_11_7,fifo_C_drain_C_drain_IO_L1_out_11_6,fifo_C_drain_PE_6_11 )
        // .invoke( C_drain_IO_L1_out,11,5,fifo_C_drain_C_drain_IO_L1_out_11_6,fifo_C_drain_C_drain_IO_L1_out_11_5,fifo_C_drain_PE_5_11 )
        // .invoke( C_drain_IO_L1_out,11,4,fifo_C_drain_C_drain_IO_L1_out_11_5,fifo_C_drain_C_drain_IO_L1_out_11_4,fifo_C_drain_PE_4_11 )
        // .invoke( C_drain_IO_L1_out,11,3,fifo_C_drain_C_drain_IO_L1_out_11_4,fifo_C_drain_C_drain_IO_L1_out_11_3,fifo_C_drain_PE_3_11 )
        // .invoke( C_drain_IO_L1_out,11,2,fifo_C_drain_C_drain_IO_L1_out_11_3,fifo_C_drain_C_drain_IO_L1_out_11_2,fifo_C_drain_PE_2_11 )
        // .invoke( C_drain_IO_L1_out,11,1,fifo_C_drain_C_drain_IO_L1_out_11_2,fifo_C_drain_C_drain_IO_L1_out_11_1,fifo_C_drain_PE_1_11 )
        // .invoke( C_drain_IO_L1_out,11,0,fifo_C_drain_C_drain_IO_L1_out_11_1,fifo_C_drain_C_drain_IO_L1_out_11_0,fifo_C_drain_PE_0_11 )
        // .invoke( C_drain_IO_L1_out,12,7,in_board_4,fifo_C_drain_C_drain_IO_L1_out_12_7,fifo_C_drain_PE_7_12 )
        // .invoke( C_drain_IO_L1_out,12,6,fifo_C_drain_C_drain_IO_L1_out_12_7,fifo_C_drain_C_drain_IO_L1_out_12_6,fifo_C_drain_PE_6_12 )
        // .invoke( C_drain_IO_L1_out,12,5,fifo_C_drain_C_drain_IO_L1_out_12_6,fifo_C_drain_C_drain_IO_L1_out_12_5,fifo_C_drain_PE_5_12 )
        // .invoke( C_drain_IO_L1_out,12,4,fifo_C_drain_C_drain_IO_L1_out_12_5,fifo_C_drain_C_drain_IO_L1_out_12_4,fifo_C_drain_PE_4_12 )
        // .invoke( C_drain_IO_L1_out,12,3,fifo_C_drain_C_drain_IO_L1_out_12_4,fifo_C_drain_C_drain_IO_L1_out_12_3,fifo_C_drain_PE_3_12 )
        // .invoke( C_drain_IO_L1_out,12,2,fifo_C_drain_C_drain_IO_L1_out_12_3,fifo_C_drain_C_drain_IO_L1_out_12_2,fifo_C_drain_PE_2_12 )
        // .invoke( C_drain_IO_L1_out,12,1,fifo_C_drain_C_drain_IO_L1_out_12_2,fifo_C_drain_C_drain_IO_L1_out_12_1,fifo_C_drain_PE_1_12 )
        // .invoke( C_drain_IO_L1_out,12,0,fifo_C_drain_C_drain_IO_L1_out_12_1,fifo_C_drain_C_drain_IO_L1_out_12_0,fifo_C_drain_PE_0_12 )
        // .invoke( C_drain_IO_L1_out,13,7,in_board_5,fifo_C_drain_C_drain_IO_L1_out_13_7,fifo_C_drain_PE_7_13 )
        // .invoke( C_drain_IO_L1_out,13,6,fifo_C_drain_C_drain_IO_L1_out_13_7,fifo_C_drain_C_drain_IO_L1_out_13_6,fifo_C_drain_PE_6_13 )
        // .invoke( C_drain_IO_L1_out,13,5,fifo_C_drain_C_drain_IO_L1_out_13_6,fifo_C_drain_C_drain_IO_L1_out_13_5,fifo_C_drain_PE_5_13 )
        // .invoke( C_drain_IO_L1_out,13,4,fifo_C_drain_C_drain_IO_L1_out_13_5,fifo_C_drain_C_drain_IO_L1_out_13_4,fifo_C_drain_PE_4_13 )
        // .invoke( C_drain_IO_L1_out,13,3,fifo_C_drain_C_drain_IO_L1_out_13_4,fifo_C_drain_C_drain_IO_L1_out_13_3,fifo_C_drain_PE_3_13 )
        // .invoke( C_drain_IO_L1_out,13,2,fifo_C_drain_C_drain_IO_L1_out_13_3,fifo_C_drain_C_drain_IO_L1_out_13_2,fifo_C_drain_PE_2_13 )
        // .invoke( C_drain_IO_L1_out,13,1,fifo_C_drain_C_drain_IO_L1_out_13_2,fifo_C_drain_C_drain_IO_L1_out_13_1,fifo_C_drain_PE_1_13 )
        // .invoke( C_drain_IO_L1_out,13,0,fifo_C_drain_C_drain_IO_L1_out_13_1,fifo_C_drain_C_drain_IO_L1_out_13_0,fifo_C_drain_PE_0_13 )
        // .invoke( C_drain_IO_L1_out,14,7,in_board_6,fifo_C_drain_C_drain_IO_L1_out_14_7,fifo_C_drain_PE_7_14 )
        // .invoke( C_drain_IO_L1_out,14,6,fifo_C_drain_C_drain_IO_L1_out_14_7,fifo_C_drain_C_drain_IO_L1_out_14_6,fifo_C_drain_PE_6_14 )
        // .invoke( C_drain_IO_L1_out,14,5,fifo_C_drain_C_drain_IO_L1_out_14_6,fifo_C_drain_C_drain_IO_L1_out_14_5,fifo_C_drain_PE_5_14 )
        // .invoke( C_drain_IO_L1_out,14,4,fifo_C_drain_C_drain_IO_L1_out_14_5,fifo_C_drain_C_drain_IO_L1_out_14_4,fifo_C_drain_PE_4_14 )
        // .invoke( C_drain_IO_L1_out,14,3,fifo_C_drain_C_drain_IO_L1_out_14_4,fifo_C_drain_C_drain_IO_L1_out_14_3,fifo_C_drain_PE_3_14 )
        // .invoke( C_drain_IO_L1_out,14,2,fifo_C_drain_C_drain_IO_L1_out_14_3,fifo_C_drain_C_drain_IO_L1_out_14_2,fifo_C_drain_PE_2_14 )
        // .invoke( C_drain_IO_L1_out,14,1,fifo_C_drain_C_drain_IO_L1_out_14_2,fifo_C_drain_C_drain_IO_L1_out_14_1,fifo_C_drain_PE_1_14 )
        // .invoke( C_drain_IO_L1_out,14,0,fifo_C_drain_C_drain_IO_L1_out_14_1,fifo_C_drain_C_drain_IO_L1_out_14_0,fifo_C_drain_PE_0_14 )
        // .invoke( C_drain_IO_L1_out,15,7,in_board_7,fifo_C_drain_C_drain_IO_L1_out_15_7,fifo_C_drain_PE_7_15 )
        // .invoke( C_drain_IO_L1_out,15,6,fifo_C_drain_C_drain_IO_L1_out_15_7,fifo_C_drain_C_drain_IO_L1_out_15_6,fifo_C_drain_PE_6_15 )
        // .invoke( C_drain_IO_L1_out,15,5,fifo_C_drain_C_drain_IO_L1_out_15_6,fifo_C_drain_C_drain_IO_L1_out_15_5,fifo_C_drain_PE_5_15 )
        // .invoke( C_drain_IO_L1_out,15,4,fifo_C_drain_C_drain_IO_L1_out_15_5,fifo_C_drain_C_drain_IO_L1_out_15_4,fifo_C_drain_PE_4_15 )
        // .invoke( C_drain_IO_L1_out,15,3,fifo_C_drain_C_drain_IO_L1_out_15_4,fifo_C_drain_C_drain_IO_L1_out_15_3,fifo_C_drain_PE_3_15 )
        // .invoke( C_drain_IO_L1_out,15,2,fifo_C_drain_C_drain_IO_L1_out_15_3,fifo_C_drain_C_drain_IO_L1_out_15_2,fifo_C_drain_PE_2_15 )
        // .invoke( C_drain_IO_L1_out,15,1,fifo_C_drain_C_drain_IO_L1_out_15_2,fifo_C_drain_C_drain_IO_L1_out_15_1,fifo_C_drain_PE_1_15 )
        // .invoke( C_drain_IO_L1_out,15,0,fifo_C_drain_C_drain_IO_L1_out_15_1,fifo_C_drain_C_drain_IO_L1_out_15_0,fifo_C_drain_PE_0_15 )
        // .invoke( C_drain_IO_L2_out_boundary,15,fifo_C_drain_C_drain_IO_L2_out_15,fifo_C_drain_C_drain_IO_L1_out_15_0 )
        // .invoke( C_drain_IO_L2_out,14,fifo_C_drain_C_drain_IO_L2_out_15,fifo_C_drain_C_drain_IO_L2_out_14,fifo_C_drain_C_drain_IO_L1_out_14_0 )
        // .invoke( C_drain_IO_L2_out,13,fifo_C_drain_C_drain_IO_L2_out_14,fifo_C_drain_C_drain_IO_L2_out_13,fifo_C_drain_C_drain_IO_L1_out_13_0 )
        // .invoke( C_drain_IO_L2_out,12,fifo_C_drain_C_drain_IO_L2_out_13,fifo_C_drain_C_drain_IO_L2_out_12,fifo_C_drain_C_drain_IO_L1_out_12_0 )
        // .invoke( C_drain_IO_L2_out,11,fifo_C_drain_C_drain_IO_L2_out_12,fifo_C_drain_C_drain_IO_L2_out_11,fifo_C_drain_C_drain_IO_L1_out_11_0 )
        // .invoke( C_drain_IO_L2_out,10,fifo_C_drain_C_drain_IO_L2_out_11,fifo_C_drain_C_drain_IO_L2_out_10,fifo_C_drain_C_drain_IO_L1_out_10_0 )
        // .invoke( C_drain_IO_L2_out,9,fifo_C_drain_C_drain_IO_L2_out_10,fifo_C_drain_C_drain_IO_L2_out_9,fifo_C_drain_C_drain_IO_L1_out_9_0 )
        // .invoke( C_drain_IO_L2_out,8,fifo_C_drain_C_drain_IO_L2_out_9,fifo_C_drain_C_drain_IO_L2_out_8,fifo_C_drain_C_drain_IO_L1_out_8_0 )
        // .invoke( C_drain_IO_L2_out,7,fifo_C_drain_C_drain_IO_L2_out_8,fifo_C_drain_C_drain_IO_L2_out_7,fifo_C_drain_C_drain_IO_L1_out_7_0 )
        // .invoke( C_drain_IO_L2_out,6,fifo_C_drain_C_drain_IO_L2_out_7,fifo_C_drain_C_drain_IO_L2_out_6,fifo_C_drain_C_drain_IO_L1_out_6_0 )
        .invoke( C_drain_IO_L2_out_boundary,5,fifo_C_drain_C_drain_IO_L2_out_5,fifo_C_drain_C_drain_IO_L1_out_5_0 )
        .invoke( C_drain_IO_L2_out,4,fifo_C_drain_C_drain_IO_L2_out_5,fifo_C_drain_C_drain_IO_L2_out_4,fifo_C_drain_C_drain_IO_L1_out_4_0 )
        .invoke( C_drain_IO_L2_out,3,fifo_C_drain_C_drain_IO_L2_out_4,fifo_C_drain_C_drain_IO_L2_out_3,fifo_C_drain_C_drain_IO_L1_out_3_0 )
        .invoke( C_drain_IO_L2_out,2,fifo_C_drain_C_drain_IO_L2_out_3,fifo_C_drain_C_drain_IO_L2_out_2,fifo_C_drain_C_drain_IO_L1_out_2_0 )
        .invoke( C_drain_IO_L2_out,1,fifo_C_drain_C_drain_IO_L2_out_2,fifo_C_drain_C_drain_IO_L2_out_1,fifo_C_drain_C_drain_IO_L1_out_1_0 )
        .invoke( C_drain_IO_L2_out,0,fifo_C_drain_C_drain_IO_L2_out_1,fifo_C_drain_C_drain_IO_L2_out_0,fifo_C_drain_C_drain_IO_L1_out_0_0 )
        .invoke( C_drain_IO_L3_out,C,fifo_C_drain_C_drain_IO_L2_out_0 )
;
}
// }