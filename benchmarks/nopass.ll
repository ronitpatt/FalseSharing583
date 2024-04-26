; ModuleID = 'temp.cpp'
source_filename = "temp.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.c = type { i32, i32, i16 }

@.str = private unnamed_addr constant [7 x i8] c"%s %p\0A\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"ptr: %p\0A\00", align 1

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

; Function Attrs: mustprogress noinline norecurse uwtable
define dso_local noundef i32 @main() #2 {
entry:
  %obj = alloca %struct.c, align 4
  %a = getelementptr inbounds %struct.c, ptr %obj, i32 0, i32 0
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str.1, ptr noundef %a)
  %b = getelementptr inbounds %struct.c, ptr %obj, i32 0, i32 1
  %call1 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, ptr noundef %b)
  %c = getelementptr inbounds %struct.c, ptr %obj, i32 0, i32 2
  %call2 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, ptr noundef %c)
  ret i32 0
}

attributes #0 = { mustprogress noinline uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress noinline norecurse uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.6"}
