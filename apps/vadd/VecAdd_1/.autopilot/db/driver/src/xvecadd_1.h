// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XVECADD_1_H
#define XVECADD_1_H

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
#include "xvecadd_1_hw.h"

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
} XVecadd_1_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XVecadd_1;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XVecadd_1_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XVecadd_1_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XVecadd_1_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XVecadd_1_ReadReg(BaseAddress, RegOffset) \
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
int XVecadd_1_Initialize(XVecadd_1 *InstancePtr, u16 DeviceId);
XVecadd_1_Config* XVecadd_1_LookupConfig(u16 DeviceId);
int XVecadd_1_CfgInitialize(XVecadd_1 *InstancePtr, XVecadd_1_Config *ConfigPtr);
#else
int XVecadd_1_Initialize(XVecadd_1 *InstancePtr, const char* InstanceName);
int XVecadd_1_Release(XVecadd_1 *InstancePtr);
#endif

void XVecadd_1_Start(XVecadd_1 *InstancePtr);
u32 XVecadd_1_IsDone(XVecadd_1 *InstancePtr);
u32 XVecadd_1_IsIdle(XVecadd_1 *InstancePtr);
u32 XVecadd_1_IsReady(XVecadd_1 *InstancePtr);
void XVecadd_1_EnableAutoRestart(XVecadd_1 *InstancePtr);
void XVecadd_1_DisableAutoRestart(XVecadd_1 *InstancePtr);

void XVecadd_1_Set_a(XVecadd_1 *InstancePtr, u64 Data);
u64 XVecadd_1_Get_a(XVecadd_1 *InstancePtr);
void XVecadd_1_Set_b(XVecadd_1 *InstancePtr, u64 Data);
u64 XVecadd_1_Get_b(XVecadd_1 *InstancePtr);
void XVecadd_1_Set_c(XVecadd_1 *InstancePtr, u64 Data);
u64 XVecadd_1_Get_c(XVecadd_1 *InstancePtr);
void XVecadd_1_Set_n(XVecadd_1 *InstancePtr, u64 Data);
u64 XVecadd_1_Get_n(XVecadd_1 *InstancePtr);

void XVecadd_1_InterruptGlobalEnable(XVecadd_1 *InstancePtr);
void XVecadd_1_InterruptGlobalDisable(XVecadd_1 *InstancePtr);
void XVecadd_1_InterruptEnable(XVecadd_1 *InstancePtr, u32 Mask);
void XVecadd_1_InterruptDisable(XVecadd_1 *InstancePtr, u32 Mask);
void XVecadd_1_InterruptClear(XVecadd_1 *InstancePtr, u32 Mask);
u32 XVecadd_1_InterruptGetEnabled(XVecadd_1 *InstancePtr);
u32 XVecadd_1_InterruptGetStatus(XVecadd_1 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
