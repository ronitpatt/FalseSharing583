; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { [4 x i32], [4 x i32], [4 x i32] }

@obj = dso_local global %struct.c zeroinitializer, align 4
@.str = private unnamed_addr constant [13 x i8] c"%d %d %d %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [11 x i8] c"%d %d %d \0A\00", align 1

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca ptr, align 8
  %7 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 1, ptr @obj, align 4
  store i32 2, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 1), align 4
  store i32 3, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 2), align 4
  store i32 4, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 3), align 4
  store i32 5, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 1), align 4
  store i32 6, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 1, i64 1), align 4
  store i32 7, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 1, i64 2), align 4
  store i32 8, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 1, i64 3), align 4
  store i32 5, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 2), align 4
  store i32 6, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 2, i64 1), align 4
  store i32 7, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 2, i64 2), align 4
  store i32 8, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 2, i64 3), align 4
  %8 = load i32, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 1), align 4
  store i32 %8, ptr %2, align 4
  %9 = load i32, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 2), align 4
  store i32 %9, ptr %3, align 4
  %10 = load i32, ptr getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 3), align 4
  store i32 %10, ptr %4, align 4
  %11 = load i32, ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 1), align 4
  store i32 %11, ptr %5, align 4
  %12 = load i32, ptr %2, align 4
  %13 = load i32, ptr %3, align 4
  %14 = load i32, ptr %4, align 4
  %15 = load i32, ptr %5, align 4
  %16 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %12, i32 noundef %13, i32 noundef %14, i32 noundef %15)
  store ptr @obj, ptr %6, align 8
  store i32 0, ptr %7, align 4
  br label %17

17:                                               ; preds = %33, %0
  %18 = load i32, ptr %7, align 4
  %19 = icmp slt i32 %18, 4
  br i1 %19, label %20, label %36

20:                                               ; preds = %17
  %21 = load ptr, ptr %6, align 8
  %22 = getelementptr inbounds i32, ptr %21, i64 0
  %23 = load i32, ptr %22, align 4
  %24 = load ptr, ptr %6, align 8
  %25 = getelementptr inbounds i32, ptr %24, i64 1
  %26 = load i32, ptr %25, align 4
  %27 = load ptr, ptr %6, align 8
  %28 = getelementptr inbounds i32, ptr %27, i64 2
  %29 = load i32, ptr %28, align 4
  %30 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %23, i32 noundef %26, i32 noundef %29)
  %31 = load ptr, ptr %6, align 8
  %32 = getelementptr inbounds i32, ptr %31, i64 3
  store ptr %32, ptr %6, align 8
  br label %33

33:                                               ; preds = %20
  %34 = load i32, ptr %7, align 4
  %35 = add nsw i32 %34, 1
  store i32 %35, ptr %7, align 4
  br label %17, !llvm.loop !6

36:                                               ; preds = %17
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
