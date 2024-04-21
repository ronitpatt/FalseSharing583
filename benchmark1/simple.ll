; ModuleID = 'simple.profdata.bc'
source_filename = "src/simple.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [24 x i8] c"Should Not Be Printed!\0A\00", align 1
@.str.1 = private unnamed_addr constant [55 x i8] c"Memory addresses of each element in the 'test' array:\0A\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"test[%d]: %p\0A\00", align 1
@.str.3 = private unnamed_addr constant [15 x i8] c"testa[%d]: %p\0A\00", align 1
@.str.4 = private unnamed_addr constant [24 x i8] c"Elements of the array:\0A\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.6 = private unnamed_addr constant [20 x i8] c"Should Be Printed!\0A\00", align 1

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
  %2 = alloca i32, align 4
  %3 = alloca [5 x i32], align 16
  %4 = alloca [5 x i32], align 16
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 5, ptr %2, align 4
  call void @llvm.memset.p0.i64(ptr align 16 %3, i8 0, i64 20, i1 false)
  call void @llvm.memset.p0.i64(ptr align 16 %4, i8 0, i64 20, i1 false)
  store ptr %3, ptr %5, align 8
  store i32 0, ptr %6, align 4
  br label %11

11:                                               ; preds = %25, %0
  %12 = load i32, ptr %6, align 4
  %13 = load i32, ptr %2, align 4
  %14 = icmp slt i32 %12, %13
  br i1 %14, label %15, label %28, !prof !37

15:                                               ; preds = %11
  %16 = load i32, ptr %6, align 4
  %17 = load i32, ptr %6, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [5 x i32], ptr %3, i64 0, i64 %18
  store i32 %16, ptr %19, align 4
  %20 = load i32, ptr %6, align 4
  %21 = mul nsw i32 %20, 2
  %22 = load i32, ptr %6, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds [5 x i32], ptr %4, i64 0, i64 %23
  store i32 %21, ptr %24, align 4
  br label %25

25:                                               ; preds = %15
  %26 = load i32, ptr %6, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, ptr %6, align 4
  br label %11, !llvm.loop !38

28:                                               ; preds = %11
  %29 = call i32 (ptr, ...) @printf(ptr noundef @.str.1)
  store i32 0, ptr %7, align 4
  br label %30

30:                                               ; preds = %40, %28
  %31 = load i32, ptr %7, align 4
  %32 = load i32, ptr %2, align 4
  %33 = icmp slt i32 %31, %32
  br i1 %33, label %34, label %43, !prof !37

34:                                               ; preds = %30
  %35 = load i32, ptr %7, align 4
  %36 = load i32, ptr %7, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds [5 x i32], ptr %3, i64 0, i64 %37
  %39 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %35, ptr noundef %38)
  br label %40

40:                                               ; preds = %34
  %41 = load i32, ptr %7, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, ptr %7, align 4
  br label %30, !llvm.loop !40

43:                                               ; preds = %30
  store i32 0, ptr %8, align 4
  br label %44

44:                                               ; preds = %54, %43
  %45 = load i32, ptr %8, align 4
  %46 = load i32, ptr %2, align 4
  %47 = icmp slt i32 %45, %46
  br i1 %47, label %48, label %57, !prof !37

48:                                               ; preds = %44
  %49 = load i32, ptr %8, align 4
  %50 = load i32, ptr %8, align 4
  %51 = sext i32 %50 to i64
  %52 = getelementptr inbounds [5 x i32], ptr %4, i64 0, i64 %51
  %53 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %49, ptr noundef %52)
  br label %54

54:                                               ; preds = %48
  %55 = load i32, ptr %8, align 4
  %56 = add nsw i32 %55, 1
  store i32 %56, ptr %8, align 4
  br label %44, !llvm.loop !41

57:                                               ; preds = %44
  %58 = call i32 (ptr, ...) @printf(ptr noundef @.str.4)
  store i32 0, ptr %9, align 4
  br label %59

