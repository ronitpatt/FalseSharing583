; ModuleID = 'test.cpp'
source_filename = "test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { i32, i32 }

@.str = private unnamed_addr constant [7 x i8] c"%s %p\0A\00", align 1
@elements_per_thread = dso_local global i32 1000000, align 4

; Function Attrs: mustprogress noinline uwtable
define dso_local void @_Z7doPrintPcPv(ptr noundef %name, ptr noundef %thing) #0 {
entry:
  %name.addr = alloca ptr, align 8
  %thing.addr = alloca ptr, align 8
  store ptr %name, ptr %name.addr, align 8
  store ptr %thing, ptr %thing.addr, align 8
  %0 = load ptr, ptr %name.addr, align 8
  %1 = load ptr, ptr %thing.addr, align 8
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, ptr noundef %0, ptr noundef %1)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef ptr @_Z4workPv(ptr noundef %obj) #2 {
entry:
  %obj.addr = alloca ptr, align 8
  %i = alloca i32, align 4
  %ptr = alloca ptr, align 8
  store ptr %obj, ptr %obj.addr, align 8
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr @elements_per_thread, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load ptr, ptr %obj.addr, align 8
  store ptr %2, ptr %ptr, align 8
  %3 = load ptr, ptr %ptr, align 8
  %front = getelementptr inbounds %struct.c, ptr %3, i32 0, i32 0
  %4 = load i32, ptr %front, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, ptr %front, align 4
  %call = call i32 @sched_yield() #5
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %5 = load i32, ptr %i, align 4
  %inc1 = add nsw i32 %5, 1
  store i32 %inc1, ptr %i, align 4
  br label %for.cond, !llvm.loop !6

for.end:                                          ; preds = %for.cond
  ret ptr null
}

; Function Attrs: nounwind
declare i32 @sched_yield() #3

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef ptr @_Z5work2Pv(ptr noundef %obj) #2 {
entry:
  %obj.addr = alloca ptr, align 8
  %i = alloca i32, align 4
  %ptr = alloca ptr, align 8
  store ptr %obj, ptr %obj.addr, align 8
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, ptr %i, align 4
  %1 = load i32, ptr @elements_per_thread, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load ptr, ptr %obj.addr, align 8
  store ptr %2, ptr %ptr, align 8
  %3 = load ptr, ptr %ptr, align 8
  %back = getelementptr inbounds %struct.c, ptr %3, i32 0, i32 1
  %4 = load i32, ptr %back, align 4
  %inc = add nsw i32 %4, 1
  store i32 %inc, ptr %back, align 4
  %call = call i32 @sched_yield() #5
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %5 = load i32, ptr %i, align 4
  %inc1 = add nsw i32 %5, 1
  store i32 %inc1, ptr %i, align 4
  br label %for.cond, !llvm.loop !8

for.end:                                          ; preds = %for.cond
  ret ptr null
}

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #4 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %base = alloca i32, align 4
  %baaase = alloca i32, align 4
  %obj = alloca %struct.c, align 4
  %ptid1 = alloca i64, align 8
  %ptid2 = alloca i64, align 8
  store i32 0, ptr %retval, align 4
  %front = getelementptr inbounds %struct.c, ptr %obj, i32 0, i32 0
  store i32 0, ptr %front, align 4
  %back = getelementptr inbounds %struct.c, ptr %obj, i32 0, i32 1
  store i32 0, ptr %back, align 4
  %call = call i32 @pthread_create(ptr noundef %ptid1, ptr noundef null, ptr noundef @_Z4workPv, ptr noundef %obj) #5
  %call1 = call i32 @pthread_create(ptr noundef %ptid2, ptr noundef null, ptr noundef @_Z5work2Pv, ptr noundef %obj) #5
  %0 = load i64, ptr %ptid1, align 8
  %call2 = call i32 @pthread_join(i64 noundef %0, ptr noundef null)
  %1 = load i64, ptr %ptid2, align 8
  %call3 = call i32 @pthread_join(i64 noundef %1, ptr noundef null)
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @pthread_create(ptr noundef, ptr noundef, ptr noundef, ptr noundef) #3

declare i32 @pthread_join(i64 noundef, ptr noundef) #1

attributes #0 = { mustprogress noinline uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress noinline norecurse uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind }

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
