// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XKNN_H
#define XKNN_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xknn_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XKnn_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XKnn;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XKnn_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XKnn_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XKnn_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XKnn_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XKnn_Initialize(XKnn *InstancePtr, u16 DeviceId);
XKnn_Config* XKnn_LookupConfig(u16 DeviceId);
int XKnn_CfgInitialize(XKnn *InstancePtr, XKnn_Config *ConfigPtr);
#else
int XKnn_Initialize(XKnn *InstancePtr, const char* InstanceName);
int XKnn_Release(XKnn *InstancePtr);
#endif

void XKnn_Start(XKnn *InstancePtr);
u32 XKnn_IsDone(XKnn *InstancePtr);
u32 XKnn_IsIdle(XKnn *InstancePtr);
u32 XKnn_IsReady(XKnn *InstancePtr);
void XKnn_EnableAutoRestart(XKnn *InstancePtr);
void XKnn_DisableAutoRestart(XKnn *InstancePtr);

void XKnn_Set_in_0(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_0(XKnn *InstancePtr);
void XKnn_Set_in_1(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_1(XKnn *InstancePtr);
void XKnn_Set_in_2(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_2(XKnn *InstancePtr);
void XKnn_Set_in_3(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_3(XKnn *InstancePtr);
void XKnn_Set_in_4(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_4(XKnn *InstancePtr);
void XKnn_Set_in_5(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_5(XKnn *InstancePtr);
void XKnn_Set_in_6(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_6(XKnn *InstancePtr);
void XKnn_Set_in_7(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_7(XKnn *InstancePtr);
void XKnn_Set_in_8(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_8(XKnn *InstancePtr);
void XKnn_Set_in_9(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_9(XKnn *InstancePtr);
void XKnn_Set_in_10(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_10(XKnn *InstancePtr);
void XKnn_Set_in_11(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_11(XKnn *InstancePtr);
void XKnn_Set_in_12(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_12(XKnn *InstancePtr);
void XKnn_Set_in_13(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_13(XKnn *InstancePtr);
void XKnn_Set_in_14(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_14(XKnn *InstancePtr);
void XKnn_Set_in_15(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_15(XKnn *InstancePtr);
void XKnn_Set_in_16(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_16(XKnn *InstancePtr);
void XKnn_Set_in_17(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_in_17(XKnn *InstancePtr);
void XKnn_Set_L3_out_dist(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_L3_out_dist(XKnn *InstancePtr);
void XKnn_Set_L3_out_id(XKnn *InstancePtr, u64 Data);
u64 XKnn_Get_L3_out_id(XKnn *InstancePtr);

void XKnn_InterruptGlobalEnable(XKnn *InstancePtr);
void XKnn_InterruptGlobalDisable(XKnn *InstancePtr);
void XKnn_InterruptEnable(XKnn *InstancePtr, u32 Mask);
void XKnn_InterruptDisable(XKnn *InstancePtr, u32 Mask);
void XKnn_InterruptClear(XKnn *InstancePtr, u32 Mask);
u32 XKnn_InterruptGetEnabled(XKnn *InstancePtr);
u32 XKnn_InterruptGetStatus(XKnn *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
