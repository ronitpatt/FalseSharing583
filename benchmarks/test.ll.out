; ModuleID = 'test.bc'
source_filename = "profileGT.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { [16 x i32], [16 x i32], [16 x i32] }
%struct.cGT = type { i32, i32, i32 }

@obj = dso_local global %struct.c zeroinitializer, align 4
@.str = private unnamed_addr constant [8 x i8] c"a = %d\0A\00", align 1
@transposed = internal global [16 x %struct.cGT] zeroinitializer, align 16

; Function Attrs: mustprogress noinline uwtable
define dso_local noundef ptr @_Z5work1Pv(ptr noundef %arg) #0 {
entry:
  %arg.addr = alloca ptr, align 8
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  store ptr %arg, ptr %arg.addr, align 8
  %0 = load ptr, ptr %arg.addr, align 8
  %1 = load i32, ptr %0, align 4
  store i32 %1, ptr %a, align 4
  %2 = load i32, ptr %a, align 4
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %2)
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load i32, ptr %i, align 4
  %cmp = icmp slt i32 %3, 1000000
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %4 = load i32, ptr %a, align 4
  %idxprom = sext i32 %4 to i64
  %arrayidx = getelementptr inbounds [16 x i32], ptr @transposed, i64 0, i64 %idxprom
  %5 = load i32, ptr %arrayidx, align 4
  %inc = add nsw i32 %5, 1
  store i32 %inc, ptr %arrayidx, align 4
  %6 = load i32, ptr %a, align 4
  %idxprom1 = sext i32 %6 to i64
  %hi = getelementptr inbounds %struct.cGT, ptr @transposed, i32 0, i32 1
  %7 = getelementptr inbounds [16 x i32], ptr %hi, i64 0, i64 %idxprom1
  %8 = load i32, ptr %7, align 4
  %inc3 = add nsw i32 %8, 1
  store i32 %inc3, ptr %7, align 4
  %9 = load i32, ptr %a, align 4
  %idxprom4 = sext i32 %9 to i64
  %hi1 = getelementptr inbounds %struct.cGT, ptr @transposed, i32 0, i32 2
  %10 = getelementptr inbounds [16 x i32], ptr %hi1, i64 0, i64 %idxprom4
  %11 = load i32, ptr %10, align 4
  %inc6 = add nsw i32 %11, 1
  store i32 %inc6, ptr %10, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %12 = load i32, ptr %i, align 4
  %inc7 = add nsw i32 %12, 1
  store i32 %inc7, ptr %i, align 4
  br label %for.cond, !llvm.loop !6

for.end:                                          ; preds = %for.cond
  ret ptr null
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #2 {
entry:
  %ptid1 = alloca i64, align 8
  %ptid2 = alloca i64, align 8
  %ptid3 = alloca i64, align 8
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 0, ptr %a, align 4
  store i32 1, ptr %b, align 4
  store i32 2, ptr %c, align 4
  %call = call i32 @pthread_create(ptr noundef %ptid1, ptr noundef null, ptr noundef @_Z5work1Pv, ptr noundef %a) #4
  %call1 = call i32 @pthread_create(ptr noundef %ptid2, ptr noundef null, ptr noundef @_Z5work1Pv, ptr noundef %b) #4
  %call2 = call i32 @pthread_create(ptr noundef %ptid3, ptr noundef null, ptr noundef @_Z5work1Pv, ptr noundef %c) #4
  %0 = load i64, ptr %ptid1, align 8
  %call3 = call i32 @pthread_join(i64 noundef %0, ptr noundef null)
  %1 = load i64, ptr %ptid2, align 8
  %call4 = call i32 @pthread_join(i64 noundef %1, ptr noundef null)
  %2 = load i64, ptr %ptid3, align 8
  %call5 = call i32 @pthread_join(i64 noundef %2, ptr noundef null)
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
