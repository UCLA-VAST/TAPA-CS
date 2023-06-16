#include <tapa.h>

void Mmap2Stream(tapa::mmap<const float> mmap, uint64_t n,
                 tapa::ostream<tapa::vec_t<float, 2>>& stream) {
#pragma HLS interface m_axi port = mmap offset = direct bundle = mmap


#pragma HLS disaggregate variable = stream
#pragma HLS interface ap_fifo port = stream._
#pragma HLS aggregate variable = stream._ bit
void(stream._.full());

   for (uint64_t i = 0; i < n; ++i) {
#pragma HLS pipeline II = 2

    tapa::vec_t<float, 2> tmp;
    tmp.set(0, mmap[i * 2]);
    tmp.set(1, mmap[i * 2 + 1]);
    stream.write(tmp);
  }
  stream.close();
}

void Stream2Mmap(tapa::istream<tapa::vec_t<float, 2>>& stream,
                 uint64_t  mmap) ;

void Module0Func(tapa::ostream<float>& fifo_st_0,
                 tapa::ostream<float>& fifo_st_1,
                 tapa::istream<tapa::vec_t<float, 2>>& dram_t1_bank_0_fifo) ;

void Module1Func(tapa::ostream<float>& fifo_st_0,
                 tapa::ostream<float>& fifo_st_1,
                 tapa::istream<float>& fifo_ld_0) ;

void Module3Func1(tapa::ostream<float>& fifo_st_0,
                  tapa::istream<float>& fifo_ld_0,
                  tapa::istream<float>& fifo_ld_1) ;

void Module3Func2(tapa::ostream<float>& fifo_st_0,
                  tapa::istream<float>& fifo_ld_0,
                  tapa::istream<float>& fifo_ld_1) ;

void Module6Func1(tapa::ostream<float>& fifo_st_0,
                  tapa::istream<float>& fifo_ld_0,
                  tapa::istream<float>& fifo_ld_1,
                  tapa::istream<float>& fifo_ld_2) ;
void Module6Func2(tapa::ostream<float>& fifo_st_0,
                  tapa::istream<float>& fifo_ld_0,
                  tapa::istream<float>& fifo_ld_1,
                  tapa::istream<float>& fifo_ld_2) ;

void Module8Func(tapa::ostream<tapa::vec_t<float, 2>>& dram_t0_bank_0_fifo,
                 tapa::istream<float>& fifo_ld_0,
                 tapa::istream<float>& fifo_ld_1) ;

void Jacobi(uint64_t  bank_0_t0, uint64_t  bank_0_t1,
            uint64_t coalesced_data_num) ;
