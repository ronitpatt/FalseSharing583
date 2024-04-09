; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { i32 }
%struct.cpadded = type { i32, [60 x i8] }

@.str = private unnamed_addr constant [25 x i8] c"-----------------------\0A\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"%d %d \0A\00", align 1

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [4 x %struct.cpadded], align 16
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store ptr %2, ptr %3, align 8
  store i32 0, ptr %4, align 4
  br label %6

6:                                                ; preds = %14, %0
  %7 = load i32, ptr %4, align 4
  %8 = icmp slt i32 %7, 4
  br i1 %8, label %9, label %17

9:                                                ; preds = %6
  %10 = load i32, ptr %4, align 4
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds [4 x %struct.cpadded], ptr %2, i64 0, i64 %11
  %13 = getelementptr inbounds %struct.cpadded, ptr %12, i32 0, i32 0
  store i32 888, ptr %13, align 4
  br label %14

14:                                               ; preds = %9
  %15 = load i32, ptr %4, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, ptr %4, align 4
  br label %6, !llvm.loop !6

17:                                               ; preds = %6
  store i32 0, ptr %5, align 4
  br label %18

18:                                               ; preds = %36, %17
  %19 = load i32, ptr %5, align 4
  %20 = icmp slt i32 %19, 256
  br i1 %20, label %21, label %39

21:                                               ; preds = %18
  %22 = load i32, ptr %5, align 4
  %23 = mul nsw i32 %22, 4
  %24 = srem i32 %23, 64
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %26, label %28

26:                                               ; preds = %21
  %27 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  br label %28

28:                                               ; preds = %26, %21
  %29 = load i32, ptr %5, align 4
  %30 = load ptr, ptr %3, align 8
  %31 = load i32, ptr %5, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds i32, ptr %30, i64 %32
  %34 = load i32, ptr %33, align 4
  %35 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %29, i32 noundef %34)
  br label %36

36:                                               ; preds = %28
  %37 = load i32, ptr %5, align 4
  %38 = add nsw i32 %37, 1
  store i32 %38, ptr %5, align 4
  br label %18, !llvm.loop !8

39:                                               ; preds = %18
  ret i32 1
}

declare i32 @printf(ptr noundef, ...) #1

attributes #0 = { mustprogress noinline norecurse uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.6"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
