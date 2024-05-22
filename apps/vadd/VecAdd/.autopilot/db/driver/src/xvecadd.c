// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xvecadd.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XVecadd_CfgInitialize(XVecadd *InstancePtr, XVecadd_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XVecadd_Start(XVecadd *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_AP_CTRL) & 0x80;
    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XVecadd_IsDone(XVecadd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XVecadd_IsIdle(XVecadd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XVecadd_IsReady(XVecadd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XVecadd_EnableAutoRestart(XVecadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XVecadd_DisableAutoRestart(XVecadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_AP_CTRL, 0);
}

void XVecadd_Set_a(XVecadd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_A_DATA, (u32)(Data));
    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_A_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_Get_a(XVecadd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_A_DATA);
    Data += (u64)XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_A_DATA + 4) << 32;
    return Data;
}

void XVecadd_Set_b(XVecadd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_B_DATA, (u32)(Data));
    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_B_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_Get_b(XVecadd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_B_DATA);
    Data += (u64)XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_B_DATA + 4) << 32;
    return Data;
}

void XVecadd_Set_c(XVecadd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_C_DATA, (u32)(Data));
    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_C_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_Get_c(XVecadd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_C_DATA);
    Data += (u64)XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_C_DATA + 4) << 32;
    return Data;
}

void XVecadd_Set_n(XVecadd *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_N_DATA, (u32)(Data));
    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_N_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_Get_n(XVecadd *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_N_DATA);
    Data += (u64)XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_N_DATA + 4) << 32;
    return Data;
}

void XVecadd_InterruptGlobalEnable(XVecadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_GIE, 1);
}

void XVecadd_InterruptGlobalDisable(XVecadd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_GIE, 0);
}

void XVecadd_InterruptEnable(XVecadd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_IER);
    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_IER, Register | Mask);
}

void XVecadd_InterruptDisable(XVecadd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_IER);
    XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_IER, Register & (~Mask));
}

void XVecadd_InterruptClear(XVecadd *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    //XVecadd_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_ISR, Mask);
}

u32 XVecadd_InterruptGetEnabled(XVecadd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_IER);
}

u32 XVecadd_InterruptGetStatus(XVecadd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    // Current Interrupt Clear Behavior is Clear on Read(COR).
    return XVecadd_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_CONTROL_ADDR_ISR);
}

