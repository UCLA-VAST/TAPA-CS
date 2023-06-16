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

using std::clog;
using std::endl;
using std::vector;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char* argv[])
{
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
  float sw_in[MIDLE_REGION * WIDTH_FACTOR];
  float sw_out[MIDLE_REGION * WIDTH_FACTOR];
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
  const uint32_t iter = 1;
    for(int n = 0; n < iter; n++){
    for(int i = 1025; i < MIDLE_REGION * WIDTH_FACTOR - 1025; i++){
      sw_out[i] = (sw_in[i - 1024] + sw_in[i - 1025] + sw_in[i - 1023] + sw_in[i - 1] + sw_in[i] + sw_in[i + 1] + sw_in[i + 1023] + sw_in[i + 1] + sw_in[i + 1025]) /(float) 9;
    }
  }
  
}

