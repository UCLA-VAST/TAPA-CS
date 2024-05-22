; ModuleID = '/tmp/run-hls-krnl_globalSort_L1_L2-hryunarr/project/krnl_globalSort_L1_L2/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >" = type { %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>", %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" }
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
%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >" = type { %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" }

; Function Attrs: inaccessiblememonly nounwind
declare void @llvm.sideeffect() #0

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_krnl_globalSort_L1_L2_ir(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_dist0, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_id0, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_dist1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_id1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_dist2, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_id2, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(16) %out_dist, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(16) %out_id) local_unnamed_addr #1 {
entry:
  %in_dist0_copy.0 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_dist0_copy.0, i32 0) ]
  %in_dist0_copy.1 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_dist0_copy.1, i32 0) ]
  %in_id0_copy.0 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_id0_copy.0, i32 0) ]
  %in_id0_copy.1 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_id0_copy.1, i32 0) ]
  %in_dist1_copy.0 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_dist1_copy.0, i32 0) ]
  %in_dist1_copy.1 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_dist1_copy.1, i32 0) ]
  %in_id1_copy.0 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_id1_copy.0, i32 0) ]
  %in_id1_copy.1 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_id1_copy.1, i32 0) ]
  %in_dist2_copy.0 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_dist2_copy.0, i32 0) ]
  %in_dist2_copy.1 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_dist2_copy.1, i32 0) ]
  %in_id2_copy.0 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_id2_copy.0, i32 0) ]
  %in_id2_copy.1 = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %in_id2_copy.1, i32 0) ]
  %out_dist_copy = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %out_dist_copy, i32 0) ]
  %out_id_copy = alloca i45, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i45* %out_id_copy, i32 0) ]
  call fastcc void @copy_in(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_dist0, i45* nonnull align 512 %in_dist0_copy.0, i45* nonnull align 512 %in_dist0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_id0, i45* nonnull align 512 %in_id0_copy.0, i45* nonnull align 512 %in_id0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_dist1, i45* nonnull align 512 %in_dist1_copy.0, i45* nonnull align 512 %in_dist1_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_id1, i45* nonnull align 512 %in_id1_copy.0, i45* nonnull align 512 %in_id1_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_dist2, i45* nonnull align 512 %in_dist2_copy.0, i45* nonnull align 512 %in_dist2_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_id2, i45* nonnull align 512 %in_id2_copy.0, i45* nonnull align 512 %in_id2_copy.1, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %out_dist, i45* nonnull align 512 %out_dist_copy, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %out_id, i45* nonnull align 512 %out_id_copy)
  call void @apatb_krnl_globalSort_L1_L2_hw(i45* %in_dist0_copy.0, i45* %in_dist0_copy.1, i45* %in_id0_copy.0, i45* %in_id0_copy.1, i45* %in_dist1_copy.0, i45* %in_dist1_copy.1, i45* %in_id1_copy.0, i45* %in_id1_copy.1, i45* %in_dist2_copy.0, i45* %in_dist2_copy.1, i45* %in_id2_copy.0, i45* %in_id2_copy.1, i45* %out_dist_copy, i45* %out_id_copy)
  call void @copy_back(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_dist0, i45* %in_dist0_copy.0, i45* %in_dist0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_id0, i45* %in_id0_copy.0, i45* %in_id0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_dist1, i45* %in_dist1_copy.0, i45* %in_dist1_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_id1, i45* %in_id1_copy.0, i45* %in_id1_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_dist2, i45* %in_dist2_copy.0, i45* %in_dist2_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_id2, i45* %in_id2_copy.0, i45* %in_id2_copy.1, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %out_dist, i45* %out_dist_copy, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %out_id, i45* %out_id_copy)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.0, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %.01, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="6", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.0" %.03, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.1" %.14, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="8", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.0" %.04, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1" %.15, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="10", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.0" %.05, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1" %.16, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="12", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="13.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="14", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="15.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.0, i45* align 512 %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.01, i45* align 512 %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.02, i45* align 512 %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %2)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.03, i45* align 512 %.14, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.04, i45* align 512 %.15, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %4)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.05, i45* align 512 %.16, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %5)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >.34"(i45* align 512 %7, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %6)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >.34"(i45* align 512 %9, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %8)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.0, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %.01, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="6", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.0" %.03, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.1" %.14, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="8", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.0" %.04, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1" %.15, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="10", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.0" %.05, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1" %.16, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="12", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="13.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="14", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="15.0") unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i45* align 512 %.0, i45* align 512 %.1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i45* align 512 %.01, i45* align 512 %.12)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %2, i45* align 512 %.02, i45* align 512 %.13)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3, i45* align 512 %.03, i45* align 512 %.14)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %4, i45* align 512 %.04, i45* align 512 %.15)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %5, i45* align 512 %.05, i45* align 512 %.16)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %6, i45* align 512 %7)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %8, i45* align 512 %9)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.48"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #4 {
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
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal { %"struct.hls::axis<ap_uint<32>, 0, 0, 0>", i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>s.i45"(i45 %A) #5 {
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

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.56"(i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #4 {
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
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i45 @"_llvm.fpga.pack.bits.i45.s_class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>s"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>" %A) #5 {
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
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="1") unnamed_addr #6 {
entry:
  %1 = icmp eq %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.56"(i45* align 512 %.02, %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.0)
  %.1 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.56"(i45* align 512 %.13, %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.13) unnamed_addr #6 {
