#ifndef TAPA_TAPA_H_
#define TAPA_TAPA_H_

#if !defined(TAPA_TARGET_)

#include "/home/ubuntu/tapa_m/src/tapa/host/tapa.h"

#elif TAPA_TARGET_ == XILINX_HLS

#include "/home/ubuntu/tapa_m/src/tapa/xilinx/hls/tapa.h"

#endif

#include "/home/ubuntu/tapa_m/src/tapa/traits.h"

#endif  // TAPA_TAPA_H_
