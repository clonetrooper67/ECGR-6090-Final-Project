# NOTE: Assertions have been autogenerated by utils/update_mca_test_checks.py
# RUN: llvm-mca -mtriple=x86_64-unknown-unknown -mcpu=x86-64 -iterations=1500 -timeline -timeline-max-iterations=3 < %s | FileCheck %s

# The lzcnt cannot execute in parallel with the imul because there is a false
# dependency on %bx.

imul %ax, %bx
lzcnt %ax, %bx
add %cx, %bx

# CHECK:      Iterations:        1500
# CHECK-NEXT: Instructions:      4500
# CHECK-NEXT: Total Cycles:      3005
# CHECK-NEXT: Total uOps:        4500

# CHECK:      Dispatch Width:    4
# CHECK-NEXT: uOps Per Cycle:    1.50
# CHECK-NEXT: IPC:               1.50
# CHECK-NEXT: Block RThroughput: 2.0

# CHECK:      Instruction Info:
# CHECK-NEXT: [1]: #uOps
# CHECK-NEXT: [2]: Latency
# CHECK-NEXT: [3]: RThroughput
# CHECK-NEXT: [4]: MayLoad
# CHECK-NEXT: [5]: MayStore
# CHECK-NEXT: [6]: HasSideEffects (U)

# CHECK:      [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
# CHECK-NEXT:  1      3     1.00                        imulw	%ax, %bx
# CHECK-NEXT:  1      3     1.00                        lzcntw	%ax, %bx
# CHECK-NEXT:  1      1     0.33                        addw	%cx, %bx

# CHECK:      Resources:
# CHECK-NEXT: [0]   - SBDivider
# CHECK-NEXT: [1]   - SBFPDivider
# CHECK-NEXT: [2]   - SBPort0
# CHECK-NEXT: [3]   - SBPort1
# CHECK-NEXT: [4]   - SBPort4
# CHECK-NEXT: [5]   - SBPort5
# CHECK-NEXT: [6.0] - SBPort23
# CHECK-NEXT: [6.1] - SBPort23

# CHECK:      Resource pressure per iteration:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6.0]  [6.1]
# CHECK-NEXT:  -      -     0.50   2.00    -     0.50    -      -

# CHECK:      Resource pressure by instruction:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6.0]  [6.1]  Instructions:
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     imulw	%ax, %bx
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     lzcntw	%ax, %bx
# CHECK-NEXT:  -      -     0.50    -      -     0.50    -      -     addw	%cx, %bx

# CHECK:      Timeline view:
# CHECK-NEXT:                     01
# CHECK-NEXT: Index     0123456789

# CHECK:      [0,0]     DeeeER    ..   imulw	%ax, %bx
# CHECK-NEXT: [0,1]     D=eeeER   ..   lzcntw	%ax, %bx
# CHECK-NEXT: [0,2]     D====eER  ..   addw	%cx, %bx
# CHECK-NEXT: [1,0]     D=====eeeER.   imulw	%ax, %bx
# CHECK-NEXT: [1,1]     .D=eeeE---R.   lzcntw	%ax, %bx
# CHECK-NEXT: [1,2]     .D====eE--R.   addw	%cx, %bx
# CHECK-NEXT: [2,0]     .D=====eeeER   imulw	%ax, %bx
# CHECK-NEXT: [2,1]     .D==eeeE---R   lzcntw	%ax, %bx
# CHECK-NEXT: [2,2]     . D====eE--R   addw	%cx, %bx

# CHECK:      Average Wait times (based on the timeline view):
# CHECK-NEXT: [0]: Executions
# CHECK-NEXT: [1]: Average time spent waiting in a scheduler's queue
# CHECK-NEXT: [2]: Average time spent waiting in a scheduler's queue while ready
# CHECK-NEXT: [3]: Average time elapsed from WB until retire stage

# CHECK:            [0]    [1]    [2]    [3]
# CHECK-NEXT: 0.     3     4.3    0.3    0.0       imulw	%ax, %bx
# CHECK-NEXT: 1.     3     2.3    2.3    2.0       lzcntw	%ax, %bx
# CHECK-NEXT: 2.     3     5.0    0.0    1.3       addw	%cx, %bx
