; ModuleID = '/tmp/run-hls-krnl_globalSort_L3-1uu89nah/project/krnl_globalSort_L3/.autopilot/db/a.g.ld.5.gdce.bc'
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
%"struct.tapa::async_mmap<float>" = type { %"class.tapa::ostream<long>", %"class.tapa::istream<float>", %"class.tapa::ostream<long>", %"class.tapa::ostream<float>", %"class.tapa::istream<unsigned char>" }
%"class.tapa::istream<float>" = type { %"class.hls::stream<tapa::internal::elem_t<float>, 0>", %"class.hls::stream<tapa::internal::elem_t<float>, 0>" }
%"class.hls::stream<tapa::internal::elem_t<float>, 0>" = type { %"struct.tapa::internal::elem_t<float>" }
%"struct.tapa::internal::elem_t<float>" = type { float, i1 }
%"class.tapa::ostream<long>" = type { %"class.hls::stream<tapa::internal::elem_t<long>, 0>" }
%"class.hls::stream<tapa::internal::elem_t<long>, 0>" = type { %"struct.tapa::internal::elem_t<long>" }
%"struct.tapa::internal::elem_t<long>" = type { i64, i1 }
%"class.tapa::ostream<float>" = type { %"class.hls::stream<tapa::internal::elem_t<float>, 0>" }
%"class.tapa::istream<unsigned char>" = type { %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>", %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" }
%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>" = type { %"struct.tapa::internal::elem_t<unsigned char>" }
%"struct.tapa::internal::elem_t<unsigned char>" = type { i8, i1 }
%"struct.tapa::async_mmap<int>" = type { %"class.tapa::ostream<long>", %"class.tapa::istream<int>", %"class.tapa::ostream<long>", %"class.tapa::ostream<int>", %"class.tapa::istream<unsigned char>" }
%"class.tapa::istream<int>" = type { %"class.hls::stream<tapa::internal::elem_t<int>, 0>", %"class.hls::stream<tapa::internal::elem_t<int>, 0>" }
%"class.hls::stream<tapa::internal::elem_t<int>, 0>" = type { %"struct.tapa::internal::elem_t<int>" }
%"struct.tapa::internal::elem_t<int>" = type { i32, i1 }
%"class.tapa::ostream<int>" = type { %"class.hls::stream<tapa::internal::elem_t<int>, 0>" }

