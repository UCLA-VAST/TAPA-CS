// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XVECADD_H
#define XVECADD_H

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
#include "xvecadd_hw.h"

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
} XVecadd_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XVecadd;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XVecadd_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XVecadd_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XVecadd_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XVecadd_ReadReg(BaseAddress, RegOffset) \
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
int XVecadd_Initialize(XVecadd *InstancePtr, u16 DeviceId);
XVecadd_Config* XVecadd_LookupConfig(u16 DeviceId);
int XVecadd_CfgInitialize(XVecadd *InstancePtr, XVecadd_Config *ConfigPtr);
#else
int XVecadd_Initialize(XVecadd *InstancePtr, const char* InstanceName);
int XVecadd_Release(XVecadd *InstancePtr);
#endif

void XVecadd_Start(XVecadd *InstancePtr);
u32 XVecadd_IsDone(XVecadd *InstancePtr);
u32 XVecadd_IsIdle(XVecadd *InstancePtr);
u32 XVecadd_IsReady(XVecadd *InstancePtr);
void XVecadd_EnableAutoRestart(XVecadd *InstancePtr);
void XVecadd_DisableAutoRestart(XVecadd *InstancePtr);

void XVecadd_Set_a(XVecadd *InstancePtr, u64 Data);
u64 XVecadd_Get_a(XVecadd *InstancePtr);
void XVecadd_Set_b(XVecadd *InstancePtr, u64 Data);
u64 XVecadd_Get_b(XVecadd *InstancePtr);
void XVecadd_Set_c(XVecadd *InstancePtr, u64 Data);
u64 XVecadd_Get_c(XVecadd *InstancePtr);
void XVecadd_Set_n(XVecadd *InstancePtr, u64 Data);
u64 XVecadd_Get_n(XVecadd *InstancePtr);

void XVecadd_InterruptGlobalEnable(XVecadd *InstancePtr);
void XVecadd_InterruptGlobalDisable(XVecadd *InstancePtr);
void XVecadd_InterruptEnable(XVecadd *InstancePtr, u32 Mask);
void XVecadd_InterruptDisable(XVecadd *InstancePtr, u32 Mask);
void XVecadd_InterruptClear(XVecadd *InstancePtr, u32 Mask);
u32 XVecadd_InterruptGetEnabled(XVecadd *InstancePtr);
u32 XVecadd_InterruptGetStatus(XVecadd *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
