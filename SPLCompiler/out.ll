; ModuleID = 'what'
source_filename = "what"

@a = internal global i32 0

define i32 @main() {
entry:
  store i32 1, i32* @a, align 4
  store i32 1, i32* @a, align 4
  br label %repeat

repeat:                                           ; preds = %repeat, %entry
  %a7 = phi i32 [ %add, %repeat ], [ 1, %entry ]
  %add = add i32 %a7, 1
  store i32 %add, i32* @a, align 4
  %icmpeq9.not = icmp eq i32 %add, 5
  br i1 %icmpeq9.not, label %whilecond, label %repeat

whilecond:                                        ; preds = %repeat, %while
  %a12 = phi i32 [ %sub, %while ], [ 5, %repeat ]
  %icmpsgt = icmp sgt i32 %a12, 1
  br i1 %icmpsgt, label %while, label %for

while:                                            ; preds = %whilecond
  %sub = add i32 %a12, -1
  store i32 %sub, i32* @a, align 4
  br label %whilecond

for:                                              ; preds = %whilecond
  %add14 = add i32 %a12, 1
  store i32 %add14, i32* @a, align 4
  switch i32 %add14, label %default [
    i32 1, label %case
    i32 2, label %case17
    i32 3, label %case18
  ]

case:                                             ; preds = %for
  store i32 2, i32* @a, align 4
  br label %endcase

case17:                                           ; preds = %for
  store i32 3, i32* @a, align 4
  br label %endcase

case18:                                           ; preds = %for
  store i32 4, i32* @a, align 4
  br label %endcase

default:                                          ; preds = %for
  store i32 5, i32* @a, align 4
  br label %endcase

endcase:                                          ; preds = %default, %case18, %case17, %case
  ret i32 0
}