entry:
  %1 = icmp eq %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.48"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.01, i45* align 512 %.02)
  %.12 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.48"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.12, i45* align 512 %.13)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0") unnamed_addr #6 {
entry:
  %2 = icmp eq %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01 = getelementptr %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.48"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.01, i45* align 512 %1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >.34"(i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="1") unnamed_addr #6 {
entry:
  %2 = icmp eq %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0 = getelementptr %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.56"(i45* align 512 %0, %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.0)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

declare void @apatb_krnl_globalSort_L1_L2_hw(i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*)

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_back(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.0, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %.01, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="6", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.0" %.03, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.1" %.14, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="8", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.0" %.04, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1" %.15, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="10", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.0" %.05, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1" %.16, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="12", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="13.0", %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="14", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="15.0") unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i45* align 512 %.0, i45* align 512 %.1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i45* align 512 %.01, i45* align 512 %.12)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %2, i45* align 512 %.02, i45* align 512 %.13)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3, i45* align 512 %.03, i45* align 512 %.14)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %4, i45* align 512 %.04, i45* align 512 %.15)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %5, i45* align 512 %.05, i45* align 512 %.16)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %6, i45* align 512 %7)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %8, i45* align 512 %9)
  ret void
}

define void @krnl_globalSort_L1_L2_hw_stub_wrapper(i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*) #7 {
entry:
  %14 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %15 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %16 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %17 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %18 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %19 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %20 = alloca %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %21 = alloca %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  call void @copy_out(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %14, i45* %0, i45* %1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %15, i45* %2, i45* %3, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %16, i45* %4, i45* %5, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %17, i45* %6, i45* %7, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %18, i45* %8, i45* %9, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %19, i45* %10, i45* %11, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %20, i45* %12, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %21, i45* %13)
  call void @krnl_globalSort_L1_L2_hw_stub(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %14, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %15, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %16, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %17, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %18, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %19, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %20, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %21)
  call void @copy_in(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %14, i45* %0, i45* %1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %15, i45* %2, i45* %3, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %16, i45* %4, i45* %5, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %17, i45* %6, i45* %7, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %18, i45* %8, i45* %9, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %19, i45* %10, i45* %11, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %20, i45* %12, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %21, i45* %13)
  ret void
}

declare void @krnl_globalSort_L1_L2_hw_stub(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::ostream<hls::axis<ap_uint<32>, 0, 0, 0> >"*)

declare i1 @fpga_fifo_not_empty_16(i8*)

declare i1 @fpga_fifo_not_empty_8(i8*)

declare void @fpga_fifo_pop_16(i8*, i8*)

declare void @fpga_fifo_pop_8(i8*, i8*)

declare void @fpga_fifo_push_16(i8*, i8*)

declare void @fpga_fifo_push_8(i8*, i8*)

attributes #0 = { inaccessiblememonly nounwind }
attributes #1 = { inaccessiblemem_or_argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #2 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #3 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #5 = { alwaysinline nounwind readnone }
attributes #6 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #7 = { "fpga.wrapper.func"="stub" }
attributes #8 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="64" }

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
