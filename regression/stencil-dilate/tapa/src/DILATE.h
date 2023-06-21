#include "/home/nehaprakriya/HLS_arbitrary_Precision_Types/include/ap_int.h"
#include <inttypes.h>
#ifndef DILATE_H

#define DILATE_H

#define GRID_ROWS 4096
#define GRID_COLS 4096

#define KERNEL_COUNT 15
#define PART_ROWS GRID_ROWS / KERNEL_COUNT

#define ITERATION 128

// #define ITERATION 64

#define DWIDTH 512
#define INTERFACE_WIDTH ap_uint<DWIDTH>
	const int WIDTH_FACTOR = DWIDTH/32;
#define PARA_FACTOR 16
const int MIDLE_REGION=1;
#define STAGE_COUNT 1
#define TOP_APPEND 0
#define BOTTOM_APPEND 1026
#define OVERLAP_TOP_OVERHEAD 0
#define OVERLAP_BOTTOM_OVERHEAD 524286
#define DECRE_TOP_APPEND 0
#define DECRE_BOTTOM_APPEND 1026
#endif
