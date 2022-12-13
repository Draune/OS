.section .data
gdt_start:
    gdt_null:
        .quad 0x0
    gdt_kernel_code:
        .quad 0x00CF9A000000FFFF
    gdt_kernel_data:
        .quad 0x00CF92000000FFFF
gdt_end:

gdtr: 
    .word gdt_end - gdt_start
    .long gdt_start

.section .text
.global kinit_gdt
kinit_gdt:
    lgdt gdtr

    // Reload data segment registers:
    movl   $0x10, %eax  // 0x10 is a stand-in for the data segment
    movl   %eax, %ds
    movl   %eax, %es
    movl   %eax, %fs
    movl   %eax, %gs
    movl   %eax, %ss

    // Reload CS register containing code selector:
    ljmp   $0x08,$kinit_gdt_return // 0x08 is a stand-in for the code segment

kinit_gdt_return:
    ret
    
    
    