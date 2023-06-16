#include <tapa.h>

void Mmap2Stream(uint64_t  mmap, uint64_t n,
                 tapa::ostream<tapa::vec_t<float, 2>>& stream) ;

void Stream2Mmap(tapa::istream<tapa::vec_t<float, 2>>& stream,
                 tapa::mmap<float> mmap) {
#pragma HLS disaggregate variable = stream
#pragma HLS interface ap_fifo port = stream._
#pragma HLS aggregate variable = stream._ bit
#pragma HLS interface ap_fifo port = stream._peek
#pragma HLS aggregate variable = stream._peek bit
void(stream._.empty());
void(stream._peek.empty());

#pragma HLS interface m_axi port = mmap offset = direct bundle = mmap

   for (uint64_t i = 0;;) {
#pragma HLS pipeline II = 2

    bool eot;
    if (stream.try_eot(eot)) {
      if (eot) break;
      auto packed = stream.read(nullptr);
      mmap[i * 2] = packed[0];
      mmap[i * 2 + 1] = packed[1];
      ++i;
    }
  }
}

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
