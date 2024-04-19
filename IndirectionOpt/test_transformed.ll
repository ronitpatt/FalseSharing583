; ModuleID = 'test.ll'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@stdout = external global ptr, align 8
@.str = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@word.odd = global [5 x i8] c"elwrd"
@word.even = global [6 x i8] c"hlool\00"
@word.ptr = global [11 x ptr] [ptr @word.even, ptr @word.odd, ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 1), ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 1), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 2), ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 2), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 3), ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 3), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 4), ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 4), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 5)]

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 0, ptr %2, align 4
  br label %3

3:                                                ; preds = %16, %0
  %4 = load i32, ptr %2, align 4
  %5 = sext i32 %4 to i64
  %6 = icmp ult i64 %5, 11
  br i1 %6, label %7, label %19

7:                                                ; preds = %3
  %8 = load ptr, ptr @stdout, align 8
  %9 = load i32, ptr %2, align 4
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds [11 x ptr], ptr @word.ptr, i64 0, i64 %10
  %12 = load ptr, ptr %11, align 8
  %13 = load i8, ptr %12, align 1
  %14 = sext i8 %13 to i32
  %15 = call i32 (ptr, ptr, ...) @fprintf(ptr noundef %8, ptr noundef @.str, i32 noundef %14)
  br label %16

16:                                               ; preds = %7
  %17 = load i32, ptr %2, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, ptr %2, align 4
  br label %3, !llvm.loop !6

19:                                               ; preds = %3
  %20 = load ptr, ptr @stdout, align 8
  %21 = call i32 (ptr, ptr, ...) @fprintf(ptr noundef %20, ptr noundef @.str, i32 noundef 10)
  ret i32 1
}

declare i32 @fprintf(ptr noundef, ptr noundef, ...) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
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
