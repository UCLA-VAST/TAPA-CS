// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xknn.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XKnn_CfgInitialize(XKnn *InstancePtr, XKnn_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XKnn_Start(XKnn *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_AP_CTRL) & 0x80;
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XKnn_IsDone(XKnn *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XKnn_IsIdle(XKnn *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XKnn_IsReady(XKnn *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XKnn_EnableAutoRestart(XKnn *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XKnn_DisableAutoRestart(XKnn *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_AP_CTRL, 0);
}

void XKnn_Set_in_0(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_0_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_0_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_0(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_0_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_0_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_1(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_1_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_1_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_1(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_1_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_1_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_2(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_2_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_2_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_2(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_2_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_2_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_3(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_3_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_3_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_3(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_3_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_3_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_4(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_4_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_4_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_4(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_4_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_4_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_5(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_5_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_5_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_5(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_5_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_5_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_6(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_6_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_6_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_6(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_6_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_6_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_7(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_7_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_7_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_7(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_7_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_7_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_8(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_8_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_8_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_8(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_8_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_8_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_9(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_9_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_9_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_9(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_9_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_9_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_10(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_10_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_10_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_10(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_10_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_10_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_11(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_11_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_11_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_11(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_11_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_11_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_12(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_12_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_12_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_12(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_12_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_12_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_13(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_13_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_13_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_13(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_13_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_13_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_14(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_14_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_14_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_14(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_14_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_14_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_15(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_15_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_15_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_15(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_15_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_15_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_16(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_16_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_16_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_16(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_16_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_16_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_in_17(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_17_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_17_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_in_17(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_17_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IN_17_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_L3_out_dist(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_DIST_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_DIST_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_L3_out_dist(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_DIST_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_DIST_DATA + 4) << 32;
    return Data;
}

void XKnn_Set_L3_out_id(XKnn *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_ID_DATA, (u32)(Data));
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_ID_DATA + 4, (u32)(Data >> 32));
}

u64 XKnn_Get_L3_out_id(XKnn *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_ID_DATA);
    Data += (u64)XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_L3_OUT_ID_DATA + 4) << 32;
    return Data;
}

void XKnn_InterruptGlobalEnable(XKnn *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_GIE, 1);
}

void XKnn_InterruptGlobalDisable(XKnn *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_GIE, 0);
}

void XKnn_InterruptEnable(XKnn *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IER);
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IER, Register | Mask);
}

void XKnn_InterruptDisable(XKnn *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IER);
    XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IER, Register & (~Mask));
}

void XKnn_InterruptClear(XKnn *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    //XKnn_WriteReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_ISR, Mask);
}

u32 XKnn_InterruptGetEnabled(XKnn *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_IER);
}

u32 XKnn_InterruptGetStatus(XKnn *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    // Current Interrupt Clear Behavior is Clear on Read(COR).
    return XKnn_ReadReg(InstancePtr->Control_BaseAddress, XKNN_CONTROL_ADDR_ISR);
}