; Function Attrs: inaccessiblememonly nounwind
declare void @llvm.sideeffect() #0

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_krnl_globalSort_L3_ir(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_dist0, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_id0, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_dist1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias nocapture nonnull dereferenceable(32) %in_id1, %"struct.tapa::async_mmap<float>"* noalias nonnull dereferenceable(64) %output_knnDist, %"struct.tapa::async_mmap<int>"* noalias nonnull dereferenceable(64) %output_knnId) local_unnamed_addr #1 {
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
  %output_knnDist_copy.0 = alloca i65, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i65* %output_knnDist_copy.0, i32 0) ]
  %output_knnDist_copy.1.0 = alloca i33, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i33* %output_knnDist_copy.1.0, i32 0) ]
  %output_knnDist_copy.1.1 = alloca i33, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i33* %output_knnDist_copy.1.1, i32 0) ]
  %output_knnDist_copy.2 = alloca i65, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i65* %output_knnDist_copy.2, i32 0) ]
  %output_knnDist_copy.3 = alloca i33, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i33* %output_knnDist_copy.3, i32 0) ]
  %output_knnDist_copy.4.0 = alloca i9, align 512
  call void @llvm.sideeffect() #10 [ "stream_interface"(i9* %output_knnDist_copy.4.0, i32 0) ]
  %output_knnDist_copy.4.1 = alloca i9, align 512
  call void @llvm.sideeffect() #10 [ "stream_interface"(i9* %output_knnDist_copy.4.1, i32 0) ]
  %output_knnId_copy.0 = alloca i65, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i65* %output_knnId_copy.0, i32 0) ]
  %output_knnId_copy.1.0 = alloca i33, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i33* %output_knnId_copy.1.0, i32 0) ]
  %output_knnId_copy.1.1 = alloca i33, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i33* %output_knnId_copy.1.1, i32 0) ]
  %output_knnId_copy.2 = alloca i65, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i65* %output_knnId_copy.2, i32 0) ]
  %output_knnId_copy.3 = alloca i33, align 512
  call void @llvm.sideeffect() #8 [ "stream_interface"(i33* %output_knnId_copy.3, i32 0) ]
  %output_knnId_copy.4.0 = alloca i9, align 512
  call void @llvm.sideeffect() #10 [ "stream_interface"(i9* %output_knnId_copy.4.0, i32 0) ]
  %output_knnId_copy.4.1 = alloca i9, align 512
  call void @llvm.sideeffect() #10 [ "stream_interface"(i9* %output_knnId_copy.4.1, i32 0) ]
  call fastcc void @copy_in(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_dist0, i45* nonnull align 512 %in_dist0_copy.0, i45* nonnull align 512 %in_dist0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_id0, i45* nonnull align 512 %in_id0_copy.0, i45* nonnull align 512 %in_id0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_dist1, i45* nonnull align 512 %in_dist1_copy.0, i45* nonnull align 512 %in_dist1_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* nonnull %in_id1, i45* nonnull align 512 %in_id1_copy.0, i45* nonnull align 512 %in_id1_copy.1, %"struct.tapa::async_mmap<float>"* nonnull %output_knnDist, i65* nonnull align 512 %output_knnDist_copy.0, i33* nonnull align 512 %output_knnDist_copy.1.0, i33* nonnull align 512 %output_knnDist_copy.1.1, i65* nonnull align 512 %output_knnDist_copy.2, i33* nonnull align 512 %output_knnDist_copy.3, i9* nonnull align 512 %output_knnDist_copy.4.0, i9* nonnull align 512 %output_knnDist_copy.4.1, %"struct.tapa::async_mmap<int>"* nonnull %output_knnId, i65* nonnull align 512 %output_knnId_copy.0, i33* nonnull align 512 %output_knnId_copy.1.0, i33* nonnull align 512 %output_knnId_copy.1.1, i65* nonnull align 512 %output_knnId_copy.2, i33* nonnull align 512 %output_knnId_copy.3, i9* nonnull align 512 %output_knnId_copy.4.0, i9* nonnull align 512 %output_knnId_copy.4.1)
  call void @apatb_krnl_globalSort_L3_hw(i45* %in_dist0_copy.0, i45* %in_dist0_copy.1, i45* %in_id0_copy.0, i45* %in_id0_copy.1, i45* %in_dist1_copy.0, i45* %in_dist1_copy.1, i45* %in_id1_copy.0, i45* %in_id1_copy.1, i65* %output_knnDist_copy.0, i33* %output_knnDist_copy.1.0, i33* %output_knnDist_copy.1.1, i65* %output_knnDist_copy.2, i33* %output_knnDist_copy.3, i9* %output_knnDist_copy.4.0, i9* %output_knnDist_copy.4.1, i65* %output_knnId_copy.0, i33* %output_knnId_copy.1.0, i33* %output_knnId_copy.1.1, i65* %output_knnId_copy.2, i33* %output_knnId_copy.3, i9* %output_knnId_copy.4.0, i9* %output_knnId_copy.4.1)
  call void @copy_back(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_dist0, i45* %in_dist0_copy.0, i45* %in_dist0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_id0, i45* %in_id0_copy.0, i45* %in_id0_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_dist1, i45* %in_dist1_copy.0, i45* %in_dist1_copy.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %in_id1, i45* %in_id1_copy.0, i45* %in_id1_copy.1, %"struct.tapa::async_mmap<float>"* %output_knnDist, i65* %output_knnDist_copy.0, i33* %output_knnDist_copy.1.0, i33* %output_knnDist_copy.1.1, i65* %output_knnDist_copy.2, i33* %output_knnDist_copy.3, i9* %output_knnDist_copy.4.0, i9* %output_knnDist_copy.4.1, %"struct.tapa::async_mmap<int>"* %output_knnId, i65* %output_knnId_copy.0, i33* %output_knnId_copy.1.0, i33* %output_knnId_copy.1.1, i65* %output_knnId_copy.2, i33* %output_knnId_copy.3, i9* %output_knnId_copy.4.0, i9* %output_knnId_copy.4.1)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.0, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %.01, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="6", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.0" %.03, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.1" %.14, %"struct.tapa::async_mmap<float>"* noalias "unpacked"="8", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.0.0" %.04, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1.0" %.15.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1.1" %.15.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.2.0" %.2, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.4.1" %.4.1, %"struct.tapa::async_mmap<int>"* noalias "unpacked"="10", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.0.0" %.05, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1.0" %.16.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1.1" %.16.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.2.0" %.27, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.3.0" %.38, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.4.0" %.4.01, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.4.1" %.4.12) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.0, i45* align 512 %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.01, i45* align 512 %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.02, i45* align 512 %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %2)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* align 512 %.03, i45* align 512 %.14, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3)
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<float>"(i65* align 512 %.04, i33* align 512 %.15.0, i33* align 512 %.15.1, i65* align 512 %.2, i33* align 512 %.3, i9* align 512 %.4.0, i9* align 512 %.4.1, %"struct.tapa::async_mmap<float>"* %4)
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<int>"(i65* align 512 %.05, i33* align 512 %.16.0, i33* align 512 %.16.1, i65* align 512 %.27, i33* align 512 %.38, i9* align 512 %.4.01, i9* align 512 %.4.12, %"struct.tapa::async_mmap<int>"* %5)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.0, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %.01, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="6", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.0" %.03, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.1" %.14, %"struct.tapa::async_mmap<float>"* noalias "unpacked"="8", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.0.0" %.04, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1.0" %.15.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1.1" %.15.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.2.0" %.2, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.4.1" %.4.1, %"struct.tapa::async_mmap<int>"* noalias "unpacked"="10", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.0.0" %.05, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1.0" %.16.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1.1" %.16.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.2.0" %.27, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.3.0" %.38, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.4.0" %.4.01, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.4.1" %.4.12) unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i45* align 512 %.0, i45* align 512 %.1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i45* align 512 %.01, i45* align 512 %.12)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %2, i45* align 512 %.02, i45* align 512 %.13)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3, i45* align 512 %.03, i45* align 512 %.14)
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<float>.23"(%"struct.tapa::async_mmap<float>"* %4, i65* align 512 %.04, i33* align 512 %.15.0, i33* align 512 %.15.1, i65* align 512 %.2, i33* align 512 %.3, i9* align 512 %.4.0, i9* align 512 %.4.1)
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<int>.75"(%"struct.tapa::async_mmap<int>"* %5, i65* align 512 %.05, i33* align 512 %.16.0, i33* align 512 %.16.1, i65* align 512 %.27, i33* align 512 %.38, i9* align 512 %.4.01, i9* align 512 %.4.12)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<float>"(i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0.0" %.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1.0" %.1.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.2.0" %.2, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.4.1" %.4.1, %"struct.tapa::async_mmap<float>"* noalias "unpacked"="1") unnamed_addr #4 {
entry:
  %1 = icmp eq %"struct.tapa::async_mmap<float>"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0.06 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.187"(i65* align 512 %.0, %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.0.06)
  %.1.08 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 1, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>.192"(i33* align 512 %.1.0, %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.1.08)
  %.1.110 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 1, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>.192"(i33* align 512 %.1.1, %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.1.110)
  %.2.012 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 2, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.187"(i65* align 512 %.2, %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.2.012)
  %.3.014 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 3, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>.192"(i33* align 512 %.3, %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.3.014)
  %.4.016 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 4, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.219"(i9* align 512 %.4.0, %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.4.016)
  %.4.118 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 4, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.219"(i9* align 512 %.4.1, %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.4.118)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<float>.23"(%"struct.tapa::async_mmap<float>"* noalias "unpacked"="0", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0.0" %.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.0" %.1.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2.0" %.2, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.1" %.4.1) unnamed_addr #4 {