59:                                               ; preds = %69, %57
  %60 = load i32, ptr %9, align 4
  %61 = load i32, ptr %2, align 4
  %62 = icmp slt i32 %60, %61
  br i1 %62, label %63, label %72, !prof !37

63:                                               ; preds = %59
  %64 = load i32, ptr %9, align 4
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds [5 x i32], ptr %3, i64 0, i64 %65
  %67 = load i32, ptr %66, align 4
  %68 = call i32 (ptr, ...) @printf(ptr noundef @.str.5, i32 noundef %67)
  br label %69

69:                                               ; preds = %63
  %70 = load i32, ptr %9, align 4
  %71 = add nsw i32 %70, 1
  store i32 %71, ptr %9, align 4
  br label %59, !llvm.loop !42

72:                                               ; preds = %59
  store i32 0, ptr %10, align 4
  br label %73

73:                                               ; preds = %83, %72
  %74 = load i32, ptr %10, align 4
  %75 = load i32, ptr %2, align 4
  %76 = icmp slt i32 %74, %75
  br i1 %76, label %77, label %86, !prof !37

77:                                               ; preds = %73
  %78 = load i32, ptr %10, align 4
  %79 = sext i32 %78 to i64
  %80 = getelementptr inbounds [5 x i32], ptr %4, i64 0, i64 %79
  %81 = load i32, ptr %80, align 4
  %82 = call i32 (ptr, ...) @printf(ptr noundef @.str.5, i32 noundef %81)
  br label %83

83:                                               ; preds = %77
  %84 = load i32, ptr %10, align 4
  %85 = add nsw i32 %84, 1
  store i32 %85, ptr %10, align 4
  br label %73, !llvm.loop !43

86:                                               ; preds = %73
  %87 = call i32 (ptr, ...) @printf(ptr noundef @.str.6)
  ret i32 0
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #3

attributes #0 = { cold noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nocallback nofree nounwind willreturn memory(argmem: write) }

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
!8 = !{!"TotalCount", i64 26}
!9 = !{!"MaxCount", i64 5}
!10 = !{!"MaxInternalCount", i64 5}
!11 = !{!"MaxFunctionCount", i64 5}
!12 = !{!"NumCounts", i64 9}
!13 = !{!"NumFunctions", i64 4}
!14 = !{!"IsPartialProfile", i64 0}
!15 = !{!"PartialProfileRatio", double 0.000000e+00}
!16 = !{!"DetailedSummary", !17}
!17 = !{!18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33}
!18 = !{i32 10000, i64 0, i32 0}
!19 = !{i32 100000, i64 5, i32 5}
!20 = !{i32 200000, i64 5, i32 5}
!21 = !{i32 300000, i64 5, i32 5}
!22 = !{i32 400000, i64 5, i32 5}
!23 = !{i32 500000, i64 5, i32 5}
!24 = !{i32 600000, i64 5, i32 5}
!25 = !{i32 700000, i64 5, i32 5}
!26 = !{i32 800000, i64 5, i32 5}
!27 = !{i32 900000, i64 5, i32 5}
!28 = !{i32 950000, i64 5, i32 5}
!29 = !{i32 990000, i64 5, i32 5}
!30 = !{i32 999000, i64 5, i32 5}
!31 = !{i32 999900, i64 5, i32 5}
!32 = !{i32 999990, i64 5, i32 5}
!33 = !{i32 999999, i64 5, i32 5}
!34 = !{!"clang version 17.0.6"}
!35 = !{!"function_entry_count", i64 0}
!36 = !{!"function_entry_count", i64 1}
!37 = !{!"branch_weights", i32 5, i32 1}
!38 = distinct !{!38, !39}
!39 = !{!"llvm.loop.mustprogress"}
!40 = distinct !{!40, !39}
!41 = distinct !{!41, !39}
!42 = distinct !{!42, !39}
!43 = distinct !{!43, !39}
