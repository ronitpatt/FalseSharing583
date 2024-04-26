; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { i32, i32 }

@elements_per_thread = dso_local global i32 1000000, align 4
@.str = private unnamed_addr constant [4 x i8] c"%p\0A\00", align 1
@.str.1 = private unnamed_addr constant [11 x i8] c"front: %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c"back: %d\0A\00", align 1

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef ptr @_Z4workPv(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  store i32 0, ptr %3, align 4
  br label %5

5:                                                ; preds = %15, %1
  %6 = load i32, ptr %3, align 4
  %7 = load i32, ptr @elements_per_thread, align 4
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %18

9:                                                ; preds = %5
  %10 = load ptr, ptr %2, align 8
  store ptr %10, ptr %4, align 8
  %11 = load ptr, ptr %4, align 8
  %12 = getelementptr inbounds %struct.c, ptr %11, i32 0, i32 0
  %13 = load i32, ptr %12, align 4
  %14 = add nsw i32 %13, 1
  store i32 %14, ptr %12, align 4
  br label %15

15:                                               ; preds = %9
  %16 = load i32, ptr %3, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, ptr %3, align 4
  br label %5, !llvm.loop !6

18:                                               ; preds = %5
  ret ptr null
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef ptr @_Z5work2Pv(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  store i32 0, ptr %3, align 4
  br label %5

5:                                                ; preds = %15, %1
  %6 = load i32, ptr %3, align 4
  %7 = load i32, ptr @elements_per_thread, align 4
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %9, label %18

9:                                                ; preds = %5
  %10 = load ptr, ptr %2, align 8
  store ptr %10, ptr %4, align 8
  %11 = load ptr, ptr %4, align 8
  %12 = getelementptr inbounds %struct.c, ptr %11, i32 0, i32 1
  %13 = load i32, ptr %12, align 4
  %14 = add nsw i32 %13, 1
  store i32 %14, ptr %12, align 4
  br label %15

15:                                               ; preds = %9
  %16 = load i32, ptr %3, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, ptr %3, align 4
  br label %5, !llvm.loop !8

18:                                               ; preds = %5
  ret ptr null
}

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #1 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.c, align 4
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  store i32 0, ptr %1, align 4
  %5 = getelementptr inbounds %struct.c, ptr %2, i32 0, i32 0
  store i32 0, ptr %5, align 4
  %6 = getelementptr inbounds %struct.c, ptr %2, i32 0, i32 1
  store i32 0, ptr %6, align 4
  %7 = getelementptr inbounds %struct.c, ptr %2, i32 0, i32 0
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str, ptr noundef %7)
  %9 = getelementptr inbounds %struct.c, ptr %2, i32 0, i32 1
  %10 = call i32 (ptr, ...) @printf(ptr noundef @.str, ptr noundef %9)
  %11 = call i32 @pthread_create(ptr noundef %3, ptr noundef null, ptr noundef @_Z4workPv, ptr noundef %2) #4
  %12 = call i32 @pthread_create(ptr noundef %4, ptr noundef null, ptr noundef @_Z5work2Pv, ptr noundef %2) #4
  %13 = load i64, ptr %3, align 8
  %14 = call i32 @pthread_join(i64 noundef %13, ptr noundef null)
  %15 = load i64, ptr %4, align 8
  %16 = call i32 @pthread_join(i64 noundef %15, ptr noundef null)
  %17 = getelementptr inbounds %struct.c, ptr %2, i32 0, i32 0
  %18 = load i32, ptr %17, align 4
  %19 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %18)
  %20 = getelementptr inbounds %struct.c, ptr %2, i32 0, i32 1
  %21 = load i32, ptr %20, align 4
  %22 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %21)
  ret i32 0
}

declare i32 @printf(ptr noundef, ...) #2

; Function Attrs: nounwind
declare i32 @pthread_create(ptr noundef, ptr noundef, ptr noundef, ptr noundef) #3

declare i32 @pthread_join(i64 noundef, ptr noundef) #2

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
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