entry:
  %1 = icmp eq %"struct.tapa::async_mmap<float>"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01.07 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.01.07, i65* align 512 %.0)
  %.12.09 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 1, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.12.09, i33* align 512 %.1.0)
  %.12.111 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 1, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.12.111, i33* align 512 %.1.1)
  %.23.013 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 2, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.23.013, i65* align 512 %.2)
  %.34.015 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 3, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.34.015, i33* align 512 %.3)
  %.45.017 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 4, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.45.017, i9* align 512 %.4.0)
  %.45.119 = getelementptr %"struct.tapa::async_mmap<float>", %"struct.tapa::async_mmap<float>"* %0, i32 0, i32 4, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.45.119, i9* align 512 %.4.1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<int>"(i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0.0" %.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1.0" %.1.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.2.0" %.2, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.4.1" %.4.1, %"struct.tapa::async_mmap<int>"* noalias "unpacked"="1") unnamed_addr #4 {
entry:
  %1 = icmp eq %"struct.tapa::async_mmap<int>"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0.06 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.187"(i65* align 512 %.0, %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.0.06)
  %.1.08 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 1, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>"(i33* align 512 %.1.0, %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %.1.08)
  %.1.110 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 1, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>"(i33* align 512 %.1.1, %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %.1.110)
  %.2.012 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 2, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.187"(i65* align 512 %.2, %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.2.012)
  %.3.014 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 3, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>"(i33* align 512 %.3, %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %.3.014)
  %.4.016 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 4, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.219"(i9* align 512 %.4.0, %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.4.016)
  %.4.118 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 4, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.219"(i9* align 512 %.4.1, %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.4.118)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<int>.75"(%"struct.tapa::async_mmap<int>"* noalias "unpacked"="0", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0.0" %.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.0" %.1.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1.1" %.1.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.2.0" %.2, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.4.1" %.4.1) unnamed_addr #4 {
entry:
  %1 = icmp eq %"struct.tapa::async_mmap<int>"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01.07 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.01.07, i65* align 512 %.0)
  %.12.09 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 1, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>.240"(%"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %.12.09, i33* align 512 %.1.0)
  %.12.111 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 1, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>.240"(%"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %.12.111, i33* align 512 %.1.1)
  %.23.013 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 2, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* %.23.013, i65* align 512 %.2)
  %.34.015 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 3, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>.240"(%"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %.34.015, i33* align 512 %.3)
  %.45.017 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 4, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.45.017, i9* align 512 %.4.0)
  %.45.119 = getelementptr %"struct.tapa::async_mmap<int>", %"struct.tapa::async_mmap<int>"* %0, i32 0, i32 4, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* %.45.119, i9* align 512 %.4.1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.133"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
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

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.141"(i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
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
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >.9"(i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="1") unnamed_addr #4 {
entry:
  %1 = icmp eq %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.141"(i45* align 512 %.02, %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.0)
  %.1 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.141"(i45* align 512 %.13, %"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.13) unnamed_addr #4 {
