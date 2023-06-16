#include <iostream>
#include <vector>
#include <gflags/gflags.h>
#include <tapa.h>
#include "AlvLink.h"
#include "/home/nehaprakriya/AlveoLink/network/roce_v2/sw/include/netLayer.hpp"
#include "genColHost.hpp"
#include "popl.hpp"
using std::clog;
using std::endl;
using std::vector;
using namespace std;
std::cout<<"hello"<<std::endl;
// void VecAdd(tapa::mmap<const float> a_array, tapa::mmap<const float> b_array,
//             tapa::mmap<float> c_array, uint64_t n);

// DEFINE_string(bitstream, "", "path to bitstream file, run csim if empty");

int main(int argc, char* argv[]) {
  // std::cout<<"hello";
  gflags::ParseCommandLineFlags(&argc, &argv, /*remove_flags=*/true);

  const uint64_t n = argc > 1 ? atoll(argv[1]) : 1024 * 1024;
  // std::cout<<"hello";
  vector<float> a(n);
  vector<float> b(n);
  vector<float> c(n);
  // read b externally using AlveoLink
  // Inputs: are array to which to read the data and the sender ID to read from.
  std::cout<<"hello";
  tapa::invoke(external_read, "hiveNetTest.xclbin", 2, 1, 2);
  // external_read(1, 1, 2);
  for (uint64_t i = 0; i < n; ++i) {
    a[i] = static_cast<float>(i);
    // b[i] = static_cast<float>(i) * 2;
    c[i] = 0.f;
  }
  /*
  int64_t kernel_time_ns = tapa::invoke(
      VecAdd, FLAGS_bitstream, tapa::read_only_mmap<const float>(a),
      tapa::read_only_mmap<const float>(b), tapa::write_only_mmap<float>(c), n);
  clog << "kernel time: " << kernel_time_ns * 1e-9 << " s" << endl;

  uint64_t num_errors = 0;
  const uint64_t threshold = 10;  // only report up to these errors
  for (uint64_t i = 0; i < n; ++i) {
    auto expected = i * 3;
    auto actual = static_cast<uint64_t>(c[i]);
    if (actual != expected) {
      if (num_errors < threshold) {
        clog << "expected: " << expected << ", actual: " << actual << endl;
      } else if (num_errors == threshold) {
        clog << "...";
      }
      ++num_errors;
    }
  }
  if (num_errors == 0) {
    clog << "PASS!" << endl;
  } else {
    if (num_errors > threshold) {
      clog << " (+" << (num_errors - threshold) << " more errors)" << endl;
    }
    clog << "FAIL!" << endl;
  }
  return num_errors > 0 ? 1 : 0;*/
}
