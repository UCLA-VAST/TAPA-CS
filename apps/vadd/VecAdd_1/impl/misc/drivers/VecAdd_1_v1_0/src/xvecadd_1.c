// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xvecadd_1.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XVecadd_1_CfgInitialize(XVecadd_1 *InstancePtr, XVecadd_1_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XVecadd_1_Start(XVecadd_1 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_AP_CTRL) & 0x80;
    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XVecadd_1_IsDone(XVecadd_1 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XVecadd_1_IsIdle(XVecadd_1 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XVecadd_1_IsReady(XVecadd_1 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XVecadd_1_EnableAutoRestart(XVecadd_1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XVecadd_1_DisableAutoRestart(XVecadd_1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_AP_CTRL, 0);
}

void XVecadd_1_Set_a(XVecadd_1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_A_DATA, (u32)(Data));
    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_A_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_1_Get_a(XVecadd_1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_A_DATA);
    Data += (u64)XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_A_DATA + 4) << 32;
    return Data;
}

void XVecadd_1_Set_b(XVecadd_1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_B_DATA, (u32)(Data));
    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_B_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_1_Get_b(XVecadd_1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_B_DATA);
    Data += (u64)XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_B_DATA + 4) << 32;
    return Data;
}

void XVecadd_1_Set_c(XVecadd_1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_C_DATA, (u32)(Data));
    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_C_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_1_Get_c(XVecadd_1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_C_DATA);
    Data += (u64)XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_C_DATA + 4) << 32;
    return Data;
}

void XVecadd_1_Set_n(XVecadd_1 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_N_DATA, (u32)(Data));
    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_N_DATA + 4, (u32)(Data >> 32));
}

u64 XVecadd_1_Get_n(XVecadd_1 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_N_DATA);
    Data += (u64)XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_N_DATA + 4) << 32;
    return Data;
}

void XVecadd_1_InterruptGlobalEnable(XVecadd_1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_GIE, 1);
}

void XVecadd_1_InterruptGlobalDisable(XVecadd_1 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_GIE, 0);
}

void XVecadd_1_InterruptEnable(XVecadd_1 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_IER);
    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_IER, Register | Mask);
}

void XVecadd_1_InterruptDisable(XVecadd_1 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_IER);
    XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_IER, Register & (~Mask));
}

void XVecadd_1_InterruptClear(XVecadd_1 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    //XVecadd_1_WriteReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_ISR, Mask);
}

u32 XVecadd_1_InterruptGetEnabled(XVecadd_1 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_IER);
}

u32 XVecadd_1_InterruptGetStatus(XVecadd_1 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    // Current Interrupt Clear Behavior is Clear on Read(COR).
    return XVecadd_1_ReadReg(InstancePtr->Control_BaseAddress, XVECADD_1_CONTROL_ADDR_ISR);
}

