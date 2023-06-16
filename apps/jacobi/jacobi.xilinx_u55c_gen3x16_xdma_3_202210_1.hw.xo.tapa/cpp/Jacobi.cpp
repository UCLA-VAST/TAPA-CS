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
                 tapa::istream<float>& fifo_ld_1) ;

extern "C" {

void Jacobi(uint64_t  bank_0_t0, uint64_t  bank_0_t1,
            uint64_t coalesced_data_num) {

#pragma HLS interface s_axilite port = bank_0_t0 bundle = control
{ auto val = reinterpret_cast<volatile uint8_t&>(bank_0_t0); }
{ auto val = reinterpret_cast<volatile uint8_t&>(bank_0_t0); }

#pragma HLS interface s_axilite port = bank_0_t1 bundle = control
{ auto val = reinterpret_cast<volatile uint8_t&>(bank_0_t1); }
{ auto val = reinterpret_cast<volatile uint8_t&>(bank_0_t1); }

#pragma HLS interface s_axilite port = coalesced_data_num bundle = control
{ auto val = reinterpret_cast<volatile uint8_t&>(coalesced_data_num); }


#pragma HLS interface s_axilite port = return bundle = control
}


}  // extern "C"

