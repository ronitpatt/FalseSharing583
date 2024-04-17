; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { [4 x i32], [4 x i32], [4 x i32] }

@obj = dso_local global %struct.c zeroinitializer, align 4
@.str = private unnamed_addr constant [10 x i8] c"%p %p %p\0A\00", align 1
@.str.1 = private unnamed_addr constant [11 x i8] c"%d %d %d \0A\00", align 1

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
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
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str, ptr noundef @obj, ptr noundef getelementptr inbounds ([4 x i32], ptr @obj, i64 0, i64 1), ptr noundef getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 2))
  store ptr @obj, ptr %2, align 8
  store i32 0, ptr %3, align 4
  br label %5

5:                                                ; preds = %21, %0
  %6 = load i32, ptr %3, align 4
  %7 = icmp slt i32 %6, 4
  br i1 %7, label %8, label %24

8:                                                ; preds = %5
  %9 = load ptr, ptr %2, align 8
  %10 = getelementptr inbounds i32, ptr %9, i64 0
  %11 = load i32, ptr %10, align 4
  %12 = load ptr, ptr %2, align 8
  %13 = getelementptr inbounds i32, ptr %12, i64 1
  %14 = load i32, ptr %13, align 4
  %15 = load ptr, ptr %2, align 8
  %16 = getelementptr inbounds i32, ptr %15, i64 2
  %17 = load i32, ptr %16, align 4
  %18 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %11, i32 noundef %14, i32 noundef %17)
  %19 = load ptr, ptr %2, align 8
  %20 = getelementptr inbounds i32, ptr %19, i64 3
  store ptr %20, ptr %2, align 8
  br label %21

21:                                               ; preds = %8
  %22 = load i32, ptr %3, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, ptr %3, align 4
  br label %5, !llvm.loop !6

24:                                               ; preds = %5
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
