; ModuleID = '/tmp/run-hls-krnl_partialKnn_wrapper_9-uqo9uvhy/project/krnl_partialKnn_wrapper_9/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.tapa::async_mmap<ap_uint<256> >" = type { %"class.tapa::ostream<long>", %"class.tapa::istream<ap_uint<256> >", %"class.tapa::ostream<long>", %"class.tapa::ostream<ap_uint<256> >", %"class.tapa::istream<unsigned char>" }
%"class.tapa::istream<ap_uint<256> >" = type { %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>", %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" }
%"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" = type { %"struct.tapa::internal::elem_t<ap_uint<256> >" }
%"struct.tapa::internal::elem_t<ap_uint<256> >" = type { %"struct.ap_uint<256>", i1 }
%"struct.ap_uint<256>" = type { %"struct.ap_int_base<256, false>" }
%"struct.ap_int_base<256, false>" = type { %"struct.ssdm_int<256, false>" }
%"struct.ssdm_int<256, false>" = type { i256 }
%"class.tapa::ostream<long>" = type { %"class.hls::stream<tapa::internal::elem_t<long>, 0>" }
%"class.hls::stream<tapa::internal::elem_t<long>, 0>" = type { %"struct.tapa::internal::elem_t<long>" }
%"struct.tapa::internal::elem_t<long>" = type { i64, i1 }
%"class.tapa::ostream<ap_uint<256> >" = type { %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" }
%"class.tapa::istream<unsigned char>" = type { %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>", %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" }
%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" = type { %"struct.tapa::internal::elem_t<unsigned char>" }
%"struct.tapa::internal::elem_t<unsigned char>" = type { i8, i1 }
%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >" = type { %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" }
%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" = type { %"struct.tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >" }
%"struct.tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >" = type { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 }
%"struct.hls::axis<ap_uint<32>, 0, 0, 0>" = type { %"struct.ap_uint<32>", %"struct.ap_uint<4>", %"struct.ap_uint<4>", %"struct.ap_uint<1>", %"struct.ap_uint<1>", %"struct.ap_uint<1>", %"struct.ap_uint<1>" }
%"struct.ap_uint<32>" = type { %"struct.ap_int_base<32, false>" }
%"struct.ap_int_base<32, false>" = type { %"struct.ssdm_int<32, false>" }
%"struct.ssdm_int<32, false>" = type { i32 }
%"struct.ap_uint<4>" = type { %"struct.ap_int_base<4, false>" }
%"struct.ap_int_base<4, false>" = type { %"struct.ssdm_int<4, false>" }
%"struct.ssdm_int<4, false>" = type { i4 }
%"struct.ap_uint<1>" = type { %"struct.ap_int_base<1, false>" }
%"struct.ap_int_base<1, false>" = type { %"struct.ssdm_int<1, false>" }
%"struct.ssdm_int<1, false>" = type { i1 }

; Function Attrs: inaccessiblememonly nounwind
declare void @llvm.sideeffect() #0

