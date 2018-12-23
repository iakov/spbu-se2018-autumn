.global sort

sort:
    push %r8
    push %r9
    push %r10
    push %r11
    mov $0, %r8
.l8c:
    cmp %rdx, %r8
    jge .l8e
    mov %r8, %r9
    add $1, %r9
.l9c:
    cmp %rdx, %r9
    jge .l9e
    mov (%rcx, %r8, 8), %r10
    mov (%rcx, %r9, 8), %r11
    cmp %r10, %r11
    jge .ijse
    mov %r10, (%rcx, %r9, 8)
    mov %r11, (%rcx, %r8, 8)
.ijse:
    add $1, %r9
    jmp .l9c
.l9e:
    add $1, %r8
    jmp .l8c
.l8e:
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    ret
