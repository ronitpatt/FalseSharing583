; ModuleID = 'sum.cpp'
source_filename = "sum.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@a = dso_local global [17 x i32] zeroinitializer, align 16
@part_size = dso_local global i32 3, align 4
@.str = private unnamed_addr constant [20 x i8] c"Sum of array is %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [20 x i8] c"Expected sum is %d\0A\00", align 1

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef ptr @_Z9sum_arrayPv(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i64, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  %6 = load ptr, ptr %2, align 8
  %7 = ptrtoint ptr %6 to i64
  store i64 %7, ptr %3, align 8
  store i32 0, ptr %4, align 4
  %8 = load i64, ptr %3, align 8
  %9 = icmp eq i64 %8, 4
  br i1 %9, label %10, label %11

10:                                               ; preds = %1
  store i32 2, ptr %4, align 4
  br label %11

11:                                               ; preds = %10, %1
  %12 = load i64, ptr %3, align 8
  %13 = load i32, ptr @part_size, align 4
  %14 = sext i32 %13 to i64
  %15 = mul i64 %12, %14
  %16 = add i64 %15, 1
  %17 = trunc i64 %16 to i32
  store i32 %17, ptr %5, align 4
  br label %18

18:                                               ; preds = %47, %11
  %19 = load i32, ptr %5, align 4
  %20 = sext i32 %19 to i64
  %21 = load i64, ptr %3, align 8
  %22 = add i64 %21, 1
  %23 = load i32, ptr @part_size, align 4
  %24 = sext i32 %23 to i64
  %25 = mul i64 %22, %24
  %26 = load i32, ptr %4, align 4
  %27 = sext i32 %26 to i64
  %28 = add i64 %25, %27
  %29 = icmp ult i64 %20, %28
  br i1 %29, label %30, label %50

30:                                               ; preds = %18
  %31 = load i32, ptr %5, align 4
  %32 = sext i32 %31 to i64
  %33 = icmp ult i64 %32, 17
  br i1 %33, label %34, label %46

34:                                               ; preds = %30
  %35 = load i32, ptr %5, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds [17 x i32], ptr @a, i64 0, i64 %36
  %38 = load i32, ptr %37, align 4
  %39 = load i64, ptr %3, align 8
  %40 = load i32, ptr @part_size, align 4
  %41 = sext i32 %40 to i64
  %42 = mul i64 %39, %41
  %43 = getelementptr inbounds [17 x i32], ptr @a, i64 0, i64 %42
  %44 = load i32, ptr %43, align 4
  %45 = add nsw i32 %44, %38
  store i32 %45, ptr %43, align 4
  br label %46

46:                                               ; preds = %34, %30
  br label %47

47:                                               ; preds = %46
  %48 = load i32, ptr %5, align 4
  %49 = add nsw i32 %48, 1
  store i32 %49, ptr %5, align 4
  br label %18, !llvm.loop !6

50:                                               ; preds = %18
  ret ptr null
}

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #1 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca [5 x i64], align 16
  %4 = alloca i64, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 0, ptr %2, align 4
  br label %8

8:                                                ; preds = %17, %0
  %9 = load i32, ptr %2, align 4
  %10 = icmp slt i32 %9, 17
  br i1 %10, label %11, label %20

11:                                               ; preds = %8
  %12 = load i32, ptr %2, align 4
  %13 = add nsw i32 %12, 1
  %14 = load i32, ptr %2, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [17 x i32], ptr @a, i64 0, i64 %15
  store i32 %13, ptr %16, align 4
  br label %17

17:                                               ; preds = %11
  %18 = load i32, ptr %2, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, ptr %2, align 4
  br label %8, !llvm.loop !8

20:                                               ; preds = %8
  store i64 0, ptr %4, align 8
  br label %21

21:                                               ; preds = %30, %20
  %22 = load i64, ptr %4, align 8
  %23 = icmp ult i64 %22, 5
  br i1 %23, label %24, label %33

24:                                               ; preds = %21
  %25 = load i64, ptr %4, align 8
  %26 = getelementptr inbounds [5 x i64], ptr %3, i64 0, i64 %25
  %27 = load i64, ptr %4, align 8
  %28 = inttoptr i64 %27 to ptr
  %29 = call i32 @pthread_create(ptr noundef %26, ptr noundef null, ptr noundef @_Z9sum_arrayPv, ptr noundef %28) #4
  br label %30

30:                                               ; preds = %24
  %31 = load i64, ptr %4, align 8
  %32 = add i64 %31, 1
  store i64 %32, ptr %4, align 8
  br label %21, !llvm.loop !9

33:                                               ; preds = %21
  store i32 0, ptr %5, align 4
  br label %34

34:                                               ; preds = %43, %33
  %35 = load i32, ptr %5, align 4
  %36 = icmp slt i32 %35, 5
  br i1 %36, label %37, label %46

37:                                               ; preds = %34
  %38 = load i32, ptr %5, align 4
  %39 = sext i32 %38 to i64
  %40 = getelementptr inbounds [5 x i64], ptr %3, i64 0, i64 %39
  %41 = load i64, ptr %40, align 8
  %42 = call i32 @pthread_join(i64 noundef %41, ptr noundef null)
  br label %43

43:                                               ; preds = %37
  %44 = load i32, ptr %5, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, ptr %5, align 4
  br label %34, !llvm.loop !10

46:                                               ; preds = %34
  store i32 0, ptr %6, align 4
  store i32 0, ptr %7, align 4
  br label %47

47:                                               ; preds = %59, %46
  %48 = load i32, ptr %7, align 4
  %49 = icmp slt i32 %48, 5
  br i1 %49, label %50, label %62

50:                                               ; preds = %47
  %51 = load i32, ptr %7, align 4
  %52 = load i32, ptr @part_size, align 4
  %53 = mul nsw i32 %51, %52
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds [17 x i32], ptr @a, i64 0, i64 %54
  %56 = load i32, ptr %55, align 4
  %57 = load i32, ptr %6, align 4
  %58 = add nsw i32 %57, %56
  store i32 %58, ptr %6, align 4
  br label %59

59:                                               ; preds = %50
  %60 = load i32, ptr %7, align 4
  %61 = add nsw i32 %60, 1
  store i32 %61, ptr %7, align 4
  br label %47, !llvm.loop !11

62:                                               ; preds = %47
  %63 = load i32, ptr %6, align 4
  %64 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %63)
  %65 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef 153)
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @pthread_create(ptr noundef, ptr noundef, ptr noundef, ptr noundef) #2

declare i32 @pthread_join(i64 noundef, ptr noundef) #3

declare i32 @printf(ptr noundef, ...) #3

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind }

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
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