; Function Attrs: noinline
define void @apatb_krnl_partialKnn_wrapper_9_ir(%"struct.tapa::async_mmap<ap_uint<256> >"* noalias nonnull dereferenceable(288) %searchSpace_0, i32 %start_id_0, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(16) %out_dist, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(16) %out_id) local_unnamed_addr #1 {
entry:
  %searchSpace_0_copy.0 = alloca i65, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i65* %searchSpace_0_copy.0, i32 0) ]
  %searchSpace_0_copy.1.0 = alloca i257, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i257* %searchSpace_0_copy.1.0, i32 0) ]
  %searchSpace_0_copy.1.1 = alloca i257, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i257* %searchSpace_0_copy.1.1, i32 0) ]
  %searchSpace_0_copy.2 = alloca i65, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i65* %searchSpace_0_copy.2, i32 0) ]
  %searchSpace_0_copy.3 = alloca i257, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i257* %searchSpace_0_copy.3, i32 0) ]
  %searchSpace_0_copy.4.0 = alloca i9, align 512
  call void @llvm.sideeffect() #10 [ "stream_interface"(i9* %searchSpace_0_copy.4.0, i32 0) ]
  %searchSpace_0_copy.4.1 = alloca i9, align 512
  call void @llvm.sideeffect() #10 [ "stream_interface"(i9* %searchSpace_0_copy.4.1, i32 0) ]
  %out_dist_copy = alloca i45, align 512
  call void @llvm.sideeffect() #11 [ "stream_interface"(i45* %out_dist_copy, i32 0) ]
  %out_id_copy = alloca i45, align 512
  call void @llvm.sideeffect() #11 [ "stream_interface"(i45* %out_id_copy, i32 0) ]
  call fastcc void @copy_in(%"struct.tapa::async_mmap<ap_uint<256> >"* nonnull %searchSpace_0, i65* nonnull align 512 %searchSpace_0_copy.0, i257* nonnull align 512 %searchSpace_0_copy.1.0, i257* nonnull align 512 %searchSpace_0_copy.1.1, i65* nonnull align 512 %searchSpace_0_copy.2, i257* nonnull align 512 %searchSpace_0_copy.3, i9* nonnull align 512 %searchSpace_0_copy.4.0, i9* nonnull align 512 %searchSpace_0_copy.4.1, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %out_dist, i45* nonnull align 512 %out_dist_copy, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %out_id, i45* nonnull align 512 %out_id_copy)
  call void @apatb_krnl_partialKnn_wrapper_9_hw(i65* %searchSpace_0_copy.0, i257* %searchSpace_0_copy.1.0, i257* %searchSpace_0_copy.1.1, i65* %searchSpace_0_copy.2, i257* %searchSpace_0_copy.3, i9* %searchSpace_0_copy.4.0, i9* %searchSpace_0_copy.4.1, i32 %start_id_0, i45* %out_dist_copy, i45* %out_id_copy)
  call void @copy_back(%"struct.tapa::async_mmap<ap_uint<256> >"* %searchSpace_0, i65* %searchSpace_0_copy.0, i257* %searchSpace_0_copy.1.0, i257* %searchSpace_0_copy.1.1, i65* %searchSpace_0_copy.2, i257* %searchSpace_0_copy.3, i9* %searchSpace_0_copy.4.0, i9* %searchSpace_0_copy.4.1, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %out_dist, i45* %out_dist_copy, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %out_id, i45* %out_id_copy)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in(%"struct.tapa::async_mmap<ap_uint<256> >"* noalias "unpacked"="0", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0.0" %.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.0" %.1.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2.0" %.2, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.1" %.4.1, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<ap_uint<256> >"(i65* align 512 %.0, i257* align 512 %.1.0, i257* align 512 %.1.1, i65* align 512 %.2, i257* align 512 %.3, i9* align 512 %.4.0, i9* align 512 %.4.1, %"struct.tapa::async_mmap<ap_uint<256> >"* %0)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >.109"(i45* align 512 %2, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >.109"(i45* align 512 %4, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out(%"struct.tapa::async_mmap<ap_uint<256> >"* noalias "unpacked"="0", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0.0" %.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.0" %.1.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2.0" %.2, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.1" %.4.1, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0") unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<ap_uint<256> >.28"(%"struct.tapa::async_mmap<ap_uint<256> >"* %0, i65* align 512 %.0, i257* align 512 %.1.0, i257* align 512 %.1.1, i65* align 512 %.2, i257* align 512 %.3, i9* align 512 %.4.0, i9* align 512 %.4.1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i45* align 512 %2)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3, i45* align 512 %4)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<ap_uint<256> >"(i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0.0" %.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1.0" %.1.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.2.0" %.2, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.4.1" %.4.1, %"struct.tapa::async_mmap<ap_uint<256> >"* noalias "unpacked"="1") unnamed_addr #4 {
entry:
  %1 = icmp eq %"struct.tapa::async_mmap<ap_uint<256> >"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0.06 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(i65* align 512 %.0, %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.0.06)
  %.1.08 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 1, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>.147"(i257* align 512 %.1.0, %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %.1.08)
  %.1.110 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 1, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>.147"(i257* align 512 %.1.1, %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %.1.110)
  %.2.012 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 2, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(i65* align 512 %.2, %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.2.012)
  %.3.014 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 3, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>.147"(i257* align 512 %.3, %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %.3.014)
  %.4.016 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 4, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(i9* align 512 %.4.0, %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.4.016)
  %.4.118 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 4, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(i9* align 512 %.4.1, %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.4.118)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<ap_uint<256> >.28"(%"struct.tapa::async_mmap<ap_uint<256> >"* noalias "unpacked"="0", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0.0" %.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.0" %.1.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2.0" %.2, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.1" %.4.1) unnamed_addr #4 {
entry:
  %1 = icmp eq %"struct.tapa::async_mmap<ap_uint<256> >"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01.07 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.132"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.01.07, i65* align 512 %.0)
  %.12.09 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 1, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"(%"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %.12.09, i257* align 512 %.1.0)
  %.12.111 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 1, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"(%"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %.12.111, i257* align 512 %.1.1)
  %.23.013 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 2, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.132"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.23.013, i65* align 512 %.2)
  %.34.015 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 3, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"(%"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %.34.015, i257* align 512 %.3)
  %.45.017 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 4, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.173"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.45.017, i9* align 512 %.4.0)
  %.45.119 = getelementptr %"struct.tapa::async_mmap<ap_uint<256> >", %"struct.tapa::async_mmap<ap_uint<256> >"* %0, i32 0, i32 4, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.173"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.45.119, i9* align 512 %.4.1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.132"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca i65
  %3 = alloca %"class.hls::stream<tapa::internal::elem_t<long>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast i65* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_16(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast i65* %2 to i8*
  %7 = bitcast i65* %1 to i8*
  call void @fpga_fifo_pop_16(i8* %6, i8* %7)
  %8 = bitcast i65* %2 to i72*
  %9 = load i72, i72* %8
  %10 = trunc i72 %9 to i65
  %11 = call { i64, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<long>, 0>s.i65"(i65 %10)
  %newret = extractvalue { i64, i1 } %11, 0
  %oldret1 = insertvalue %"struct.tapa::internal::elem_t<long>" undef, i64 %newret, 0
  %newret2 = extractvalue { i64, i1 } %11, 1
  %oldret3 = insertvalue %"struct.tapa::internal::elem_t<long>" %oldret1, i1 %newret2, 1
  %oldret = insertvalue %"class.hls::stream<tapa::internal::elem_t<long>, 0>" undef, %"struct.tapa::internal::elem_t<long>" %oldret3, 0
  store %"class.hls::stream<tapa::internal::elem_t<long>, 0>" %oldret, %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %3
  %12 = bitcast %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %3 to i8*
  %13 = bitcast %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %0 to i8*
  call void @fpga_fifo_push_16(i8* %12, i8* %13)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal { i64, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<long>, 0>s.i65"(i65 %A) #6 {
  %1 = trunc i65 %A to i64
  %2 = lshr i65 %A, 64
  %3 = trunc i65 %2 to i1
  %newret = insertvalue { i64, i1 } undef, i64 %1, 0
  %newret2 = insertvalue { i64, i1 } %newret, i1 %3, 1
  ret { i64, i1 } %newret2
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca %"class.hls::stream<tapa::internal::elem_t<long>, 0>"
  %3 = alloca i65
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_16(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %2 to i8*
  %7 = bitcast %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %1 to i8*
  call void @fpga_fifo_pop_16(i8* %6, i8* %7)
  %8 = load volatile %"class.hls::stream<tapa::internal::elem_t<long>, 0>", %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %2
  %9 = call i65 @"_llvm.fpga.pack.bits.i65.s_class.hls::stream<tapa::internal::elem_t<long>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>" %8)
  store i65 %9, i65* %3
  %10 = bitcast i65* %3 to i8*
  %11 = bitcast i65* %0 to i8*
  call void @fpga_fifo_push_16(i8* %10, i8* %11)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i65 @"_llvm.fpga.pack.bits.i65.s_class.hls::stream<tapa::internal::elem_t<long>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>" %A) #6 {
  %A.0 = extractvalue %"class.hls::stream<tapa::internal::elem_t<long>, 0>" %A, 0
  %A.0.0 = extractvalue %"struct.tapa::internal::elem_t<long>" %A.0, 0
  %1 = zext i64 %A.0.0 to i65
  %A.0.1 = extractvalue %"struct.tapa::internal::elem_t<long>" %A.0, 1
  %2 = zext i1 %A.0.1 to i65
  %3 = shl i65 %2, 64
  %4 = or i65 %3, %1
  ret i65 %4
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>.147"(i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"
  %3 = alloca i257
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_64(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %2 to i8*
  %7 = bitcast %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %1 to i8*
  call void @fpga_fifo_pop_64(i8* %6, i8* %7)
  %8 = load volatile %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>", %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %2
  %9 = call i257 @"_llvm.fpga.pack.bits.i257.s_class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>s"(%"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" %8)
  store i257 %9, i257* %3
  %10 = bitcast i257* %3 to i8*
  %11 = bitcast i257* %0 to i8*
  call void @fpga_fifo_push_64(i8* %10, i8* %11)
  br label %empty, !llvm.loop !7

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i257 @"_llvm.fpga.pack.bits.i257.s_class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>s"(%"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" %A) #6 {
  %A.0 = extractvalue %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" %A, 0
  %A.0.0 = extractvalue %"struct.tapa::internal::elem_t<ap_uint<256> >" %A.0, 0
  %A.0.0.0 = extractvalue %"struct.ap_uint<256>" %A.0.0, 0
  %A.0.0.0.0 = extractvalue %"struct.ap_int_base<256, false>" %A.0.0.0, 0
  %A.0.0.0.0.0 = extractvalue %"struct.ssdm_int<256, false>" %A.0.0.0.0, 0
  %1 = zext i256 %A.0.0.0.0.0 to i257
  %A.0.1 = extractvalue %"struct.tapa::internal::elem_t<ap_uint<256> >" %A.0, 1
  %2 = zext i1 %A.0.1 to i257
  %3 = shl i257 %2, 256
  %4 = or i257 %3, %1
  ret i257 %4
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"(%"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca i257
  %3 = alloca %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast i257* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_64(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast i257* %2 to i8*
  %7 = bitcast i257* %1 to i8*
  call void @fpga_fifo_pop_64(i8* %6, i8* %7)
  %8 = bitcast i257* %2 to i264*
  %9 = load i264, i264* %8
  %10 = trunc i264 %9 to i257
  %11 = call { %"struct.ap_uint<256>", i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>s.i257"(i257 %10)
  %newret = extractvalue { %"struct.ap_uint<256>", i1 } %11, 0
  %oldret1 = insertvalue %"struct.tapa::internal::elem_t<ap_uint<256> >" undef, %"struct.ap_uint<256>" %newret, 0
  %newret2 = extractvalue { %"struct.ap_uint<256>", i1 } %11, 1
  %oldret3 = insertvalue %"struct.tapa::internal::elem_t<ap_uint<256> >" %oldret1, i1 %newret2, 1
  %oldret = insertvalue %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" undef, %"struct.tapa::internal::elem_t<ap_uint<256> >" %oldret3, 0
  store %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>" %oldret, %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %3
  %12 = bitcast %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %3 to i8*
  %13 = bitcast %"class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>"* %0 to i8*
  call void @fpga_fifo_push_64(i8* %12, i8* %13)
  br label %empty, !llvm.loop !7

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal { %"struct.ap_uint<256>", i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<ap_uint<256> >, 0>s.i257"(i257 %A) #6 {
  %1 = trunc i257 %A to i256
  %.0 = insertvalue %"struct.ssdm_int<256, false>" undef, i256 %1, 0
  %.01 = insertvalue %"struct.ap_int_base<256, false>" undef, %"struct.ssdm_int<256, false>" %.0, 0
  %.02 = insertvalue %"struct.ap_uint<256>" undef, %"struct.ap_int_base<256, false>" %.01, 0
  %2 = lshr i257 %A, 256
  %3 = trunc i257 %2 to i1
  %newret = insertvalue { %"struct.ap_uint<256>", i1 } undef, %"struct.ap_uint<256>" %.02, 0
  %newret2 = insertvalue { %"struct.ap_uint<256>", i1 } %newret, i1 %3, 1
  ret { %"struct.ap_uint<256>", i1 } %newret2
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.173"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca i9
  %3 = alloca %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast i9* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_2(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast i9* %2 to i8*
  %7 = bitcast i9* %1 to i8*
  call void @fpga_fifo_pop_2(i8* %6, i8* %7)
  %8 = bitcast i9* %2 to i16*
  %9 = load i16, i16* %8
  %10 = trunc i16 %9 to i9
  %11 = call { i8, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>s.i9"(i9 %10)
  %newret = extractvalue { i8, i1 } %11, 0
  %oldret1 = insertvalue %"struct.tapa::internal::elem_t<unsigned char>" undef, i8 %newret, 0
  %newret2 = extractvalue { i8, i1 } %11, 1
  %oldret3 = insertvalue %"struct.tapa::internal::elem_t<unsigned char>" %oldret1, i1 %newret2, 1
  %oldret = insertvalue %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" undef, %"struct.tapa::internal::elem_t<unsigned char>" %oldret3, 0
  store %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" %oldret, %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %3
  %12 = bitcast %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %3 to i8*
  %13 = bitcast %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %0 to i8*
  call void @fpga_fifo_push_2(i8* %12, i8* %13)
  br label %empty, !llvm.loop !8

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal { i8, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>s.i9"(i9 %A) #6 {
  %1 = trunc i9 %A to i8
  %2 = lshr i9 %A, 8
  %3 = trunc i9 %2 to i1
  %newret = insertvalue { i8, i1 } undef, i8 %1, 0
  %newret2 = insertvalue { i8, i1 } %newret, i1 %3, 1
  ret { i8, i1 } %newret2
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"
  %3 = alloca i9
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_2(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %2 to i8*
  %7 = bitcast %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %1 to i8*
  call void @fpga_fifo_pop_2(i8* %6, i8* %7)
  %8 = load volatile %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>", %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %2
  %9 = call i9 @"_llvm.fpga.pack.bits.i9.s_class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" %8)
  store i9 %9, i9* %3
  %10 = bitcast i9* %3 to i8*
  %11 = bitcast i9* %0 to i8*
  call void @fpga_fifo_push_2(i8* %10, i8* %11)
  br label %empty, !llvm.loop !8

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i9 @"_llvm.fpga.pack.bits.i9.s_class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" %A) #6 {
  %A.0 = extractvalue %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" %A, 0
  %A.0.0 = extractvalue %"struct.tapa::internal::elem_t<unsigned char>" %A.0, 0
  %1 = zext i8 %A.0.0 to i9
  %A.0.1 = extractvalue %"struct.tapa::internal::elem_t<unsigned char>" %A.0, 1
  %2 = zext i1 %A.0.1 to i9
  %3 = shl i9 %2, 8
  %4 = or i9 %3, %1
  ret i9 %4
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >.109"(i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="1") unnamed_addr #4 {
entry:
  %2 = icmp eq %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0 = getelementptr %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.198"(i45* align 512 %0, %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.0)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.198"(i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"
  %3 = alloca i45
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_16(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %2 to i8*
  %7 = bitcast %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %1 to i8*
  call void @fpga_fifo_pop_16(i8* %6, i8* %7)
  %8 = load volatile %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>", %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %2
  %9 = call i45 @"_llvm.fpga.pack.bits.i45.s_class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>s"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" %8)
  store i45 %9, i45* %3
  %10 = bitcast i45* %3 to i8*
  %11 = bitcast i45* %0 to i8*
  call void @fpga_fifo_push_8(i8* %10, i8* %11)
  br label %empty, !llvm.loop !9

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i45 @"_llvm.fpga.pack.bits.i45.s_class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>s"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" %A) #6 {
  %A.0 = extractvalue %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" %A, 0
  %A.0.0 = extractvalue %"struct.tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >" %A.0, 0
  %A.0.0.0 = extractvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %A.0.0, 0
  %A.0.0.0.0 = extractvalue %"struct.ap_uint<32>" %A.0.0.0, 0
  %A.0.0.0.0.0 = extractvalue %"struct.ap_int_base<32, false>" %A.0.0.0.0, 0
  %A.0.0.0.0.0.0 = extractvalue %"struct.ssdm_int<32, false>" %A.0.0.0.0.0, 0
  %1 = zext i32 %A.0.0.0.0.0.0 to i44
  %A.0.0.1 = extractvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %A.0.0, 1
  %A.0.0.1.0 = extractvalue %"struct.ap_uint<4>" %A.0.0.1, 0
  %A.0.0.1.0.0 = extractvalue %"struct.ap_int_base<4, false>" %A.0.0.1.0, 0
  %A.0.0.1.0.0.0 = extractvalue %"struct.ssdm_int<4, false>" %A.0.0.1.0.0, 0
  %2 = zext i4 %A.0.0.1.0.0.0 to i44
  %3 = shl i44 %2, 32
  %4 = or i44 %3, %1
  %A.0.0.2 = extractvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %A.0.0, 2
  %A.0.0.2.0 = extractvalue %"struct.ap_uint<4>" %A.0.0.2, 0
  %A.0.0.2.0.0 = extractvalue %"struct.ap_int_base<4, false>" %A.0.0.2.0, 0
  %A.0.0.2.0.0.0 = extractvalue %"struct.ssdm_int<4, false>" %A.0.0.2.0.0, 0
  %5 = zext i4 %A.0.0.2.0.0.0 to i44
  %6 = shl i44 %5, 36
  %7 = or i44 %4, %6
  %A.0.0.3 = extractvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %A.0.0, 3
  %A.0.0.3.0 = extractvalue %"struct.ap_uint<1>" %A.0.0.3, 0
  %A.0.0.3.0.0 = extractvalue %"struct.ap_int_base<1, false>" %A.0.0.3.0, 0
  %A.0.0.3.0.0.0 = extractvalue %"struct.ssdm_int<1, false>" %A.0.0.3.0.0, 0
  %8 = zext i1 %A.0.0.3.0.0.0 to i44
  %9 = shl i44 %8, 40
  %10 = or i44 %7, %9
  %A.0.0.4 = extractvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %A.0.0, 4
  %A.0.0.4.0 = extractvalue %"struct.ap_uint<1>" %A.0.0.4, 0
  %A.0.0.4.0.0 = extractvalue %"struct.ap_int_base<1, false>" %A.0.0.4.0, 0
  %A.0.0.4.0.0.0 = extractvalue %"struct.ssdm_int<1, false>" %A.0.0.4.0.0, 0
  %11 = zext i1 %A.0.0.4.0.0.0 to i44
  %12 = shl i44 %11, 41
  %A.0.0.5 = extractvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %A.0.0, 5
  %A.0.0.5.0 = extractvalue %"struct.ap_uint<1>" %A.0.0.5, 0
  %A.0.0.5.0.0 = extractvalue %"struct.ap_int_base<1, false>" %A.0.0.5.0, 0
  %A.0.0.5.0.0.0 = extractvalue %"struct.ssdm_int<1, false>" %A.0.0.5.0.0, 0
  %13 = zext i1 %A.0.0.5.0.0.0 to i44
  %14 = shl i44 %13, 42
  %15 = or i44 %10, %12
  %A.0.0.6 = extractvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %A.0.0, 6
  %A.0.0.6.0 = extractvalue %"struct.ap_uint<1>" %A.0.0.6, 0
  %A.0.0.6.0.0 = extractvalue %"struct.ap_int_base<1, false>" %A.0.0.6.0, 0
  %A.0.0.6.0.0.0 = extractvalue %"struct.ssdm_int<1, false>" %A.0.0.6.0.0, 0
  %16 = zext i1 %A.0.0.6.0.0.0 to i44
  %17 = shl i44 %16, 43
  %18 = or i44 %15, %14
  %19 = or i44 %18, %17
  %20 = zext i44 %19 to i45
  %A.0.1 = extractvalue %"struct.tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >" %A.0, 1
  %21 = zext i1 %A.0.1 to i45
  %22 = shl i45 %21, 44
  %23 = or i45 %22, %20
  ret i45 %23
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0") unnamed_addr #4 {
entry:
  %2 = icmp eq %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01 = getelementptr %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.206"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.01, i45* align 512 %1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.206"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca i45
  %3 = alloca %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast i45* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_8(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast i45* %2 to i8*
  %7 = bitcast i45* %1 to i8*
  call void @fpga_fifo_pop_8(i8* %6, i8* %7)
  %8 = bitcast i45* %2 to i48*
  %9 = load i48, i48* %8
  %10 = trunc i48 %9 to i45
  %11 = call { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>s.i45"(i45 %10)
  %newret = extractvalue { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } %11, 0
  %oldret1 = insertvalue %"struct.tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >" undef, %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %newret, 0
  %newret2 = extractvalue { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } %11, 1
  %oldret3 = insertvalue %"struct.tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >" %oldret1, i1 %newret2, 1
  %oldret = insertvalue %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" undef, %"struct.tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >" %oldret3, 0
  store %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" %oldret, %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %3
  %12 = bitcast %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %3 to i8*
  %13 = bitcast %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %0 to i8*
  call void @fpga_fifo_push_16(i8* %12, i8* %13)
  br label %empty, !llvm.loop !9

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>s.i45"(i45 %A) #6 {
  %1 = trunc i45 %A to i44
  %2 = trunc i44 %1 to i32
  %.0 = insertvalue %"struct.ssdm_int<32, false>" undef, i32 %2, 0
  %.01 = insertvalue %"struct.ap_int_base<32, false>" undef, %"struct.ssdm_int<32, false>" %.0, 0
  %.02 = insertvalue %"struct.ap_uint<32>" undef, %"struct.ap_int_base<32, false>" %.01, 0
  %.03 = insertvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" undef, %"struct.ap_uint<32>" %.02, 0
  %3 = lshr i44 %1, 32
  %4 = trunc i44 %3 to i4
  %.04 = insertvalue %"struct.ssdm_int<4, false>" undef, i4 %4, 0
  %.05 = insertvalue %"struct.ap_int_base<4, false>" undef, %"struct.ssdm_int<4, false>" %.04, 0
  %.06 = insertvalue %"struct.ap_uint<4>" undef, %"struct.ap_int_base<4, false>" %.05, 0
  %.1 = insertvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %.03, %"struct.ap_uint<4>" %.06, 1
  %5 = lshr i44 %1, 36
  %6 = trunc i44 %5 to i4
  %.07 = insertvalue %"struct.ssdm_int<4, false>" undef, i4 %6, 0
  %.08 = insertvalue %"struct.ap_int_base<4, false>" undef, %"struct.ssdm_int<4, false>" %.07, 0
  %.09 = insertvalue %"struct.ap_uint<4>" undef, %"struct.ap_int_base<4, false>" %.08, 0
  %.2 = insertvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %.1, %"struct.ap_uint<4>" %.09, 2
  %7 = lshr i44 %1, 40
  %8 = trunc i44 %7 to i1
  %.010 = insertvalue %"struct.ssdm_int<1, false>" undef, i1 %8, 0
  %.011 = insertvalue %"struct.ap_int_base<1, false>" undef, %"struct.ssdm_int<1, false>" %.010, 0
  %.012 = insertvalue %"struct.ap_uint<1>" undef, %"struct.ap_int_base<1, false>" %.011, 0
  %.3 = insertvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %.2, %"struct.ap_uint<1>" %.012, 3
  %9 = lshr i44 %1, 41
  %10 = trunc i44 %9 to i1
  %.013 = insertvalue %"struct.ssdm_int<1, false>" undef, i1 %10, 0
  %.014 = insertvalue %"struct.ap_int_base<1, false>" undef, %"struct.ssdm_int<1, false>" %.013, 0
  %.015 = insertvalue %"struct.ap_uint<1>" undef, %"struct.ap_int_base<1, false>" %.014, 0
  %.4 = insertvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %.3, %"struct.ap_uint<1>" %.015, 4
  %11 = lshr i44 %1, 42
  %12 = trunc i44 %11 to i1
  %.016 = insertvalue %"struct.ssdm_int<1, false>" undef, i1 %12, 0
  %.017 = insertvalue %"struct.ap_int_base<1, false>" undef, %"struct.ssdm_int<1, false>" %.016, 0
  %.018 = insertvalue %"struct.ap_uint<1>" undef, %"struct.ap_int_base<1, false>" %.017, 0
  %.5 = insertvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %.4, %"struct.ap_uint<1>" %.018, 5
  %13 = lshr i44 %1, 43
  %14 = trunc i44 %13 to i1
  %.019 = insertvalue %"struct.ssdm_int<1, false>" undef, i1 %14, 0
  %.020 = insertvalue %"struct.ap_int_base<1, false>" undef, %"struct.ssdm_int<1, false>" %.019, 0
  %.021 = insertvalue %"struct.ap_uint<1>" undef, %"struct.ap_int_base<1, false>" %.020, 0
  %.6 = insertvalue %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %.5, %"struct.ap_uint<1>" %.021, 6
  %15 = lshr i45 %A, 44
  %16 = trunc i45 %15 to i1
  %newret = insertvalue { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } undef, %"struct.hls::axis<ap_uint<32>, 0, 0, 0>" %.6, 0
  %newret2 = insertvalue { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } %newret, i1 %16, 1
  ret { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } %newret2
}

declare void @apatb_krnl_partialKnn_wrapper_9_hw(i65*, i257*, i257*, i65*, i257*, i9*, i9*, i32, i45*, i45*)

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_back(%"struct.tapa::async_mmap<ap_uint<256> >"* noalias "unpacked"="0", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0.0" %.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.0" %.1.0, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2.0" %.2, i257* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.1" %.4.1, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0") unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<ap_uint<256> >.28"(%"struct.tapa::async_mmap<ap_uint<256> >"* %0, i65* align 512 %.0, i257* align 512 %.1.0, i257* align 512 %.1.1, i65* align 512 %.2, i257* align 512 %.3, i9* align 512 %.4.0, i9* align 512 %.4.1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i45* align 512 %2)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3, i45* align 512 %4)
  ret void
}

define void @krnl_partialKnn_wrapper_9_hw_stub_wrapper(i65*, i257*, i257*, i65*, i257*, i9*, i9*, i32, i45*, i45*) #7 {
entry:
  %10 = alloca %"struct.tapa::async_mmap<ap_uint<256> >"
  %11 = alloca %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %12 = alloca %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  call void @copy_out(%"struct.tapa::async_mmap<ap_uint<256> >"* %10, i65* %0, i257* %1, i257* %2, i65* %3, i257* %4, i9* %5, i9* %6, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %11, i45* %8, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %12, i45* %9)
  call void @krnl_partialKnn_wrapper_9_hw_stub(%"struct.tapa::async_mmap<ap_uint<256> >"* %10, i32 %7, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %11, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %12)
  call void @copy_in(%"struct.tapa::async_mmap<ap_uint<256> >"* %10, i65* %0, i257* %1, i257* %2, i65* %3, i257* %4, i9* %5, i9* %6, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %11, i45* %8, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %12, i45* %9)
  ret void
}

declare void @krnl_partialKnn_wrapper_9_hw_stub(%"struct.tapa::async_mmap<ap_uint<256> >"*, i32, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"*)

declare i1 @fpga_fifo_not_empty_16(i8*)

declare i1 @fpga_fifo_not_empty_64(i8*)

declare i1 @fpga_fifo_not_empty_2(i8*)

declare i1 @fpga_fifo_not_empty_8(i8*)

declare void @fpga_fifo_pop_16(i8*, i8*)

declare void @fpga_fifo_pop_64(i8*, i8*)

declare void @fpga_fifo_pop_2(i8*, i8*)

declare void @fpga_fifo_pop_8(i8*, i8*)

declare void @fpga_fifo_push_16(i8*, i8*)

declare void @fpga_fifo_push_64(i8*, i8*)

declare void @fpga_fifo_push_2(i8*, i8*)

declare void @fpga_fifo_push_8(i8*, i8*)

attributes #0 = { inaccessiblememonly nounwind }
attributes #1 = { noinline "fpga.wrapper.func"="wrapper" }
attributes #2 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #3 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #5 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #6 = { alwaysinline nounwind readnone }
attributes #7 = { "fpga.wrapper.func"="stub" }
attributes #8 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="128" }
attributes #9 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="512" }
attributes #10 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="16" }
attributes #11 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="64" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.rotate.disable"}
!7 = distinct !{!7, !6}
!8 = distinct !{!8, !6}
!9 = distinct !{!9, !6}
