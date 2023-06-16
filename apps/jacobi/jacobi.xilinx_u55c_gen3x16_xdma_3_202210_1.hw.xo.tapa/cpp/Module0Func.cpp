#include <tapa.h>

void Mmap2Stream(uint64_t  mmap, uint64_t n,
                 tapa::ostream<tapa::vec_t<float, 2>>& stream) ;

void Stream2Mmap(tapa::istream<tapa::vec_t<float, 2>>& stream,
                 uint64_t  mmap) ;

void Module0Func(tapa::ostream<float>& fifo_st_0,
                 tapa::ostream<float>& fifo_st_1,
                 tapa::istream<tapa::vec_t<float, 2>>& dram_t1_bank_0_fifo) {
#pragma HLS disaggregate variable = fifo_st_0
#pragma HLS interface ap_fifo port = fifo_st_0._
#pragma HLS aggregate variable = fifo_st_0._ bit
void(fifo_st_0._.full());

#pragma HLS disaggregate variable = fifo_st_1
#pragma HLS interface ap_fifo port = fifo_st_1._
#pragma HLS aggregate variable = fifo_st_1._ bit
void(fifo_st_1._.full());

#pragma HLS disaggregate variable = dram_t1_bank_0_fifo
#pragma HLS interface ap_fifo port = dram_t1_bank_0_fifo._
#pragma HLS aggregate variable = dram_t1_bank_0_fifo._ bit
#pragma HLS interface ap_fifo port = dram_t1_bank_0_fifo._peek
#pragma HLS aggregate variable = dram_t1_bank_0_fifo._peek bit
void(dram_t1_bank_0_fifo._.empty());
void(dram_t1_bank_0_fifo._peek.empty());

module_0_epoch:
  TAPA_WHILE_NOT_EOT(dram_t1_bank_0_fifo) {
    auto dram_t1_bank_0_buf = dram_t1_bank_0_fifo.read(nullptr);
    fifo_st_0.write(dram_t1_bank_0_buf[1]);
    fifo_st_1.write(dram_t1_bank_0_buf[0]);
  }
  fifo_st_0.close();
  fifo_st_1.close();
}

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
