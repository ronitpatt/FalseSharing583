; ModuleID = 'temp.cpp'
source_filename = "temp.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c_elem = type { i32, i32, i32 }

@arr = dso_local global [4 x %struct.c_elem] zeroinitializer, align 16
@.str = private unnamed_addr constant [11 x i8] c"%d %d %d \0A\00", align 1

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 1, ptr @arr, align 16
  store i32 2, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 1), align 4
  store i32 3, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 2), align 8
  store i32 4, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 3), align 4
  store i32 5, ptr getelementptr inbounds (%struct.c_elem, ptr @arr, i32 0, i32 1), align 4
  store i32 6, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 1, i32 1), align 4
  store i32 7, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 2, i32 1), align 4
  store i32 8, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 3, i32 1), align 4
  store i32 9, ptr getelementptr inbounds (%struct.c_elem, ptr @arr, i32 0, i32 2), align 8
  store i32 10, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 1, i32 2), align 4
  store i32 11, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 2, i32 2), align 8
  store i32 12, ptr getelementptr inbounds ([4 x %struct.c_elem], ptr @arr, i64 0, i64 3, i32 2), align 4
  store ptr @arr, ptr %2, align 8
  store i32 0, ptr %3, align 4
  br label %4

4:                                                ; preds = %20, %0
  %5 = load i32, ptr %3, align 4
  %6 = icmp slt i32 %5, 4
  br i1 %6, label %7, label %23

7:                                                ; preds = %4
  %8 = load ptr, ptr %2, align 8
  %9 = getelementptr inbounds i32, ptr %8, i64 0
  %10 = load i32, ptr %9, align 4
  %11 = load ptr, ptr %2, align 8
  %12 = getelementptr inbounds i32, ptr %11, i64 1
  %13 = load i32, ptr %12, align 4
  %14 = load ptr, ptr %2, align 8
  %15 = getelementptr inbounds i32, ptr %14, i64 2
  %16 = load i32, ptr %15, align 4
  %17 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %10, i32 noundef %13, i32 noundef %16)
  %18 = load ptr, ptr %2, align 8
  %19 = getelementptr inbounds i32, ptr %18, i64 3
  store ptr %19, ptr %2, align 8
  br label %20

20:                                               ; preds = %7
  %21 = load i32, ptr %3, align 4
  %22 = add nsw i32 %21, 1
  store i32 %22, ptr %3, align 4
  br label %4, !llvm.loop !6

23:                                               ; preds = %4
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
