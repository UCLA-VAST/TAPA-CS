#include <tapa.h>

void Mmap2Stream(uint64_t  mmap, uint64_t n,
                 tapa::ostream<tapa::vec_t<float, 2>>& stream) ;

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
                 tapa::istream<float>& fifo_ld_1) {
#pragma HLS disaggregate variable = dram_t0_bank_0_fifo
#pragma HLS interface ap_fifo port = dram_t0_bank_0_fifo._
#pragma HLS aggregate variable = dram_t0_bank_0_fifo._ bit
void(dram_t0_bank_0_fifo._.full());

#pragma HLS disaggregate variable = fifo_ld_0
#pragma HLS interface ap_fifo port = fifo_ld_0._
#pragma HLS aggregate variable = fifo_ld_0._ bit
#pragma HLS interface ap_fifo port = fifo_ld_0._peek
#pragma HLS aggregate variable = fifo_ld_0._peek bit
void(fifo_ld_0._.empty());
void(fifo_ld_0._peek.empty());

#pragma HLS disaggregate variable = fifo_ld_1
#pragma HLS interface ap_fifo port = fifo_ld_1._
#pragma HLS aggregate variable = fifo_ld_1._ bit
#pragma HLS interface ap_fifo port = fifo_ld_1._peek
#pragma HLS aggregate variable = fifo_ld_1._peek bit
void(fifo_ld_1._.empty());
void(fifo_ld_1._peek.empty());

module_8_epoch:
  TAPA_WHILE_NEITHER_EOT(fifo_ld_0, fifo_ld_1) {
    tapa::vec_t<float, 2> tmp;
    tmp.set(0, fifo_ld_0.read(nullptr));
    tmp.set(1, fifo_ld_1.read(nullptr));
    dram_t0_bank_0_fifo.write(tmp);
  }
  dram_t0_bank_0_fifo.close();
}

void Jacobi(uint64_t  bank_0_t0, uint64_t  bank_0_t1,
            uint64_t coalesced_data_num) ;
