; ModuleID = 'simple.profdata.bc'
source_filename = "src/simple.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [24 x i8] c"Should Not Be Printed!\0A\00", align 1
@.str.1 = private unnamed_addr constant [24 x i8] c"Elements of the array:\0A\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.3 = private unnamed_addr constant [20 x i8] c"Should Be Printed!\0A\00", align 1

; Function Attrs: cold noinline nounwind uwtable
define dso_local void @never_executed() #0 !prof !35 {
  %1 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: cold noinline nounwind uwtable
define dso_local i32 @iAdd(i32 noundef %0, i32 noundef %1) #0 !prof !35 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %5 = load i32, ptr %3, align 4
  %6 = load i32, ptr %4, align 4
  %7 = add nsw i32 %5, %6
  ret i32 %7
}

; Function Attrs: cold noinline nounwind uwtable
define dso_local float @fAdd(float noundef %0, float noundef %1) #0 !prof !35 {
  %3 = alloca float, align 4
  %4 = alloca float, align 4
  store float %0, ptr %3, align 4
  store float %1, ptr %4, align 4
  %5 = load float, ptr %3, align 4
  %6 = load float, ptr %4, align 4
  %7 = fadd float %5, %6
  ret float %7
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #2 !prof !36 {
  %1 = alloca i32, align 4
  %2 = alloca [200 x i32], align 16
  %3 = alloca [200 x i32], align 16
  %4 = alloca [200 x float], align 16
  %5 = alloca [200 x float], align 16
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  %8 = alloca i64, align 8
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  call void @llvm.memset.p0.i64(ptr align 16 %2, i8 0, i64 800, i1 false)
  call void @llvm.memset.p0.i64(ptr align 16 %3, i8 0, i64 800, i1 false)
  %11 = getelementptr inbounds <{ i32, [199 x i32] }>, ptr %3, i32 0, i32 0
  store i32 1, ptr %11, align 16
  call void @llvm.memset.p0.i64(ptr align 16 %4, i8 0, i64 800, i1 false)
  %12 = getelementptr inbounds <{ float, [199 x float] }>, ptr %4, i32 0, i32 0
  store float 0x3FB99999A0000000, ptr %12, align 16
  call void @llvm.memset.p0.i64(ptr align 16 %5, i8 0, i64 800, i1 false)
  %13 = getelementptr inbounds <{ float, [199 x float] }>, ptr %5, i32 0, i32 0
  store float 0x40099999A0000000, ptr %13, align 16
  store i32 5, ptr %6, align 4
  %14 = load i32, ptr %6, align 4
  %15 = zext i32 %14 to i64
  %16 = call ptr @llvm.stacksave()
  store ptr %16, ptr %7, align 8
  %17 = alloca i32, i64 %15, align 16
  store i64 %15, ptr %8, align 8
  store i32 0, ptr %9, align 4
  br label %18

18:                                               ; preds = %27, %0
  %19 = load i32, ptr %9, align 4
  %20 = load i32, ptr %6, align 4
  %21 = icmp slt i32 %19, %20
  br i1 %21, label %22, label %30, !prof !37

22:                                               ; preds = %18
  %23 = load i32, ptr %9, align 4
  %24 = load i32, ptr %9, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds i32, ptr %17, i64 %25
  store i32 %23, ptr %26, align 4
  br label %27

27:                                               ; preds = %22
  %28 = load i32, ptr %9, align 4
  %29 = add nsw i32 %28, 1
  store i32 %29, ptr %9, align 4
  br label %18, !llvm.loop !38

30:                                               ; preds = %18
  %31 = call i32 (ptr, ...) @printf(ptr noundef @.str.1)
  store i32 0, ptr %10, align 4
  br label %32

32:                                               ; preds = %42, %30
  %33 = load i32, ptr %10, align 4
  %34 = load i32, ptr %6, align 4
  %35 = icmp slt i32 %33, %34
  br i1 %35, label %36, label %45, !prof !37

36:                                               ; preds = %32
  %37 = load i32, ptr %10, align 4
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds i32, ptr %17, i64 %38
  %40 = load i32, ptr %39, align 4
  %41 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %40)
  br label %42

42:                                               ; preds = %36
  %43 = load i32, ptr %10, align 4
  %44 = add nsw i32 %43, 1
  store i32 %44, ptr %10, align 4
  br label %32, !llvm.loop !40

45:                                               ; preds = %32
  %46 = call i32 (ptr, ...) @printf(ptr noundef @.str.3)
  store i32 0, ptr %1, align 4
  %47 = load ptr, ptr %7, align 8
  call void @llvm.stackrestore(ptr %47)
  %48 = load i32, ptr %1, align 4
  ret i32 %48
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #3

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare ptr @llvm.stacksave() #4

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare void @llvm.stackrestore(ptr) #4

attributes #0 = { cold noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #4 = { nocallback nofree nosync nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5}
!llvm.ident = !{!34}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{i32 1, !"ProfileSummary", !6}
!6 = !{!7, !8, !9, !10, !11, !12, !13, !14, !15, !16}
!7 = !{!"ProfileFormat", !"InstrProf"}
!8 = !{!"TotalCount", i64 11}
!9 = !{!"MaxCount", i64 5}
!10 = !{!"MaxInternalCount", i64 5}
!11 = !{!"MaxFunctionCount", i64 5}
!12 = !{!"NumCounts", i64 6}
!13 = !{!"NumFunctions", i64 4}
!14 = !{!"IsPartialProfile", i64 0}
!15 = !{!"PartialProfileRatio", double 0.000000e+00}
!16 = !{!"DetailedSummary", !17}
!17 = !{!18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33}
!18 = !{i32 10000, i64 0, i32 0}
!19 = !{i32 100000, i64 5, i32 2}
!20 = !{i32 200000, i64 5, i32 2}
!21 = !{i32 300000, i64 5, i32 2}
!22 = !{i32 400000, i64 5, i32 2}
!23 = !{i32 500000, i64 5, i32 2}
!24 = !{i32 600000, i64 5, i32 2}
!25 = !{i32 700000, i64 5, i32 2}
!26 = !{i32 800000, i64 5, i32 2}
!27 = !{i32 900000, i64 5, i32 2}
!28 = !{i32 950000, i64 5, i32 2}
!29 = !{i32 990000, i64 5, i32 2}
!30 = !{i32 999000, i64 5, i32 2}
!31 = !{i32 999900, i64 5, i32 2}
!32 = !{i32 999990, i64 5, i32 2}
!33 = !{i32 999999, i64 5, i32 2}
!34 = !{!"clang version 17.0.6"}
!35 = !{!"function_entry_count", i64 0}
!36 = !{!"function_entry_count", i64 1}
!37 = !{!"branch_weights", i32 5, i32 1}
!38 = distinct !{!38, !39}
!39 = !{!"llvm.loop.mustprogress"}
!40 = distinct !{!40, !39}
