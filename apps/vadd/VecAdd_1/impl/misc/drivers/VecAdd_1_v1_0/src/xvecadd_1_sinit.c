// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xvecadd_1.h"

extern XVecadd_1_Config XVecadd_1_ConfigTable[];

XVecadd_1_Config *XVecadd_1_LookupConfig(u16 DeviceId) {
	XVecadd_1_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XVECADD_1_NUM_INSTANCES; Index++) {
		if (XVecadd_1_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XVecadd_1_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XVecadd_1_Initialize(XVecadd_1 *InstancePtr, u16 DeviceId) {
	XVecadd_1_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XVecadd_1_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XVecadd_1_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

