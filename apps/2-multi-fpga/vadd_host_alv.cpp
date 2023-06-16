#include <iostream>
#include <vector>
#include <gflags/gflags.h>
#include <tapa.h>
#include "genColHost.hpp"
#include "netLayer.hpp"
#include "popl.hpp"
#include "xNativeFPGA.hpp"

using std::clog;
using std::endl;
using std::vector;

int main(int argc, char* argv[]){
    gflags::ParseCommandLineFlags(&argc, &argv, /*remove_flags=*/true);
    const uint64_t n = argc>1 ? atoll(argv[1]) : 1024*1024;
    std::string xclbin = "./vitis_run_hw/VecAdd_.xclbin";
    vector<float> a(n);
    vector<float> b(n);
    vector<float> c(n);
    for (uint64_t i = 0; i < n; ++i) {
    a[i] = static_cast<float>(i);
    b[i] = static_cast<float>(i) * 2;
    c[i] = 0.f;
    }
    // setup the fpga cards:
    AlveoLink::common::FPGA fpga_card[2];
    fpga_card[0].setId(1);
    fpga_card[1].setId(2);
    std::cout<<"loaded xclbin not yet"<<std::endl;
    fpga_card[0].load_xclbin("./vitis_run_hw/VecAdd_.xclbin");
    std::cout<<"loaded xclbin on one fpga"<<std::endl;
    fpga_card[1].load_xclbin("./vitis_run_hw/VecAdd_.xclbin");
    std::cout<<"loaded the second xclbin too"<<std::endl;
    // setup the links on both FPGAs
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
    // now run the codes on both FPGAs
    
    genColHost<2> l_genColHost[2];
    // l_genCol[2][2] keeps record of ID of the ports to check which is a sender and which is a receiever (1 if sender and 0 is receiver)
    unsigned int l_genCol[2][2];
    // l_id keeps record of ID for each of the ports on the FPGAs
    unsigned int l_id[2][2];
    unsigned int l_numPkts[2][2];
    for (auto i=0; i<2; ++i) {
        for (auto j=0; j<2; ++j) {
            // l_id[0][0] = 0 (port 1, FPGA 1), l_id[0][1] = 1 (port 2, FPGA 1), l_id[1][0]=2 (port 1, FPGA 2), l_id[1][1] (port 2, FPGA 2)= 3
            l_id[i][j] = i*2+j;
            // checking which port is a sender and which is a receiver and assigning ID to them (sender = 1 and receiver = 0)
            if (j==1) {
                // sender
                l_genCol[i][j] = 1;
            }
            else {
                // receiver
                l_genCol[i][j] = 0;
            }
            // packet_cnt was a user input to run the code, default = 32
            l_numPkts[i][j] = 32;
        }
    }
    // now run the vadd xclbin on both the fpgas and wait
    std::cout<<"we reach here"<<std::endl;
    for (auto i=0; i<2; ++i) {
        l_genColHost[i].init(&(fpga_card[i]));
        if (l_genCol[i][0] == 0) {
            // std::cout << "INFO: start collectors on device " << i << std::endl;
            l_genColHost[i].runCollectors(l_genCol[i], l_id[i], l_numPkts[i]);
        }
    }
    for (auto i=0; i<2; ++i) {
        if (l_genCol[i][0] == 1) {
            // std::cout << "INFO: start generators on device " << i << std::endl;
            l_genColHost[i].runGenerators(l_genCol[i], l_id[1-i], l_numPkts[i]);
        }
    }
    for (auto i=0; i<2; ++i) {
        l_genColHost[i].finish();
    }
    std::cout<<"did we finish"<<std::endl;
    return EXIT_SUCCESS;



}