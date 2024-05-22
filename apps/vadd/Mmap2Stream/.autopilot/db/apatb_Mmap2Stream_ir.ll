; ModuleID = '/tmp/run-hls-Mmap2Stream-e7a2xhrl/project/Mmap2Stream/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"class.tapa::ostream<float>" = type { %"class.hls::stream<tapa::internal::elem_t<float>, 0>" }
%"class.hls::stream<tapa::internal::elem_t<float>, 0>" = type { %"struct.tapa::internal::elem_t<float>" }
%"struct.tapa::internal::elem_t<float>" = type { float, i1 }

; Function Attrs: inaccessiblememonly nounwind
declare void @llvm.sideeffect() #0

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_Mmap2Stream_ir(float* noalias nocapture nonnull readonly %mmap, i64 %n, %"class.tapa::ostream<float>"* noalias nocapture nonnull dereferenceable(8) %stream) local_unnamed_addr #1 {
entry:
  %mmap_copy = alloca float, align 512
  %stream_copy = alloca i33, align 512
  call void @llvm.sideeffect() #9 [ "stream_interface"(i33* %stream_copy, i32 0) ]
  call fastcc void @copy_in(float* nonnull %mmap, float* nonnull align 512 %mmap_copy, %"class.tapa::ostream<float>"* nonnull %stream, i33* nonnull align 512 %stream_copy)
  call void @apatb_Mmap2Stream_hw(float* %mmap_copy, i64 %n, i33* %stream_copy)
  call void @copy_back(float* %mmap, float* %mmap_copy, %"class.tapa::ostream<float>"* %stream, i33* %stream_copy)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in(float* noalias readonly "unpacked"="0", float* noalias align 512 "unpacked"="1", %"class.tapa::ostream<float>"* noalias "unpacked"="2", i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0") unnamed_addr #2 {
entry:
  call fastcc void @onebyonecpy_hls.p0f32(float* align 512 %1, float* %0)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<float>"(i33* align 512 %3, %"class.tapa::ostream<float>"* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0f32(float* noalias align 512, float* noalias readonly) unnamed_addr #3 {
entry:
  %2 = icmp eq float* %0, null
  %3 = icmp eq float* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %5 = load float, float* %1, align 4
  store float %5, float* %0, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<float>"(i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="0.0", %"class.tapa::ostream<float>"* noalias "unpacked"="1") unnamed_addr #4 {
entry:
  %2 = icmp eq %"class.tapa::ostream<float>"* %1, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0 = getelementptr %"class.tapa::ostream<float>", %"class.tapa::ostream<float>"* %1, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>.12"(i33* align 512 %0, %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.0)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
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
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out(float* noalias "unpacked"="0", float* noalias readonly align 512 "unpacked"="1", %"class.tapa::ostream<float>"* noalias "unpacked"="2", i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0") unnamed_addr #6 {
entry:
  call fastcc void @onebyonecpy_hls.p0f32(float* %0, float* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<float>.4"(%"class.tapa::ostream<float>"* %2, i33* align 512 %3)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<float>.4"(%"class.tapa::ostream<float>"* noalias "unpacked"="0", i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="1.0") unnamed_addr #4 {
entry:
  %2 = icmp eq %"class.tapa::ostream<float>"* %0, null
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %.01 = getelementptr %"class.tapa::ostream<float>", %"class.tapa::ostream<float>"* %0, i32 0, i32 0
  call fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>"* %.01, i33* align 512 %1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<tapa::internal::elem_t<float>, 0>.12"(i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed", %"class.hls::stream<tapa::internal::elem_t<float>, 0>"* noalias nocapture "fpga.caller.interfaces"="layout_transformed") unnamed_addr #5 {
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
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: alwaysinline nounwind readnone
define internal i33 @"_llvm.fpga.pack.bits.i33.s_class.hls::stream<tapa::internal::elem_t<float>, 0>s"(%"class.hls::stream<tapa::internal::elem_t<float>, 0>" %A) #7 {
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

; Function Attrs: alwaysinline nounwind readnone
define internal { float, i1 } @"_llvm.fpga.unpack.bits.s_class.hls::stream<tapa::internal::elem_t<float>, 0>s.i33"(i33 %A) #7 {
  %1 = trunc i33 %A to i32
  %.0.cast = bitcast i32 %1 to float
  %2 = lshr i33 %A, 32
  %3 = trunc i33 %2 to i1
  %newret = insertvalue { float, i1 } undef, float %.0.cast, 0
  %newret2 = insertvalue { float, i1 } %newret, i1 %3, 1
  ret { float, i1 } %newret2
}

declare void @apatb_Mmap2Stream_hw(float*, i64, i33*)

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_back(float* noalias "unpacked"="0", float* noalias readonly align 512 "unpacked"="1", %"class.tapa::ostream<float>"* noalias "unpacked"="2", i33* noalias nocapture align 512 "fpga.caller.interfaces"="layout_transformed" "unpacked"="3.0") unnamed_addr #6 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.tapa::ostream<float>.4"(%"class.tapa::ostream<float>"* %2, i33* align 512 %3)
  ret void
}

define void @Mmap2Stream_hw_stub_wrapper(float*, i64, i33*) #8 {
entry:
  %3 = alloca %"class.tapa::ostream<float>"
  call void @copy_out(float* null, float* %0, %"class.tapa::ostream<float>"* %3, i33* %2)
  call void @Mmap2Stream_hw_stub(float* %0, i64 %1, %"class.tapa::ostream<float>"* %3)
  call void @copy_in(float* null, float* %0, %"class.tapa::ostream<float>"* %3, i33* %2)
  ret void
}

declare void @Mmap2Stream_hw_stub(float*, i64, %"class.tapa::ostream<float>"*)

declare i1 @fpga_fifo_not_empty_8(i8*)

declare void @fpga_fifo_pop_8(i8*, i8*)

declare void @fpga_fifo_push_8(i8*, i8*)

attributes #0 = { inaccessiblememonly nounwind }
attributes #1 = { inaccessiblemem_or_argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #2 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #5 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #6 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #7 = { alwaysinline nounwind readnone }
attributes #8 = { "fpga.wrapper.func"="stub" }
attributes #9 = { inaccessiblememonly nounwind "xlx.port.bitwidth"="64" }

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