entry:
  %1 = icmp eq %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, null
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.133"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.01, i45* align 512 %.02)
  %.12 = getelementptr %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >", %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i32 0, i32 1
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>.133"(%"class.hls::stream<tapa::internal::elem_t<hls::axis<ap_uint<32>, 0, 0, 0> >, 0>"* %.12, i45* align 512 %.13)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>"(%"class.hls::stream<tapa::internal::elem_t<long>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
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
  br label %empty, !llvm.loop !7

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
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<long>, 0>.187"(i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<long>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
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
  br label %empty, !llvm.loop !7

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
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>.192"(i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca %"class.hls::stream<tapa::internal::elem_t<float>, 0>"
  %3 = alloca i33
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_8(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %2 to i8*
  %7 = bitcast %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %1 to i8*
  call void @fpga_fifo_pop_8(i8* %6, i8* %7)
  %8 = load volatile %"class.hls::stream<tapa::internal::elem_t<float>, 0>", %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %2
  %9 = call i33 @"_llvm.fpga.pack.bits.i33.s_class.hls::stream<tapa::internal::elem_t<float>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>" %8)
  store i33 %9, i33* %3
  %10 = bitcast i33* %3 to i8*
  %11 = bitcast i33* %0 to i8*
  call void @fpga_fifo_push_8(i8* %10, i8* %11)
  br label %empty, !llvm.loop !8

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i33 @"_llvm.fpga.pack.bits.i33.s_class.hls::stream<tapa::internal::elem_t<float>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>" %A) #6 {
  %A.0 = extractvalue %"class.hls::stream<tapa::internal::elem_t<float>, 0>" %A, 0
  %A.0.0 = extractvalue %"struct.tapa::internal::elem_t<float>" %A.0, 0
  %A.0.0.cast = bitcast float %A.0.0 to i32
  %1 = zext i32 %A.0.0.cast to i33
  %A.0.1 = extractvalue %"struct.tapa::internal::elem_t<float>" %A.0, 1
  %2 = zext i1 %A.0.1 to i33
  %3 = shl i33 %2, 32
  %4 = or i33 %3, %1
  ret i33 %4
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca i33
  %3 = alloca %"class.hls::stream<tapa::internal::elem_t<float>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast i33* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_8(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast i33* %2 to i8*
  %7 = bitcast i33* %1 to i8*
  call void @fpga_fifo_pop_8(i8* %6, i8* %7)
  %8 = bitcast i33* %2 to i40*
  %9 = load i40, i40* %8
  %10 = trunc i40 %9 to i33
  %11 = call { float, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<float>, 0>s.i33"(i33 %10)
  %newret = extractvalue { float, i1 } %11, 0
  %oldret1 = insertvalue %"struct.tapa::internal::elem_t<float>" undef, float %newret, 0
  %newret2 = extractvalue { float, i1 } %11, 1
  %oldret3 = insertvalue %"struct.tapa::internal::elem_t<float>" %oldret1, i1 %newret2, 1
  %oldret = insertvalue %"class.hls::stream<tapa::internal::elem_t<float>, 0>" undef, %"struct.tapa::internal::elem_t<float>" %oldret3, 0
  store %"class.hls::stream<tapa::internal::elem_t<float>, 0>" %oldret, %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %3
  %12 = bitcast %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %3 to i8*
  %13 = bitcast %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %0 to i8*
  call void @fpga_fifo_push_8(i8* %12, i8* %13)
  br label %empty, !llvm.loop !8

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal { float, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<float>, 0>s.i33"(i33 %A) #6 {
  %1 = trunc i33 %A to i32
  %.0.cast = bitcast i32 %1 to float
  %2 = lshr i33 %A, 32
  %3 = trunc i33 %2 to i1
  %newret = insertvalue { float, i1 } undef, float %.0.cast, 0
  %newret2 = insertvalue { float, i1 } %newret, i1 %3, 1
  ret { float, i1 } %newret2
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"(%"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
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
  br label %empty, !llvm.loop !9

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
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>.219"(i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<unsigned char>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
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
  br label %empty, !llvm.loop !9

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
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>.240"(%"class.hls::stream<tapa::internal::elem_t<int>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed", i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca i33
  %3 = alloca %"class.hls::stream<tapa::internal::elem_t<int>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast i33* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_8(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast i33* %2 to i8*
  %7 = bitcast i33* %1 to i8*
  call void @fpga_fifo_pop_8(i8* %6, i8* %7)
  %8 = bitcast i33* %2 to i40*
  %9 = load i40, i40* %8
  %10 = trunc i40 %9 to i33
  %11 = call { i32, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<int>, 0>s.i33"(i33 %10)
  %newret = extractvalue { i32, i1 } %11, 0
  %oldret1 = insertvalue %"struct.tapa::internal::elem_t<int>" undef, i32 %newret, 0
  %newret2 = extractvalue { i32, i1 } %11, 1
  %oldret3 = insertvalue %"struct.tapa::internal::elem_t<int>" %oldret1, i1 %newret2, 1
  %oldret = insertvalue %"class.hls::stream<tapa::internal::elem_t<int>, 0>" undef, %"struct.tapa::internal::elem_t<int>" %oldret3, 0
  store %"class.hls::stream<tapa::internal::elem_t<int>, 0>" %oldret, %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %3
  %12 = bitcast %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %3 to i8*
  %13 = bitcast %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %0 to i8*
  call void @fpga_fifo_push_8(i8* %12, i8* %13)
  br label %empty, !llvm.loop !10

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal { i32, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<int>, 0>s.i33"(i33 %A) #6 {
  %1 = trunc i33 %A to i32
  %2 = lshr i33 %A, 32
  %3 = trunc i33 %2 to i1
  %newret = insertvalue { i32, i1 } undef, i32 %1, 0
  %newret2 = insertvalue { i32, i1 } %newret, i1 %3, 1
  ret { i32, i1 } %newret2
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<int>, 0>"(i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
entry:
  %2 = alloca %"class.hls::stream<tapa::internal::elem_t<int>, 0>"
  %3 = alloca i33
  br label %empty

empty:                                            ; preds = %push, %entry
  %4 = bitcast %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %1 to i8*
  %5 = call i1 @fpga_fifo_not_empty_8(i8* %4)
  br i1 %5, label %push, label %ret

push:                                             ; preds = %empty
  %6 = bitcast %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %2 to i8*
  %7 = bitcast %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %1 to i8*
  call void @fpga_fifo_pop_8(i8* %6, i8* %7)
  %8 = load volatile %"class.hls::stream<tapa::internal::elem_t<int>, 0>", %"class.hls::stream<tapa::internal::elem_t<int>, 0>"* %2
  %9 = call i33 @"_llvm.fpga.pack.bits.i33.s_class.hls::stream<tapa::internal::elem_t<int>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<int>, 0>" %8)
  store i33 %9, i33* %3
  %10 = bitcast i33* %3 to i8*
  %11 = bitcast i33* %0 to i8*
  call void @fpga_fifo_push_8(i8* %10, i8* %11)
  br label %empty, !llvm.loop !10

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i33 @"_llvm.fpga.pack.bits.i33.s_class.hls::stream<tapa::internal::elem_t<int>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<int>, 0>" %A) #6 {
  %A.0 = extractvalue %"class.hls::stream<tapa::internal::elem_t<int>, 0>" %A, 0
  %A.0.0 = extractvalue %"struct.tapa::internal::elem_t<int>" %A.0, 0
  %1 = zext i32 %A.0.0 to i33
  %A.0.1 = extractvalue %"struct.tapa::internal::elem_t<int>" %A.0, 1
  %2 = zext i1 %A.0.1 to i33
  %3 = shl i33 %2, 32
  %4 = or i33 %3, %1
  ret i33 %4
}

declare void @apatb_krnl_globalSort_L3_hw(i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i65*, i33*, i33*, i65*, i33*, i9*, i9*, i65*, i33*, i33*, i65*, i33*, i9*, i9*)

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_back(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="0", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0" %.0, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.1" %.1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="2", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0" %.01, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.1" %.12, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="4", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.0" %.02, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="5.1" %.13, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* noalias "unpacked"="6", i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.0" %.03, i45* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="7.1" %.14, %"struct.tapa::async_mmap<float>"* noalias "unpacked"="8", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.0.0" %.04, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1.0" %.15.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.1.1" %.15.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.2.0" %.2, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.3.0" %.3, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.4.0" %.4.0, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="9.4.1" %.4.1, %"struct.tapa::async_mmap<int>"* noalias "unpacked"="10", i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.0.0" %.05, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1.0" %.16.0, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.1.1" %.16.1, i65* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.2.0" %.27, i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.3.0" %.38, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.4.0" %.4.01, i9* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="11.4.1" %.4.12) unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %0, i45* align 512 %.0, i45* align 512 %.1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %1, i45* align 512 %.01, i45* align 512 %.12)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %2, i45* align 512 %.02, i45* align 512 %.13)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %3, i45* align 512 %.03, i45* align 512 %.14)
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<float>.23"(%"struct.tapa::async_mmap<float>"* %4, i65* align 512 %.04, i33* align 512 %.15.0, i33* align 512 %.15.1, i65* align 512 %.2, i33* align 512 %.3, i9* align 512 %.4.0, i9* align 512 %.4.1)
  call fastcc void @"onebyonecpy_hls.p0struct.tapa::async_mmap<int>.75"(%"struct.tapa::async_mmap<int>"* %5, i65* align 512 %.05, i33* align 512 %.16.0, i33* align 512 %.16.1, i65* align 512 %.27, i33* align 512 %.38, i9* align 512 %.4.01, i9* align 512 %.4.12)
  ret void
}

