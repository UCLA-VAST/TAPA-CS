#include <ap_int.h>
#include <tapa.h>

typedef ap_uint<512> A_t16;
typedef ap_uint<256> A_t8;
typedef ap_uint<512> B_t16;
typedef ap_uint<256> B_t8;
typedef ap_uint<512> C_t16;
typedef ap_uint<64> C_t2;

<<<<<<< HEAD

void Mmap2Stream_a(tapa::mmap<A_t8> mmap, uint64_t n,
                 tapa::ostream<A_t8>& stream) {
  for (uint64_t i = 0; i < n; ++i) {
    stream << mmap[i];
  }
}
void Stream2Mmap_a(tapa::istream<A_t8>& stream, tapa::mmap<A_t8> mmap,
                 uint64_t n) {
  for (uint64_t i = 0; i < n; ++i) {
    stream >> mmap[i];
  }
}

void Mmap2Stream_b(tapa::mmap<B_t8> mmap, uint64_t n,
                 tapa::ostream<B_t8>& stream) {
  for (uint64_t i = 0; i < n; ++i) {
    stream << mmap[i];
  }
}
void Stream2Mmap_b(tapa::istream<B_t8>& stream, tapa::mmap<B_t8> mmap,
                 uint64_t n) {
  for (uint64_t i = 0; i < n; ++i) {
    stream >> mmap[i];
  }
}

void Mmap2Stream_c(tapa::mmap<C_t2> mmap, uint64_t n,
                 tapa::ostream<C_t2>& stream) {
  for (uint64_t i = 0; i < n; ++i) {
    stream << mmap[i];
  }
}
void Stream2Mmap_c(tapa::istream<C_t2>& stream, tapa::mmap<C_t2> mmap,
                 uint64_t n) {
  for (uint64_t i = 0; i < n; ++i) {
    stream >> mmap[i];
  }
}


=======
>>>>>>> 7107e487dade8a32d831151f03e44facb01a21e7
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

