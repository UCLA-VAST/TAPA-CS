#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>

#include <gflags/gflags.h>
#include "/home/ubuntu/tapa_m/src/tapa.h"
#include "DILATE.h"

// alveolink specific imports
#include <vector>
#include "genColHost.hpp"
#include "netLayer.hpp"
#include "popl.hpp"
#include "xNativeFPGA.hpp"
// #include "kernel_1.cpp"
using std::clog;
using std::endl;
using std::vector;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

extern "C"{
void unikernel(tapa::mmap<INTERFACE_WIDTH> in_0, tapa::mmap<INTERFACE_WIDTH> out_0, //HBM 0 1
                tapa::mmap<INTERFACE_WIDTH> in_1, tapa::mmap<INTERFACE_WIDTH> out_1, 
               tapa::mmap<INTERFACE_WIDTH> in_2, tapa::mmap<INTERFACE_WIDTH> out_2, 
               tapa::mmap<INTERFACE_WIDTH> in_3, tapa::mmap<INTERFACE_WIDTH> out_3, 
               tapa::mmap<INTERFACE_WIDTH> in_4, tapa::mmap<INTERFACE_WIDTH> out_4, 
               tapa::mmap<INTERFACE_WIDTH> in_5, tapa::mmap<INTERFACE_WIDTH> out_5, 
               tapa::mmap<INTERFACE_WIDTH> in_6, tapa::mmap<INTERFACE_WIDTH> out_6, 
               tapa::mmap<INTERFACE_WIDTH> in_7, tapa::mmap<INTERFACE_WIDTH> out_7,
               tapa::mmap<INTERFACE_WIDTH> temp, uint32_t iters
);
}
DEFINE_string(bitstream, "", "path to bitstream file, run csim if empty");

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, /*remove_flags=*/true);

  // alveolink setup begin:
  AlveoLink::common::FPGA fpga_card[2];
  fpga_card[0].setId(1);
  fpga_card[1].setId(2);
  AlveoLink::network_roce_v2::NetLayer<2> l_netLayer[2];
  std::cout<<"here"<<std::endl;
  for (auto i=0; i<2; ++i) {
    std::cout<<"in here?"<<std::endl;
    l_netLayer[i].init(&(fpga_card[i]));
    std::cout<<"init"<<std::endl;
    for (auto j=0; j<2; ++j) {
        std::cout<<"we reach inside"<<std::endl;
        l_netLayer[i].setIPSubnet(j, 0x0000a8c0);
        l_netLayer[i].setMACSubnet(j, 0x347844332211);
        l_netLayer[i].setID(j, i*2+j);
        std::cout<<"we reach here"<<std::endl;
        }
    }
  std::cout<<"setup the links on both"<<std::endl;
    for (auto i=0; i<2; ++i) {
        for (auto j=0; j<2; ++j) {
            std::cout <<"INFO: turn on RS_FEC for device " << i << " port " <<j << std::endl;
            l_netLayer[i].turnOn_RS_FEC(j, true);
        }
    }
    unsigned int l_totalDevLinksUp = 0;
    while (l_totalDevLinksUp < 2) {
        std::cout << "INFO: Waiting for links up on device " << l_totalDevLinksUp << std::endl;
        if (l_netLayer[l_totalDevLinksUp].linksUp()) {
            l_totalDevLinksUp++;
        }
    }

  srand (time(NULL));

  //Data initialization
  // const uint64_t n = argc > 1 ? atoll(argv[1]) : 1024 * 1024;
  printf("midle_region = %d\n", MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_0(MIDLE_REGION); vector<INTERFACE_WIDTH> out_0(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_1(MIDLE_REGION); vector<INTERFACE_WIDTH> out_1(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_2(MIDLE_REGION); vector<INTERFACE_WIDTH> out_2(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_3(MIDLE_REGION); vector<INTERFACE_WIDTH> out_3(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_4(MIDLE_REGION); vector<INTERFACE_WIDTH> out_4(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_5(MIDLE_REGION); vector<INTERFACE_WIDTH> out_5(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_6(MIDLE_REGION); vector<INTERFACE_WIDTH> out_6(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_7(MIDLE_REGION); vector<INTERFACE_WIDTH> out_7(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_8(MIDLE_REGION); vector<INTERFACE_WIDTH> out_8(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_9(MIDLE_REGION); vector<INTERFACE_WIDTH> out_9(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_10(MIDLE_REGION); vector<INTERFACE_WIDTH> out_10(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_11(MIDLE_REGION); vector<INTERFACE_WIDTH> out_11(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_12(MIDLE_REGION); vector<INTERFACE_WIDTH> out_12(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_13(MIDLE_REGION); vector<INTERFACE_WIDTH> out_13(MIDLE_REGION);
  vector<INTERFACE_WIDTH> in_14(MIDLE_REGION); vector<INTERFACE_WIDTH> out_14(MIDLE_REGION);
  // for (uint64_t i = 0; i < n; ++i) {
  //   a[i] = static_cast<float>(i);
  //   b[i] = static_cast<float>(i) * 2;
  //   c[i] = 0.f;
  // }
  //Software emulation vector
  float sw_in[MIDLE_REGION * WIDTH_FACTOR];
  float sw_out[MIDLE_REGION * WIDTH_FACTOR];

  // input test
  for(int i = 0; i < MIDLE_REGION; i++){
    INTERFACE_WIDTH a;
    float temp = rand() % 100 + 1;
    // float temp = (i * i) % 100;
    for(int k = 0; k < WIDTH_FACTOR; k++){
      unsigned int idx_k = k << 5;
      // float temp = (i * WIDTH_FACTOR + k);
      
      a.range(idx_k + 31, idx_k) =  *((uint32_t *)(&temp));
      sw_in[i * WIDTH_FACTOR + k] = temp;
    }
    in_0[i] = a; out_0[i] = a;
    in_1[i] = a; out_1[i] = a;
    in_2[i] = a; out_2[i] = a;
    in_3[i] = a; out_3[i] = a;
    in_4[i] = a; out_4[i] = a;
    in_5[i] = a; out_5[i] = a;
    in_6[i] = a; out_6[i] = a;
    in_7[i] = a; out_7[i] = a;
    in_8[i] = a; out_8[i] = a;
    in_9[i] = a; out_9[i] = a;
    in_10[i] = a; out_10[i] = a;
    in_11[i] = a; out_11[i] = a;
    in_12[i] = a; out_12[i] = a;
    in_13[i] = a; out_13[i] = a;
    in_14[i] = a; out_14[i] = a;
  }
  uint32_t iter = 1;

  // Software result

  // for(int i = 0; i < MIDLE_REGION * WIDTH_FACTOR; i++){
  //   sw_in[i] = i;
  // }

  for(uint32_t n = 0; n < iter; n++){
    for(uint32_t i = 1025; i < MIDLE_REGION * WIDTH_FACTOR - 1025; i++){
      sw_out[i] = (sw_in[i - 1024] + sw_in[i - 1025] + sw_in[i - 1023] + sw_in[i - 1] + sw_in[i] + sw_in[i + 1] + sw_in[i + 1023] + sw_in[i + 1] + sw_in[i + 1025]) /(float) 9;
    }
  }
  // std::cout << (GRID_COLS/WIDTH_FACTOR*PART_ROWS + (TOP_APPEND+BOTTOM_APPEND)*(1-1)) << endl;
  // std::cout << MIDLE_REGION << endl;

  std::cout << "kernel start" << endl;
  //Kernel execution
  auto start = high_resolution_clock::now();
  // tapa::invoke(VecAdd, FLAGS_bitstream, tapa::read_only_mmap<const float>(a),
  //              tapa::read_only_mmap<const float>(b),
  //              tapa::write_only_mmap<float>(c), n);
  // uint32_t iter=1
  tapa::invoke(unikernel, FLAGS_bitstream, 
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_0), tapa::read_write_mmap<INTERFACE_WIDTH>(out_0),
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_1), tapa::read_write_mmap<INTERFACE_WIDTH> (out_1), 
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_2), tapa::read_write_mmap<INTERFACE_WIDTH> (out_2), 
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_3), tapa::read_write_mmap<INTERFACE_WIDTH> (out_3), 
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_4), tapa::read_write_mmap<INTERFACE_WIDTH> (out_4), 
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_5), tapa::read_write_mmap<INTERFACE_WIDTH> (out_5), 
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_6), tapa::read_write_mmap<INTERFACE_WIDTH> (out_6), 
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_7), tapa::read_write_mmap<INTERFACE_WIDTH> (out_7), 
                // tapa::read_write_mmap<INTERFACE_WIDTH>(in_8), tapa::read_write_mmap<INTERFACE_WIDTH> (out_8), 
                // tapa::read_write_mmap<INTERFACE_WIDTH>(in_9), tapa::read_write_mmap<INTERFACE_WIDTH> (out_9), 
                // tapa::read_write_mmap<INTERFACE_WIDTH>(in_10), tapa::read_write_mmap<INTERFACE_WIDTH> (out_10), 
                // tapa::read_write_mmap<INTERFACE_WIDTH>(in_11), tapa::read_write_mmap<INTERFACE_WIDTH> (out_11),
                // tapa::read_write_mmap<INTERFACE_WIDTH>(in_12), tapa::read_write_mmap<INTERFACE_WIDTH> (out_12), 
                // tapa::read_write_mmap<INTERFACE_WIDTH>(in_13), tapa::read_write_mmap<INTERFACE_WIDTH> (out_13), 
                // tapa::read_write_mmap<INTERFACE_WIDTH>(in_14), tapa::read_write_mmap<INTERFACE_WIDTH> (out_14),
                tapa::read_write_mmap<INTERFACE_WIDTH>(in_14), iter
//                 , tapa::ostream<INTERFACE_WIDTH> &out_board,
// tapa::istream<INTERFACE_WIDTH> &in_board
);
  auto stop = high_resolution_clock::now();
  duration<double> elapsed = stop - start;
  clog << "elapsed time: " << elapsed.count() << "s" << endl;

  // Verification
  uint64_t num_errors = 0;
  const uint64_t threshold = 10;  // only report up to these errors
  for(int i = 66; i < 128; i++){
    for(int k = 0; k < WIDTH_FACTOR; k++){
      unsigned int idx_k = k << 5;
      uint32_t temp = out_0[i + 66].range(idx_k + 31, idx_k);
      float hw_result = (*((float*)(&temp)));
      if(sw_out[i * WIDTH_FACTOR + k] != hw_result){
        ++num_errors;
        std::cout << (i * WIDTH_FACTOR + k) << " " << hw_result << " " << sw_out[i * WIDTH_FACTOR + k] << endl;
      }
      // sstd::cout << (i * WIDTH_FACTOR + k) << " " << hw_result << " " << sw_out[i * WIDTH_FACTOR + k] << endl;
    }
  }
  // for (uint64_t i = 0; i < n; ++i) {
  //   auto expected = i * 3;
  //   auto actual = static_cast<uint64_t>(c[i]);
  //   if (actual != expected) {
  //     if (num_errors < threshold) {
  //       clog << "expected: " << expected << ", actual: " << actual << endl;
  //     } else if (num_errors == threshold) {
  //       clog << "...";
  //     }
  //     ++num_errors;
  //   }
  // }

  
  if (num_errors == 0) {
    clog << "PASS!" << endl;
  } else {
    if (num_errors > threshold) {
      clog << " (+" << (num_errors - threshold) << " more errors)" << endl;
    }
    clog << "FAIL!" << endl;
  }
  return num_errors > 0 ? 1 : 0;
}