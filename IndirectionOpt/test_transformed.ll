; ModuleID = 'test.ll'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@stdout = external global ptr, align 8
@.str = private unnamed_addr constant [4 x i8] c"%c \00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@word.odd = global [5 x i8] c"ELWRD"
@word.even = global [6 x i8] c"HLOOL\00"
@word.ptr = global [11 x ptr] [ptr @word.even, ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 1), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 2), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 3), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 4), ptr getelementptr inbounds ([6 x i8], ptr @word.even, i32 0, i32 5), ptr @word.odd, ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 1), ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 2), ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 3), ptr getelementptr inbounds ([5 x i8], ptr @word.odd, i32 0, i32 4)]

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca ptr, align 8
  %3 = alloca ptr, align 8
  %4 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  %5 = call noalias ptr @malloc(i64 noundef 11) #3
  store ptr %5, ptr %2, align 8
  %6 = call noalias ptr @malloc(i64 noundef 11) #3
  store ptr %6, ptr %3, align 8
  store i32 0, ptr %4, align 4
  br label %7

7:                                                ; preds = %18, %0
  %8 = load i32, ptr %4, align 4
  %9 = icmp slt i32 %8, 15
  br i1 %9, label %10, label %21

10:                                               ; preds = %7
  %11 = load ptr, ptr @stdout, align 8
  %12 = load i32, ptr %4, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds [11 x i8], ptr @word.ptr, i64 0, i64 %13
  %15 = load i8, ptr %14, align 1
  %16 = sext i8 %15 to i32
  %17 = call i32 (ptr, ptr, ...) @fprintf(ptr noundef %11, ptr noundef @.str, i32 noundef %16)
  br label %18

18:                                               ; preds = %10
  %19 = load i32, ptr %4, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, ptr %4, align 4
  br label %7, !llvm.loop !6

21:                                               ; preds = %7
  %22 = load ptr, ptr @stdout, align 8
  %23 = call i32 (ptr, ptr, ...) @fprintf(ptr noundef %22, ptr noundef @.str.1, i32 noundef 10)
  ret i32 1
}

; Function Attrs: nounwind allocsize(0)
declare noalias ptr @malloc(i64 noundef) #1

declare i32 @fprintf(ptr noundef, ptr noundef, ...) #2

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind allocsize(0) }

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
