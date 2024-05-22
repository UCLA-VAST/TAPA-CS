// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W_H__
#define __krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W_H__


#include <systemc>
using namespace sc_core;
using namespace sc_dt;




#include <iostream>
#include <fstream>

struct krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W_ram : public sc_core::sc_module {

  static const unsigned DataWidth = 32;
  static const unsigned AddressRange = 515;
  static const unsigned AddressWidth = 10;

//latency = 1
//input_reg = 1
//output_reg = 0
sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in <sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> we0;
sc_core::sc_in<sc_lv<DataWidth> > d0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


sc_lv<DataWidth> ram[AddressRange];


   SC_CTOR(krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W_ram) {


SC_METHOD(prc_write_0);
  sensitive<<clk.pos();
   }


void prc_write_0()
{
    if (ce0.read() == sc_dt::Log_1) 
    {
        if (we0.read() == sc_dt::Log_1) 
        {
           if(address0.read().is_01() && address0.read().to_uint()<AddressRange)
           {
              ram[address0.read().to_uint()] = d0.read(); 
              q0 = d0.read();
           }
           else
              q0 = sc_lv<DataWidth>();
        }
        else {
            if(address0.read().is_01() && address0.read().to_uint()<AddressRange)
              q0 = ram[address0.read().to_uint()];
            else
              q0 = sc_lv<DataWidth>();
        }
    }
}


}; //endmodule


SC_MODULE(krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W) {


static const unsigned DataWidth = 32;
static const unsigned AddressRange = 515;
static const unsigned AddressWidth = 10;

sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in<sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> we0;
sc_core::sc_in<sc_lv<DataWidth> > d0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W_ram* meminst;


SC_CTOR(krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W) {
meminst = new krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W_ram("krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W_ram");
meminst->address0(address0);
meminst->ce0(ce0);
meminst->q0(q0);
meminst->we0(we0);
meminst->d0(d0);


meminst->reset(reset);
meminst->clk(clk);
}
~krnl_partialKnn_wrapper_12_local_distance_0_A_RAM_AUTO_1R1W() {
    delete meminst;
}


};//endmodule
#endif
