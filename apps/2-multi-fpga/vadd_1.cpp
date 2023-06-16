#include <cstdint>
#include "ap_int.h"
#include "ap_axi_sdata.h"
#include <tapa.h>

void Add(tapa::istream<float>& a, tapa::istream<float>& b,
         tapa::ostream<float>& c, uint64_t n) {
  for (uint64_t i = 0; i < n; ++i) {
    c << (a.read() + b.read());
  }
}

void Mmap2Stream(tapa::mmap<float> mmap, uint64_t n,
                 tapa::ostream<float>& stream) {
  for (uint64_t i = 0; i < n; ++i) {
    stream << mmap[i];
  }
}

void Stream2Mmap(tapa::istream<float>& stream, tapa::mmap<float> mmap,
                 uint64_t n) {
  for (uint64_t i = 0; i < n; ++i) {
    stream >> mmap[i];
  }
}

void VecAdd_1(tapa::mmap<float> a, tapa::mmap<float> b,
            tapa::mmap<float> c, uint64_t n, tapa::ostream<float> &out_board, tapa::istream<float> &in_board){
  tapa::stream<float> a_q("a");
  tapa::stream<float> b_q("b");
  tapa::stream<float> c_q("c");
  //tapa::mmap<float> c_hive("c_hive");
  tapa::task()
      .invoke(Mmap2Stream, a, n, a_q)
      .invoke(Mmap2Stream, b, n, b_q)
      .invoke(Add, a_q, b_q, c_q, n)
      .invoke(Stream2Mmap, c_q, c, n)
      .invoke(Mmap2Stream, c, n, out_board);
  
}