define void @krnl_globalSort_L3_hw_stub_wrapper(i45*, i45*, i45*, i45*, i45*, i45*, i45*, i45*, i65*, i33*, i33*, i65*, i33*, i9*, i9*, i65*, i33*, i33*, i65*, i33*, i9*, i9*) #7 {
entry:
  %22 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %23 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %24 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %25 = alloca %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"
  %26 = alloca %"struct.tapa::async_mmap<float>"
  %27 = alloca %"struct.tapa::async_mmap<int>"
  call void @copy_out(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %22, i45* %0, i45* %1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %23, i45* %2, i45* %3, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %24, i45* %4, i45* %5, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %25, i45* %6, i45* %7, %"struct.tapa::async_mmap<float>"* %26, i65* %8, i33* %9, i33* %10, i65* %11, i33* %12, i9* %13, i9* %14, %"struct.tapa::async_mmap<int>"* %27, i65* %15, i33* %16, i33* %17, i65* %18, i33* %19, i9* %20, i9* %21)
  call void @krnl_globalSort_L3_hw_stub(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %22, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %23, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %24, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %25, %"struct.tapa::async_mmap<float>"* %26, %"struct.tapa::async_mmap<int>"* %27)
  call void @copy_in(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %22, i45* %0, i45* %1, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %23, i45* %2, i45* %3, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %24, i45* %4, i45* %5, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"* %25, i45* %6, i45* %7, %"struct.tapa::async_mmap<float>"* %26, i65* %8, i33* %9, i33* %10, i65* %11, i33* %12, i9* %13, i9* %14, %"struct.tapa::async_mmap<int>"* %27, i65* %15, i33* %16, i33* %17, i65* %18, i33* %19, i9* %20, i9* %21)
  ret void
}

declare void @krnl_globalSort_L3_hw_stub(%"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"class.tapa::istream<hls::axis<ap_uint<32>, 0, 0, 0> >"*, %"struct.tapa::async_mmap<float>"*, %"struct.tapa::async_mmap<int>"*)

declare i1 @fpga_fifo_not_empty_16(i8*)

declare i1 @fpga_fifo_not_empty_8(i8*)

declare i1 @fpga_fifo_not_empty_2(i8*)

declare void @fpga_fifo_pop_16(i8*, i8*)

declare void @fpga_fifo_pop_8(i8*, i8*)

declare void @fpga_fifo_pop_2(i8*, i8*)

declare void @fpga_fifo_push_16(i8*, i8*)

declare void @fpga_fifo_push_8(i8*, i8*)

declare void @fpga_fifo_push_2(i8*, i8*)

attributes #0 = { inaccessiblememonly nounwind }
attributes #1 = { inaccessiblemem_or_argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #2 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #3 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #5 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #6 = { alwaysinline nounwind readnone }
attributes #7 = { "fpga.wrapper.func"="stub" }
attributes #8 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="64" }
attributes #9 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="128" }
attributes #10 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="16" }

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
!10 = distinct !{!10, !6}
