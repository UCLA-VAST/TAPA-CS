#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cassert>
#include <ctime>
#include <stdint.h>
#include <bits/stdc++.h>
#include "netLayer.hpp"
#include "genColHost.hpp"
#include "popl.hpp"
#include "AlvLink.h"
// #include "/home/nehaprakriya/AlveoLink/common/sw/include/xNativeFPGA.hpp"

using namespace popl;
using namespace std::chrono;
void external_read(int n, int sender_id, int receiver_id){
    std::cout<<"hello";
    auto xclbin = "hiveNetTest.xclbin";
    auto packet_cnt = (n*4)/64;
    AlveoLink::common::FPGA fpga_card[2];
    fpga_card[0].setId(sender_id);
    fpga_card[1].setId(receiver_id);
    AlveoLink::network_roce_v2::NetLayer<2> l_netLayer[2];
    fpga_card[0].load_xclbin(xclbin);
    fpga_card[1].load_xclbin(xclbin);
    std::cout<<"reached here"<<std::endl;
    for (auto i=0;i<2;i++) {
        l_netLayer[i].init(&(fpga_card[i]));
        for (auto j=0; j<2; j++){
            l_netLayer[i].setIPSubnet(j, 0x0000a8c0);
            l_netLayer[i].setMACSubnet(j, 0x347844332211);
            l_netLayer[i].setID(j, i*2+j);
        }
    }
    for (auto i=0;i<2;i++){
        for (auto j=0;j<2;j++){
            l_netLayer[i].turnOn_RS_FEC(j, true);
        }
    }
    unsigned int l_totalDevLinksUp = 0;
    while (l_totalDevLinksUp < 2) {
        if (l_netLayer[l_totalDevLinksUp].linksUp()) {
            l_totalDevLinksUp++;
        }
    }
    genColHost<2> l_genColHost[2];
    
    unsigned int l_genCol[2][2];
    unsigned int l_id[2][2];
    unsigned int l_numPkts[2][2];
    for (auto i=0;i<2;i++) {
        for (auto j=0;j<2;j++){
            l_id[i][j]=i*2+j;
            if (sender_id == i){
                l_genCol[i][j] = 1;
            }
            else {
                l_genCol[i][j] = 0;
            }
            l_numPkts[i][j] = packet_cnt;
        }
    }
    for (auto i=0;i<2;i++){
        if (l_genCol[i][0]==0){
            l_genColHost[i].runCollectors(l_genCol[i], l_id[1-i], l_numPkts[i]);
            std::cout<<"hello";
        }
    }
}
// void external_read(int n, int sender_id, int receiver_id) {
//     std::cout<<"hello";
//     auto xclbin = "hiveNetTest.xclbin";
//     auto packet_cnt = (n*4)/64;
//     AlveoLink::common::FPGA fpga_card[2];
//     // other card
//     fpga_card[0].setId(sender_id);
//     // initial card with vadd
//     fpga_card[1].setId(receiver_id);
//     AlveoLink::network_roce_v2::NetLayer<2> l_netLayer[2];
//     fpga_card[0].load_xclbin(xclbin);
//     fpga_card[1].load_xclbin(xclbin);
//     for (auto i=0;i<2;i++) {
//         l_netLayer[i].init(&(fpga_card[i]));
//         for (auto j=0; j<2; j++){
//             l_netLayer[i].setIPSubnet(j, 0x0000a8c0);
//             l_netLayer[i].setMACSubnet(j, 0x347844332211);
//             l_netLayer[i].setID(j, i*2+j);
//         }
//     }
//     for (auto i=0;i<2;i++){
//         for (auto j=0;j<2;j++){
//             l_netLayer[i].turnOn_RS_FEC(j, true);
//         }
//     }
//     unsigned int l_totalDevLinksUp = 0;
//     while (l_totalDevLinksUp < 2) {
//         if (l_netLayer[l_totalDevLinksUp].linksUp()) {
//             l_totalDevLinksUp++;
//         }
//     }
//     genColHost<2> l_genColHost[2];
//     unsigned int l_genCol[2][2];
//     unsigned int l_id[2][2];
//     unsigned int l_numPkts[2][2];
//     for (auto i=0;i<2;i++) {
//         for (auto j=0;j<2;j++){
//             l_id[i][j]=i*2+j;
//             if (sender_id == i){
//                 l_genCol[i][j] = 1;
//             }
//             else {
//                 l_genCol[i][j] = 0;
//             }
//             l_numPkts[i][j] = packet_cnt;
//         }
//     }
//     for (auto i=0;i<2;i++){
//         if (l_genCol[i][0]==0){
//             l_genColHost[i].runCollectors(l_genCol[i], l_id[1-i], l_numPkts[i]);
//         }
//     }
//     for (auto i=0;i<2;i++){
//         if (l_genCol[i][0]==1){
//             l_genColHost[i].runGenerators(l_genCol[i], l_id[1-i], l_numPkts[i]);
//         }
//     }
//     for (auto i=0;i<2;i++){
//         l_genColHost[i].finish();
//     }
//     unsigned int l_errors[2];
//     for (auto i=0;i<2;i++){
//         if (l_genCol[i][0]==0){
//             l_genColHost[i].getErrors(l_errors);
//             for (auto j=0;j<2;j++){
//                 if (l_errors[j]!=0){
//                     std::cout<<"Errors collected"<<std::endl;
//                     // return EXIT_FAILURE;
//                 }
//             }
//         }
//     }
//     std::cout<<"Data transferred"<<std::endl;
//     // return EXIT_SUCCESS;
// }