#include <cstdint>

#include <tapa.h>

void Add(tapa::istream<float>& a, tapa::istream<float>& b,
         tapa::ostream<float>& c, uint64_t n) {
  for (uint64_t i = 0; i < n; ++i) {
    c << (a.read() + b.read());
  }
}

void Mmap2Stream(tapa::mmap<const float> mmap, uint64_t n,
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

void VecAdd_2(
)
{
  tapa::stream<float> a_q("a");
  tapa::stream<float> b_q("b");
  tapa::stream<float> c_q("c");
tapa::task()
}