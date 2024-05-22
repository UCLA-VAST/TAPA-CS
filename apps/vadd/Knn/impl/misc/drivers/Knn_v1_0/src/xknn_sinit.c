// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xknn.h"

extern XKnn_Config XKnn_ConfigTable[];

XKnn_Config *XKnn_LookupConfig(u16 DeviceId) {
	XKnn_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XKNN_NUM_INSTANCES; Index++) {
		if (XKnn_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XKnn_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XKnn_Initialize(XKnn *InstancePtr, u16 DeviceId) {
	XKnn_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XKnn_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XKnn_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

