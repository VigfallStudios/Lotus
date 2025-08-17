.global _start
_start:
    // Set up stack
    ldr x30, =stack_top
    mov sp, x30

    // Call kmain(x0) where x0 contains FDT pointer
    mov x0, x0       // already contains FDT from QEMU
    bl kmain

    b .
