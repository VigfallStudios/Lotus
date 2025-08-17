    .section .text
    .global panic_asm
    .type panic_asm, %function

// panic_asm(const char *msg)
// Saves x0-x30 + original SP into a contiguous buffer on the stack
// then calls dump_regs(uint64_t *regs, const char *msg)
panic_asm:
    // allocate space: 34 * 8 = 272 bytes
    sub     sp, sp, #272

    // store x0..x30 (pairwise). Note: first stored word holds original x0 (msg)
    stp     x0,  x1,  [sp, #0]
    stp     x2,  x3,  [sp, #16]
    stp     x4,  x5,  [sp, #32]
    stp     x6,  x7,  [sp, #48]
    stp     x8,  x9,  [sp, #64]
    stp     x10, x11, [sp, #80]
    stp     x12, x13, [sp, #96]
    stp     x14, x15, [sp, #112]
    stp     x16, x17, [sp, #128]
    stp     x18, x19, [sp, #144]
    stp     x20, x21, [sp, #160]
    stp     x22, x23, [sp, #176]
    stp     x24, x25, [sp, #192]
    stp     x26, x27, [sp, #208]
    stp     x28, x29, [sp, #224]
    stp     x30, xzr, [sp, #240]    // store x30, then zero word

    // store the original SP (before the sub). old_sp = sp + 272
    add     x1, sp, #272
    str     x1, [sp, #248]

    // now call dump_regs(sp, msg)
    mov     x0, sp            // pointer to saved regs
    ldr     x1, [sp, #0]      // original x0 (msg) was saved at sp+0
    bl      dump_regs

// infinite loop so we don't return to random state
1:
    b 1b
