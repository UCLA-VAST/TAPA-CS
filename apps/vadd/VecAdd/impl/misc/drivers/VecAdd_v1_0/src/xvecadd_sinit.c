// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xvecadd.h"

extern XVecadd_Config XVecadd_ConfigTable[];

XVecadd_Config *XVecadd_LookupConfig(u16 DeviceId) {
	XVecadd_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XVECADD_NUM_INSTANCES; Index++) {
		if (XVecadd_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XVecadd_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XVecadd_Initialize(XVecadd *InstancePtr, u16 DeviceId) {
	XVecadd_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XVecadd_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XVecadd_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

