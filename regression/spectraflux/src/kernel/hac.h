
#pragma once

#include <hls_stream.h>
#include <ap_int.h>
#include <cstddef>
#include <limits>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <ap_fixed.h>
#include <type_traits>
#include "hls_task.h"


#define MAX_NUM_SPECTRA  300
#define Dhv  2048
#define f 4400
#define Q 16
#define MAX_PEAKS 64
#define DISTANCE_THRESHOLD (0.25 * Dhv)
#define CLUSTER_SIZE 300

#define MAX_BATCH_SIZE 1024

#define N_CLUSTERING 4

#define PEAK_PORT_W 1024
#define PEAK_LOOP_CNT ( (MAX_PEAKS+(PEAK_PORT_W/32)-1) / (PEAK_PORT_W/32) )

#define LOG_FUNCTION(X) (\
    X <= 15    ? 4  : \
    X <= 31    ? 5  : \
    X <= 63    ? 6  : \
    X <= 127   ? 7  : \
    X <= 255   ? 8  : \
    X <= 511   ? 9  : \
    X <= 1023  ? 10 : \
    X <= 2047  ? 11 : \
    X <= 4095  ? 12 : \
    X <= 8191  ? 13 : \
    X <= 16383 ? 14 : \
    X <= 65535 ? 16 : 32 \
    )


#define LOG_MAX_PEAKS ( LOG_FUNCTION(MAX_PEAKS) )
#define LOG_Dhv ( LOG_FUNCTION(Dhv) )
#define LOG_MAX_NUM_SPECTRA ( LOG_FUNCTION(MAX_NUM_SPECTRA) )
   



typedef ap_uint<Dhv> bitset_dhv;
typedef ap_uint<LOG_MAX_PEAKS> peak_cnt_t;

typedef ap_uint<LOG_Dhv> distance_t;
typedef ap_uint<LOG_Dhv+LOG_MAX_NUM_SPECTRA> acc_distance_t;
typedef ap_uint<LOG_FUNCTION(DISTANCE_THRESHOLD-1) + LOG_MAX_NUM_SPECTRA> acc_thres_distance_t;


struct Cluster {
    int next;
    int end;
    int num_elements;
    // float max_distance;
    int check_cluster;
};


struct PeakBuffer
{
    int mz[MAX_PEAKS];
    int intensity[MAX_PEAKS];
};

// struct EncodedBuffer {
//     int num_spectra;
//     bitset_dhv encoded_spectra[MAX_BATCH_SIZE];
// };
typedef bitset_dhv EncodedBuffer;

