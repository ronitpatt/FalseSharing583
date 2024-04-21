; ModuleID = 'profile.cpp'
source_filename = "profile.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { [16 x i32], [16 x i32], [16 x i32] }

@obj = dso_local global %struct.c zeroinitializer, align 4
@.str = private unnamed_addr constant [8 x i8] c"a = %d\0A\00", align 1

; Function Attrs: mustprogress noinline uwtable
define dso_local noundef ptr @_Z5work1Pv(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store ptr %0, ptr %2, align 8
  %5 = load ptr, ptr %2, align 8
  %6 = load i32, ptr %5, align 4
  store i32 %6, ptr %3, align 4
  %7 = load i32, ptr %3, align 4
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %7)
  store i32 0, ptr %4, align 4
  br label %9

9:                                                ; preds = %28, %1
  %10 = load i32, ptr %4, align 4
  %11 = icmp slt i32 %10, 1000000
  br i1 %11, label %12, label %31

12:                                               ; preds = %9
  %13 = load i32, ptr %3, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds [16 x i32], ptr @obj, i64 0, i64 %14
  %16 = load i32, ptr %15, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, ptr %15, align 4
  %18 = load i32, ptr %3, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds [16 x i32], ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 1), i64 0, i64 %19
  %21 = load i32, ptr %20, align 4
  %22 = add nsw i32 %21, 1
  store i32 %22, ptr %20, align 4
  %23 = load i32, ptr %3, align 4
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds [16 x i32], ptr getelementptr inbounds (%struct.c, ptr @obj, i32 0, i32 2), i64 0, i64 %24
  %26 = load i32, ptr %25, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, ptr %25, align 4
  br label %28

28:                                               ; preds = %12
  %29 = load i32, ptr %4, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, ptr %4, align 4
  br label %9, !llvm.loop !6

31:                                               ; preds = %9
  ret ptr null
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #2 {
  %1 = alloca i64, align 8
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 0, ptr %4, align 4
  store i32 1, ptr %5, align 4
  store i32 2, ptr %6, align 4
  %7 = call i32 @pthread_create(ptr noundef %1, ptr noundef null, ptr noundef @_Z5work1Pv, ptr noundef %4) #4
  %8 = call i32 @pthread_create(ptr noundef %2, ptr noundef null, ptr noundef @_Z5work1Pv, ptr noundef %5) #4
  %9 = call i32 @pthread_create(ptr noundef %3, ptr noundef null, ptr noundef @_Z5work1Pv, ptr noundef %6) #4
  %10 = load i64, ptr %1, align 8
  %11 = call i32 @pthread_join(i64 noundef %10, ptr noundef null)
  %12 = load i64, ptr %2, align 8
  %13 = call i32 @pthread_join(i64 noundef %12, ptr noundef null)
  %14 = load i64, ptr %3, align 8
  %15 = call i32 @pthread_join(i64 noundef %14, ptr noundef null)
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @pthread_create(ptr noundef, ptr noundef, ptr noundef, ptr noundef) #3

declare i32 @pthread_join(i64 noundef, ptr noundef) #1

attributes #0 = { mustprogress noinline uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress noinline norecurse uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
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