extern "C" {
void kernel3_2(tapa::ostream<float> &out_board,
<<<<<<< HEAD
tapa::istream<A_t8> &in_board_1,
tapa::istream<B_t8> &in_board_2,
tapa::istream<B_t8> &in_board_3,
tapa::istream<B_t8> &in_board_4,
tapa::istream<B_t8> &in_board_5,
tapa::istream<B_t8> &in_board_6,
tapa::istream<B_t8> &in_board_7,
tapa::istream<B_t8> &in_board_8,
tapa::istream<B_t8> &in_board_9,
tapa::istream<B_t8> &in_board_10,
tapa::istream<B_t8> &in_board_11,
tapa::istream<B_t8> &in_board_12,
tapa::istream<B_t8> &in_board_13,
tapa::istream<B_t8> &in_board_14,
tapa::istream<B_t8> &in_board_15,
tapa::istream<B_t8> &in_board_16,
tapa::istream<B_t8> &in_board_17,
){
=======
tapa::istream<float> &in_board){
>>>>>>> 7107e487dade8a32d831151f03e44facb01a21e7
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
<<<<<<< HEAD
.invoke( A_IO_L2_in, 8, in_board_1, fifo_A_A_IO_L2_in_9, fifo_A_PE_8_0 )
.invoke( A_IO_L2_in, 9, fifo_A_A_IO_L2_in_9, fifo_A_A_IO_L2_in_10, fifo_A_PE_9_0 )
.invoke( A_IO_L2_in, 10, fifo_A_A_IO_L2_in_10, fifo_A_A_IO_L2_in_11, fifo_A_PE_10_0 )
.invoke( A_IO_L2_in, 11, fifo_A_A_IO_L2_in_11, fifo_A_A_IO_L2_in_12, fifo_A_PE_11_0 )
.invoke( A_IO_L2_in_boundary, 12, fifo_A_A_IO_L2_in_12, fifo_A_PE_12_0 )
.invoke( PE_wrapper, 8, 0, fifo_A_PE_8_0, fifo_A_PE_8_1, in_board_2, fifo_B_PE_9_0, fifo_C_drain_PE_8_0 )
.invoke( PE_wrapper, 8, 1, fifo_A_PE_8_1, fifo_A_PE_8_2, in_board_3, fifo_B_PE_9_1, fifo_C_drain_PE_8_1 )
.invoke( PE_wrapper, 8, 2, fifo_A_PE_8_2, fifo_A_PE_8_3, in_board_4, fifo_B_PE_9_2, fifo_C_drain_PE_8_2 )
.invoke( PE_wrapper, 8, 3, fifo_A_PE_8_3, fifo_A_PE_8_4, in_board_5, fifo_B_PE_9_3, fifo_C_drain_PE_8_3 )
.invoke( PE_wrapper, 8, 4, fifo_A_PE_8_4, fifo_A_PE_8_5, in_board_6, fifo_B_PE_9_4, fifo_C_drain_PE_8_4 )
.invoke( PE_wrapper, 8, 5, fifo_A_PE_8_5, fifo_A_PE_8_6, in_board_7, fifo_B_PE_9_5, fifo_C_drain_PE_8_5 )
.invoke( PE_wrapper, 8, 6, fifo_A_PE_8_6, fifo_A_PE_8_7, in_board_8, fifo_B_PE_9_6, fifo_C_drain_PE_8_6 )
.invoke( PE_wrapper, 8, 7, fifo_A_PE_8_7, fifo_A_PE_8_8, in_board_9, fifo_B_PE_9_7, fifo_C_drain_PE_8_7 )
.invoke( PE_wrapper, 8, 8, fifo_A_PE_8_8, fifo_A_PE_8_9, in_board_10, fifo_B_PE_9_8, fifo_C_drain_PE_8_8 )
.invoke( PE_wrapper, 8, 9, fifo_A_PE_8_9, fifo_A_PE_8_10, in_board_11, fifo_B_PE_9_9, fifo_C_drain_PE_8_9 )
.invoke( PE_wrapper, 8, 10, fifo_A_PE_8_10, fifo_A_PE_8_11, in_board_12, fifo_B_PE_9_10, fifo_C_drain_PE_8_10 )
.invoke( PE_wrapper, 8, 11, fifo_A_PE_8_11, fifo_A_PE_8_12, in_board_13, fifo_B_PE_9_11, fifo_C_drain_PE_8_11 )
.invoke( PE_wrapper, 8, 12, fifo_A_PE_8_12, fifo_A_PE_8_13, in_board_14, fifo_B_PE_9_12, fifo_C_drain_PE_8_12 )
.invoke( PE_wrapper, 8, 13, fifo_A_PE_8_13, fifo_A_PE_8_14, in_board_15, fifo_B_PE_9_13, fifo_C_drain_PE_8_13 )
.invoke( PE_wrapper, 8, 14, fifo_A_PE_8_14, fifo_A_PE_8_15, in_board_16, fifo_B_PE_9_14, fifo_C_drain_PE_8_14 )
.invoke( PE_wrapper, 8, 15, fifo_A_PE_8_15, fifo_A_PE_8_16, in_board_17, fifo_B_PE_9_15, fifo_C_drain_PE_8_15 )
.invoke( PE_wrapper, 9, 0, fifo_A_PE_9_0, fifo_A_PE_9_1, fifo_B_PE_9_0, fifo_B_PE_10_0, fifo_C_drain_PE_9_0 )
.invoke( PE_wrapper, 9, 1, fifo_A_PE_9_1, fifo_A_PE_9_2, fifo_B_PE_9_1, fifo_B_PE_10_1, fifo_C_drain_PE_9_1 )
.invoke( PE_wrapper, 9, 2, fifo_A_PE_9_2, fifo_A_PE_9_3, fifo_B_PE_9_2, fifo_B_PE_10_2, fifo_C_drain_PE_9_2 )
.invoke( PE_wrapper, 9, 3, fifo_A_PE_9_3, fifo_A_PE_9_4, fifo_B_PE_9_3, fifo_B_PE_10_3, fifo_C_drain_PE_9_3 )
.invoke( PE_wrapper, 9, 4, fifo_A_PE_9_4, fifo_A_PE_9_5, fifo_B_PE_9_4, fifo_B_PE_10_4, fifo_C_drain_PE_9_4 )
.invoke( PE_wrapper, 9, 5, fifo_A_PE_9_5, fifo_A_PE_9_6, fifo_B_PE_9_5, fifo_B_PE_10_5, fifo_C_drain_PE_9_5 )
.invoke( PE_wrapper, 9, 6, fifo_A_PE_9_6, fifo_A_PE_9_7, fifo_B_PE_9_6, fifo_B_PE_10_6, fifo_C_drain_PE_9_6 )
.invoke( PE_wrapper, 9, 7, fifo_A_PE_9_7, fifo_A_PE_9_8, fifo_B_PE_9_7, fifo_B_PE_10_7, fifo_C_drain_PE_9_7 )
.invoke( PE_wrapper, 9, 8, fifo_A_PE_9_8, fifo_A_PE_9_9, fifo_B_PE_9_8, fifo_B_PE_10_8, fifo_C_drain_PE_9_8 )
.invoke( PE_wrapper, 9, 9, fifo_A_PE_9_9, fifo_A_PE_9_10, fifo_B_PE_9_9, fifo_B_PE_10_9, fifo_C_drain_PE_9_9 )
.invoke( PE_wrapper, 9, 10, fifo_A_PE_9_10, fifo_A_PE_9_11, fifo_B_PE_9_10, fifo_B_PE_10_10, fifo_C_drain_PE_9_10 )
.invoke( PE_wrapper, 9, 11, fifo_A_PE_9_11, fifo_A_PE_9_12, fifo_B_PE_9_11, fifo_B_PE_10_11, fifo_C_drain_PE_9_11 )
.invoke( PE_wrapper, 9, 12, fifo_A_PE_9_12, fifo_A_PE_9_13, fifo_B_PE_9_12, fifo_B_PE_10_12, fifo_C_drain_PE_9_12 )
.invoke( PE_wrapper, 9, 13, fifo_A_PE_9_13, fifo_A_PE_9_14, fifo_B_PE_9_13, fifo_B_PE_10_13, fifo_C_drain_PE_9_13 )
.invoke( PE_wrapper, 9, 14, fifo_A_PE_9_14, fifo_A_PE_9_15, fifo_B_PE_9_14, fifo_B_PE_10_14, fifo_C_drain_PE_9_14 )
.invoke( PE_wrapper, 9, 15, fifo_A_PE_9_15, fifo_A_PE_9_16, fifo_B_PE_9_15, fifo_B_PE_10_15, fifo_C_drain_PE_9_15 )
.invoke( PE_wrapper, 10, 0, fifo_A_PE_10_0, fifo_A_PE_10_1, fifo_B_PE_10_0, fifo_B_PE_11_0, fifo_C_drain_PE_10_0 )
.invoke( PE_wrapper, 10, 1, fifo_A_PE_10_1, fifo_A_PE_10_2, fifo_B_PE_10_1, fifo_B_PE_11_1, fifo_C_drain_PE_10_1 )
.invoke( PE_wrapper, 10, 2, fifo_A_PE_10_2, fifo_A_PE_10_3, fifo_B_PE_10_2, fifo_B_PE_11_2, fifo_C_drain_PE_10_2 )
.invoke( PE_wrapper, 10, 3, fifo_A_PE_10_3, fifo_A_PE_10_4, fifo_B_PE_10_3, fifo_B_PE_11_3, fifo_C_drain_PE_10_3 )
.invoke( PE_wrapper, 10, 4, fifo_A_PE_10_4, fifo_A_PE_10_5, fifo_B_PE_10_4, fifo_B_PE_11_4, fifo_C_drain_PE_10_4 )
.invoke( PE_wrapper, 10, 5, fifo_A_PE_10_5, fifo_A_PE_10_6, fifo_B_PE_10_5, fifo_B_PE_11_5, fifo_C_drain_PE_10_5 )
.invoke( PE_wrapper, 10, 6, fifo_A_PE_10_6, fifo_A_PE_10_7, fifo_B_PE_10_6, fifo_B_PE_11_6, fifo_C_drain_PE_10_6 )
.invoke( PE_wrapper, 10, 7, fifo_A_PE_10_7, fifo_A_PE_10_8, fifo_B_PE_10_7, fifo_B_PE_11_7, fifo_C_drain_PE_10_7 )
.invoke( PE_wrapper, 10, 8, fifo_A_PE_10_8, fifo_A_PE_10_9, fifo_B_PE_10_8, fifo_B_PE_11_8, fifo_C_drain_PE_10_8 )
.invoke( PE_wrapper, 10, 9, fifo_A_PE_10_9, fifo_A_PE_10_10, fifo_B_PE_10_9, fifo_B_PE_11_9, fifo_C_drain_PE_10_9 )
.invoke( PE_wrapper, 10, 10, fifo_A_PE_10_10, fifo_A_PE_10_11, fifo_B_PE_10_10, fifo_B_PE_11_10, fifo_C_drain_PE_10_10 )
.invoke( PE_wrapper, 10, 11, fifo_A_PE_10_11, fifo_A_PE_10_12, fifo_B_PE_10_11, fifo_B_PE_11_11, fifo_C_drain_PE_10_11 )
.invoke( PE_wrapper, 10, 12, fifo_A_PE_10_12, fifo_A_PE_10_13, fifo_B_PE_10_12, fifo_B_PE_11_12, fifo_C_drain_PE_10_12 )
.invoke( PE_wrapper, 10, 13, fifo_A_PE_10_13, fifo_A_PE_10_14, fifo_B_PE_10_13, fifo_B_PE_11_13, fifo_C_drain_PE_10_13 )
.invoke( PE_wrapper, 10, 14, fifo_A_PE_10_14, fifo_A_PE_10_15, fifo_B_PE_10_14, fifo_B_PE_11_14, fifo_C_drain_PE_10_14 )
.invoke( PE_wrapper, 10, 15, fifo_A_PE_10_15, fifo_A_PE_10_16, fifo_B_PE_10_15, fifo_B_PE_11_15, fifo_C_drain_PE_10_15 )
.invoke( PE_wrapper, 11, 0, fifo_A_PE_11_0, fifo_A_PE_11_1, fifo_B_PE_11_0, fifo_B_PE_12_0, fifo_C_drain_PE_11_0 )
.invoke( PE_wrapper, 11, 1, fifo_A_PE_11_1, fifo_A_PE_11_2, fifo_B_PE_11_1, fifo_B_PE_12_1, fifo_C_drain_PE_11_1 )
.invoke( PE_wrapper, 11, 2, fifo_A_PE_11_2, fifo_A_PE_11_3, fifo_B_PE_11_2, fifo_B_PE_12_2, fifo_C_drain_PE_11_2 )
.invoke( PE_wrapper, 11, 3, fifo_A_PE_11_3, fifo_A_PE_11_4, fifo_B_PE_11_3, fifo_B_PE_12_3, fifo_C_drain_PE_11_3 )
.invoke( PE_wrapper, 11, 4, fifo_A_PE_11_4, fifo_A_PE_11_5, fifo_B_PE_11_4, fifo_B_PE_12_4, fifo_C_drain_PE_11_4 )
.invoke( PE_wrapper, 11, 5, fifo_A_PE_11_5, fifo_A_PE_11_6, fifo_B_PE_11_5, fifo_B_PE_12_5, fifo_C_drain_PE_11_5 )
.invoke( PE_wrapper, 11, 6, fifo_A_PE_11_6, fifo_A_PE_11_7, fifo_B_PE_11_6, fifo_B_PE_12_6, fifo_C_drain_PE_11_6 )
.invoke( PE_wrapper, 11, 7, fifo_A_PE_11_7, fifo_A_PE_11_8, fifo_B_PE_11_7, fifo_B_PE_12_7, fifo_C_drain_PE_11_7 )
.invoke( PE_wrapper, 11, 8, fifo_A_PE_11_8, fifo_A_PE_11_9, fifo_B_PE_11_8, fifo_B_PE_12_8, fifo_C_drain_PE_11_8 )
.invoke( PE_wrapper, 11, 9, fifo_A_PE_11_9, fifo_A_PE_11_10, fifo_B_PE_11_9, fifo_B_PE_12_9, fifo_C_drain_PE_11_9 )
.invoke( PE_wrapper, 11, 10, fifo_A_PE_11_10, fifo_A_PE_11_11, fifo_B_PE_11_10, fifo_B_PE_12_10, fifo_C_drain_PE_11_10 )
.invoke( PE_wrapper, 11, 11, fifo_A_PE_11_11, fifo_A_PE_11_12, fifo_B_PE_11_11, fifo_B_PE_12_11, fifo_C_drain_PE_11_11 )
.invoke( PE_wrapper, 11, 12, fifo_A_PE_11_12, fifo_A_PE_11_13, fifo_B_PE_11_12, fifo_B_PE_12_12, fifo_C_drain_PE_11_12 )
.invoke( PE_wrapper, 11, 13, fifo_A_PE_11_13, fifo_A_PE_11_14, fifo_B_PE_11_13, fifo_B_PE_12_13, fifo_C_drain_PE_11_13 )
.invoke( PE_wrapper, 11, 14, fifo_A_PE_11_14, fifo_A_PE_11_15, fifo_B_PE_11_14, fifo_B_PE_12_14, fifo_C_drain_PE_11_14 )
.invoke( PE_wrapper, 11, 15, fifo_A_PE_11_15, fifo_A_PE_11_16, fifo_B_PE_11_15, fifo_B_PE_12_15, fifo_C_drain_PE_11_15 )
.invoke( PE_wrapper, 12, 0, fifo_A_PE_12_0, fifo_A_PE_12_1, fifo_B_PE_12_0, fifo_B_PE_13_0, fifo_C_drain_PE_12_0 )
.invoke( PE_wrapper, 12, 1, fifo_A_PE_12_1, fifo_A_PE_12_2, fifo_B_PE_12_1, fifo_B_PE_13_1, fifo_C_drain_PE_12_1 )
.invoke( PE_wrapper, 12, 2, fifo_A_PE_12_2, fifo_A_PE_12_3, fifo_B_PE_12_2, fifo_B_PE_13_2, fifo_C_drain_PE_12_2 )
.invoke( PE_wrapper, 12, 3, fifo_A_PE_12_3, fifo_A_PE_12_4, fifo_B_PE_12_3, fifo_B_PE_13_3, fifo_C_drain_PE_12_3 )
.invoke( PE_wrapper, 12, 4, fifo_A_PE_12_4, fifo_A_PE_12_5, fifo_B_PE_12_4, fifo_B_PE_13_4, fifo_C_drain_PE_12_4 )
.invoke( PE_wrapper, 12, 5, fifo_A_PE_12_5, fifo_A_PE_12_6, fifo_B_PE_12_5, fifo_B_PE_13_5, fifo_C_drain_PE_12_5 )
.invoke( PE_wrapper, 12, 6, fifo_A_PE_12_6, fifo_A_PE_12_7, fifo_B_PE_12_6, fifo_B_PE_13_6, fifo_C_drain_PE_12_6 )
.invoke( PE_wrapper, 12, 7, fifo_A_PE_12_7, fifo_A_PE_12_8, fifo_B_PE_12_7, fifo_B_PE_13_7, fifo_C_drain_PE_12_7 )
.invoke( PE_wrapper, 12, 8, fifo_A_PE_12_8, fifo_A_PE_12_9, fifo_B_PE_12_8, fifo_B_PE_13_8, fifo_C_drain_PE_12_8 )
.invoke( PE_wrapper, 12, 9, fifo_A_PE_12_9, fifo_A_PE_12_10, fifo_B_PE_12_9, fifo_B_PE_13_9, fifo_C_drain_PE_12_9 )
.invoke( PE_wrapper, 12, 10, fifo_A_PE_12_10, fifo_A_PE_12_11, fifo_B_PE_12_10, fifo_B_PE_13_10, fifo_C_drain_PE_12_10 )
.invoke( PE_wrapper, 12, 11, fifo_A_PE_12_11, fifo_A_PE_12_12, fifo_B_PE_12_11, fifo_B_PE_13_11, fifo_C_drain_PE_12_11 )
.invoke( PE_wrapper, 12, 12, fifo_A_PE_12_12, fifo_A_PE_12_13, fifo_B_PE_12_12, fifo_B_PE_13_12, fifo_C_drain_PE_12_12 )
.invoke( PE_wrapper, 12, 13, fifo_A_PE_12_13, fifo_A_PE_12_14, fifo_B_PE_12_13, fifo_B_PE_13_13, fifo_C_drain_PE_12_13 )
.invoke( PE_wrapper, 12, 14, fifo_A_PE_12_14, fifo_A_PE_12_15, fifo_B_PE_12_14, fifo_B_PE_13_14, fifo_C_drain_PE_12_14 )
.invoke( PE_wrapper, 12, 15, fifo_A_PE_12_15, fifo_A_PE_12_16, fifo_B_PE_12_15, fifo_B_PE_13_15, fifo_C_drain_PE_12_15 )

.invoke( A_PE_dummy, 8, 15, fifo_A_PE_8_16 )
.invoke( A_PE_dummy, 9, 15, fifo_A_PE_9_16 )
.invoke( A_PE_dummy, 10, 15, fifo_A_PE_10_16 )
.invoke( A_PE_dummy, 11, 15, fifo_A_PE_11_16 )
.invoke( A_PE_dummy, 12, 15, fifo_A_PE_12_16 )
.invoke( B_PE_dummy, 12, 11, fifo_B_PE_13_11 )
.invoke( B_PE_dummy, 12, 12, fifo_B_PE_13_12 )
.invoke( B_PE_dummy, 12, 13, fifo_B_PE_13_13 )
.invoke( B_PE_dummy, 12, 14, fifo_B_PE_13_14 )
.invoke( B_PE_dummy, 12, 15, fifo_B_PE_13_15 )
.invoke( B_PE_dummy, 12, 0, fifo_B_PE_13_0 )
.invoke( B_PE_dummy, 12, 1, fifo_B_PE_13_1 )
.invoke( B_PE_dummy, 12, 2, fifo_B_PE_13_2 )
.invoke( B_PE_dummy, 12, 3, fifo_B_PE_13_3 )
.invoke( B_PE_dummy, 12, 4, fifo_B_PE_13_4 )
.invoke( B_PE_dummy, 12, 5, fifo_B_PE_13_5 )
.invoke( B_PE_dummy, 12, 6, fifo_B_PE_13_6 )
.invoke( B_PE_dummy, 12, 7, fifo_B_PE_13_7 )
.invoke( B_PE_dummy, 12, 8, fifo_B_PE_13_8 )
.invoke( B_PE_dummy, 12, 9, fifo_B_PE_13_9 )
.invoke( B_PE_dummy, 12, 10, fifo_B_PE_13_10 )
.invoke( C_drain_IO_L1_out_boundary,0,12,fifo_C_drain_C_drain_IO_L1_out_0_12,fifo_C_drain_PE_12_0 )
        .invoke( C_drain_IO_L1_out,0,11,fifo_C_drain_C_drain_IO_L1_out_0_12,fifo_C_drain_C_drain_IO_L1_out_0_11,fifo_C_drain_PE_11_0 )
        .invoke( C_drain_IO_L1_out,0,10,fifo_C_drain_C_drain_IO_L1_out_0_11,fifo_C_drain_C_drain_IO_L1_out_0_10,fifo_C_drain_PE_10_0 )
        .invoke( C_drain_IO_L1_out,0,9,fifo_C_drain_C_drain_IO_L1_out_0_10,fifo_C_drain_C_drain_IO_L1_out_0_9,fifo_C_drain_PE_9_0 )
        .invoke( C_drain_IO_L1_out,0,8,fifo_C_drain_C_drain_IO_L1_out_0_9,fifo_C_drain_C_drain_IO_L1_out_0_8,fifo_C_drain_PE_8_0 )
        .invoke(Stream2Mmap_c,fifo_C_drain_C_drain_IO_L1_out_0_8, temp1, 64)
        .invoke(Mmap2Stream_c, temp1, 64, out_board_1)
        .invoke( C_drain_IO_L1_out_boundary,1,12,fifo_C_drain_C_drain_IO_L1_out_1_12,fifo_C_drain_PE_12_1 )
        .invoke( C_drain_IO_L1_out,1,11,fifo_C_drain_C_drain_IO_L1_out_1_12,fifo_C_drain_C_drain_IO_L1_out_1_11,fifo_C_drain_PE_11_1 )
        .invoke( C_drain_IO_L1_out,1,10,fifo_C_drain_C_drain_IO_L1_out_1_11,fifo_C_drain_C_drain_IO_L1_out_1_10,fifo_C_drain_PE_10_1 )
        .invoke( C_drain_IO_L1_out,1,9,fifo_C_drain_C_drain_IO_L1_out_1_10,fifo_C_drain_C_drain_IO_L1_out_1_9,fifo_C_drain_PE_9_1 )
        .invoke( C_drain_IO_L1_out,1,8,fifo_C_drain_C_drain_IO_L1_out_1_9,fifo_C_drain_C_drain_IO_L1_out_1_8,fifo_C_drain_PE_8_1 )
        .invoke( C_drain_IO_L1_out_boundary,2,12,fifo_C_drain_C_drain_IO_L1_out_2_12,fifo_C_drain_PE_12_2 )
        .invoke( C_drain_IO_L1_out,2,11,fifo_C_drain_C_drain_IO_L1_out_2_12,fifo_C_drain_C_drain_IO_L1_out_2_11,fifo_C_drain_PE_11_2 )
        .invoke( C_drain_IO_L1_out,2,10,fifo_C_drain_C_drain_IO_L1_out_2_11,fifo_C_drain_C_drain_IO_L1_out_2_10,fifo_C_drain_PE_10_2 )
        .invoke( C_drain_IO_L1_out,2,9,fifo_C_drain_C_drain_IO_L1_out_2_10,fifo_C_drain_C_drain_IO_L1_out_2_9,fifo_C_drain_PE_9_2 )
        .invoke( C_drain_IO_L1_out,2,8,fifo_C_drain_C_drain_IO_L1_out_2_9,fifo_C_drain_C_drain_IO_L1_out_2_8,fifo_C_drain_PE_8_2 )
        .invoke( C_drain_IO_L1_out_boundary,3,12,fifo_C_drain_C_drain_IO_L1_out_3_12,fifo_C_drain_PE_12_3 )
        .invoke( C_drain_IO_L1_out,3,11,fifo_C_drain_C_drain_IO_L1_out_3_12,fifo_C_drain_C_drain_IO_L1_out_3_11,fifo_C_drain_PE_11_3 )
        .invoke( C_drain_IO_L1_out,3,10,fifo_C_drain_C_drain_IO_L1_out_3_11,fifo_C_drain_C_drain_IO_L1_out_3_10,fifo_C_drain_PE_10_3 )
        .invoke( C_drain_IO_L1_out,3,9,fifo_C_drain_C_drain_IO_L1_out_3_10,fifo_C_drain_C_drain_IO_L1_out_3_9,fifo_C_drain_PE_9_3 )
        .invoke( C_drain_IO_L1_out,3,8,fifo_C_drain_C_drain_IO_L1_out_3_9,fifo_C_drain_C_drain_IO_L1_out_3_8,fifo_C_drain_PE_8_3 )
        .invoke( C_drain_IO_L1_out_boundary,4,12,fifo_C_drain_C_drain_IO_L1_out_4_12,fifo_C_drain_PE_12_4 )
        .invoke( C_drain_IO_L1_out,4,11,fifo_C_drain_C_drain_IO_L1_out_4_12,fifo_C_drain_C_drain_IO_L1_out_4_11,fifo_C_drain_PE_11_4 )
        .invoke( C_drain_IO_L1_out,4,10,fifo_C_drain_C_drain_IO_L1_out_4_11,fifo_C_drain_C_drain_IO_L1_out_4_10,fifo_C_drain_PE_10_4 )
        .invoke( C_drain_IO_L1_out,4,9,fifo_C_drain_C_drain_IO_L1_out_4_10,fifo_C_drain_C_drain_IO_L1_out_4_9,fifo_C_drain_PE_9_4 )
        .invoke( C_drain_IO_L1_out,4,8,fifo_C_drain_C_drain_IO_L1_out_4_9,fifo_C_drain_C_drain_IO_L1_out_4_8,fifo_C_drain_PE_8_4 )
         .invoke( C_drain_IO_L1_out_boundary,5,12,fifo_C_drain_C_drain_IO_L1_out_5_12,fifo_C_drain_PE_12_5 )
        .invoke( C_drain_IO_L1_out,5,11,fifo_C_drain_C_drain_IO_L1_out_5_12,fifo_C_drain_C_drain_IO_L1_out_5_11,fifo_C_drain_PE_11_5 )
        .invoke( C_drain_IO_L1_out,5,10,fifo_C_drain_C_drain_IO_L1_out_5_11,fifo_C_drain_C_drain_IO_L1_out_5_10,fifo_C_drain_PE_10_5 )
        .invoke( C_drain_IO_L1_out,5,9,fifo_C_drain_C_drain_IO_L1_out_5_10,fifo_C_drain_C_drain_IO_L1_out_5_9,fifo_C_drain_PE_9_5 )
        .invoke( C_drain_IO_L1_out,5,8,fifo_C_drain_C_drain_IO_L1_out_5_9,fifo_C_drain_C_drain_IO_L1_out_5_8,fifo_C_drain_PE_8_5 )
        .invoke( C_drain_IO_L1_out_boundary,6,12,fifo_C_drain_C_drain_IO_L1_out_6_12,fifo_C_drain_PE_12_6 )
        .invoke( C_drain_IO_L1_out,6,11,fifo_C_drain_C_drain_IO_L1_out_6_12,fifo_C_drain_C_drain_IO_L1_out_6_11,fifo_C_drain_PE_11_6 )
        .invoke( C_drain_IO_L1_out,6,10,fifo_C_drain_C_drain_IO_L1_out_6_11,fifo_C_drain_C_drain_IO_L1_out_6_10,fifo_C_drain_PE_10_6 )
        .invoke( C_drain_IO_L1_out,6,9,fifo_C_drain_C_drain_IO_L1_out_6_10,fifo_C_drain_C_drain_IO_L1_out_6_9,fifo_C_drain_PE_9_6 )
        .invoke( C_drain_IO_L1_out,6,8,fifo_C_drain_C_drain_IO_L1_out_6_9,fifo_C_drain_C_drain_IO_L1_out_6_8,fifo_C_drain_PE_8_6 )
        .invoke( C_drain_IO_L1_out_boundary,7,12,fifo_C_drain_C_drain_IO_L1_out_7_12,fifo_C_drain_PE_12_7 )
        .invoke( C_drain_IO_L1_out,7,11,fifo_C_drain_C_drain_IO_L1_out_7_12,fifo_C_drain_C_drain_IO_L1_out_7_11,fifo_C_drain_PE_11_7 )
        .invoke( C_drain_IO_L1_out,7,10,fifo_C_drain_C_drain_IO_L1_out_7_11,fifo_C_drain_C_drain_IO_L1_out_7_10,fifo_C_drain_PE_10_7 )
        .invoke( C_drain_IO_L1_out,7,9,fifo_C_drain_C_drain_IO_L1_out_7_10,fifo_C_drain_C_drain_IO_L1_out_7_9,fifo_C_drain_PE_9_7 )
        .invoke( C_drain_IO_L1_out,7,8,fifo_C_drain_C_drain_IO_L1_out_7_9,fifo_C_drain_C_drain_IO_L1_out_7_8,fifo_C_drain_PE_8_7 )
        .invoke( C_drain_IO_L1_out_boundary,8,12,fifo_C_drain_C_drain_IO_L1_out_8_12,fifo_C_drain_PE_12_8 )
        .invoke( C_drain_IO_L1_out,8,11,fifo_C_drain_C_drain_IO_L1_out_8_12,fifo_C_drain_C_drain_IO_L1_out_8_11,fifo_C_drain_PE_11_8 )
        .invoke( C_drain_IO_L1_out,8,10,fifo_C_drain_C_drain_IO_L1_out_8_11,fifo_C_drain_C_drain_IO_L1_out_8_10,fifo_C_drain_PE_10_8 )
        .invoke( C_drain_IO_L1_out,8,9,fifo_C_drain_C_drain_IO_L1_out_8_10,fifo_C_drain_C_drain_IO_L1_out_8_9,fifo_C_drain_PE_9_8 )
        .invoke( C_drain_IO_L1_out,8,8,fifo_C_drain_C_drain_IO_L1_out_8_9,fifo_C_drain_C_drain_IO_L1_out_8_8,fifo_C_drain_PE_8_8 )
        .invoke( C_drain_IO_L1_out_boundary,9,12,fifo_C_drain_C_drain_IO_L1_out_9_12,fifo_C_drain_PE_12_9 )
        .invoke( C_drain_IO_L1_out,9,11,fifo_C_drain_C_drain_IO_L1_out_9_12,fifo_C_drain_C_drain_IO_L1_out_9_11,fifo_C_drain_PE_11_9 )
        .invoke( C_drain_IO_L1_out,9,10,fifo_C_drain_C_drain_IO_L1_out_9_11,fifo_C_drain_C_drain_IO_L1_out_9_10,fifo_C_drain_PE_10_9 )
        .invoke( C_drain_IO_L1_out,9,9,fifo_C_drain_C_drain_IO_L1_out_9_10,fifo_C_drain_C_drain_IO_L1_out_9_9,fifo_C_drain_PE_9_9 )
        .invoke( C_drain_IO_L1_out,9,8,fifo_C_drain_C_drain_IO_L1_out_9_9,fifo_C_drain_C_drain_IO_L1_out_9_8,fifo_C_drain_PE_8_9 )
        .invoke( C_drain_IO_L1_out_boundary,10,12,fifo_C_drain_C_drain_IO_L1_out_10_12,fifo_C_drain_PE_12_10 )
        .invoke( C_drain_IO_L1_out,10,11,fifo_C_drain_C_drain_IO_L1_out_10_12,fifo_C_drain_C_drain_IO_L1_out_10_11,fifo_C_drain_PE_11_10 )
        .invoke( C_drain_IO_L1_out,10,10,fifo_C_drain_C_drain_IO_L1_out_10_11,fifo_C_drain_C_drain_IO_L1_out_10_10,fifo_C_drain_PE_10_10 )
        .invoke( C_drain_IO_L1_out,10,9,fifo_C_drain_C_drain_IO_L1_out_10_10,fifo_C_drain_C_drain_IO_L1_out_10_9,fifo_C_drain_PE_9_10 )
        .invoke( C_drain_IO_L1_out,10,8,fifo_C_drain_C_drain_IO_L1_out_10_9,fifo_C_drain_C_drain_IO_L1_out_10_8,fifo_C_drain_PE_8_10 )
        .invoke( C_drain_IO_L1_out_boundary,11,12,fifo_C_drain_C_drain_IO_L1_out_11_12,fifo_C_drain_PE_12_11 )
        .invoke( C_drain_IO_L1_out,11,11,fifo_C_drain_C_drain_IO_L1_out_11_12,fifo_C_drain_C_drain_IO_L1_out_11_11,fifo_C_drain_PE_11_11 )
        .invoke( C_drain_IO_L1_out,11,10,fifo_C_drain_C_drain_IO_L1_out_11_11,fifo_C_drain_C_drain_IO_L1_out_11_10,fifo_C_drain_PE_10_11 )
        .invoke( C_drain_IO_L1_out,11,9,fifo_C_drain_C_drain_IO_L1_out_11_10,fifo_C_drain_C_drain_IO_L1_out_11_9,fifo_C_drain_PE_9_11 )
        .invoke( C_drain_IO_L1_out,11,8,fifo_C_drain_C_drain_IO_L1_out_11_9,fifo_C_drain_C_drain_IO_L1_out_11_8,fifo_C_drain_PE_8_11 )
        .invoke( C_drain_IO_L1_out_boundary,12,12,fifo_C_drain_C_drain_IO_L1_out_12_12,fifo_C_drain_PE_12_12 )
        .invoke( C_drain_IO_L1_out,12,11,fifo_C_drain_C_drain_IO_L1_out_12_12,fifo_C_drain_C_drain_IO_L1_out_12_11,fifo_C_drain_PE_11_12 )
        .invoke( C_drain_IO_L1_out,12,10,fifo_C_drain_C_drain_IO_L1_out_12_11,fifo_C_drain_C_drain_IO_L1_out_12_10,fifo_C_drain_PE_10_12 )
        .invoke( C_drain_IO_L1_out,12,9,fifo_C_drain_C_drain_IO_L1_out_12_10,fifo_C_drain_C_drain_IO_L1_out_12_9,fifo_C_drain_PE_9_12 )
        .invoke( C_drain_IO_L1_out,12,8,fifo_C_drain_C_drain_IO_L1_out_12_9,fifo_C_drain_C_drain_IO_L1_out_12_8,fifo_C_drain_PE_8_12 )
        .invoke( C_drain_IO_L1_out_boundary,13,12,fifo_C_drain_C_drain_IO_L1_out_13_12,fifo_C_drain_PE_12_13 )
        .invoke( C_drain_IO_L1_out,13,11,fifo_C_drain_C_drain_IO_L1_out_13_12,fifo_C_drain_C_drain_IO_L1_out_13_11,fifo_C_drain_PE_11_13 )
        .invoke( C_drain_IO_L1_out,13,10,fifo_C_drain_C_drain_IO_L1_out_13_11,fifo_C_drain_C_drain_IO_L1_out_13_10,fifo_C_drain_PE_10_13 )
        .invoke( C_drain_IO_L1_out,13,9,fifo_C_drain_C_drain_IO_L1_out_13_10,fifo_C_drain_C_drain_IO_L1_out_13_9,fifo_C_drain_PE_9_13 )
        .invoke( C_drain_IO_L1_out,13,8,fifo_C_drain_C_drain_IO_L1_out_13_9,fifo_C_drain_C_drain_IO_L1_out_13_8,fifo_C_drain_PE_8_13 )
        .invoke( C_drain_IO_L1_out_boundary,14,12,fifo_C_drain_C_drain_IO_L1_out_14_12,fifo_C_drain_PE_12_14 )
        .invoke( C_drain_IO_L1_out,14,11,fifo_C_drain_C_drain_IO_L1_out_14_12,fifo_C_drain_C_drain_IO_L1_out_14_11,fifo_C_drain_PE_11_14 )
        .invoke( C_drain_IO_L1_out,14,10,fifo_C_drain_C_drain_IO_L1_out_14_11,fifo_C_drain_C_drain_IO_L1_out_14_10,fifo_C_drain_PE_10_14 )
        .invoke( C_drain_IO_L1_out,14,9,fifo_C_drain_C_drain_IO_L1_out_14_10,fifo_C_drain_C_drain_IO_L1_out_14_9,fifo_C_drain_PE_9_14 )
        .invoke( C_drain_IO_L1_out,14,8,fifo_C_drain_C_drain_IO_L1_out_14_9,fifo_C_drain_C_drain_IO_L1_out_14_8,fifo_C_drain_PE_8_14 )
        .invoke( C_drain_IO_L1_out_boundary,15,12,fifo_C_drain_C_drain_IO_L1_out_15_12,fifo_C_drain_PE_12_15 )
        .invoke( C_drain_IO_L1_out,15,11,fifo_C_drain_C_drain_IO_L1_out_15_12,fifo_C_drain_C_drain_IO_L1_out_15_11,fifo_C_drain_PE_11_15 )
        .invoke( C_drain_IO_L1_out,15,10,fifo_C_drain_C_drain_IO_L1_out_15_11,fifo_C_drain_C_drain_IO_L1_out_15_10,fifo_C_drain_PE_10_15 )
        .invoke( C_drain_IO_L1_out,15,9,fifo_C_drain_C_drain_IO_L1_out_15_10,fifo_C_drain_C_drain_IO_L1_out_15_9,fifo_C_drain_PE_9_15 )
        .invoke( C_drain_IO_L1_out,15,8,fifo_C_drain_C_drain_IO_L1_out_15_9,fifo_C_drain_C_drain_IO_L1_out_15_8,fifo_C_drain_PE_8_15 )

;
}}
=======
;
}
>>>>>>> 7107e487dade8a32d831151f03e44facb01a21e7
