; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { [4 x i32], [4 x i32], [4 x i32] }

@obj = dso_local global %struct.c zeroinitializer, align 4

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 0, ptr %2, align 4
  br label %3

3:                                                ; preds = %10, %0
  %4 = load i32, ptr %2, align 4
  %5 = icmp slt i32 %4, 4
  br i1 %5, label %6, label %13

6:                                                ; preds = %3
  %7 = load i32, ptr %2, align 4
  %8 = sext i32 %7 to i64
  %9 = getelementptr inbounds [4 x i32], ptr @obj, i64 0, i64 %8
  store i32 1, ptr %9, align 4
  br label %10

10:                                               ; preds = %6
  %11 = load i32, ptr %2, align 4
  %12 = add nsw i32 %11, 1
  store i32 %12, ptr %2, align 4
  br label %3, !llvm.loop !6

13:                                               ; preds = %3
  ret i32 1
}

attributes #0 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

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
