/* multiboot header definitions */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set GRAPHIQUE_FIELDS, 1<<2		/* to specify the prefered graphics mode */
.set FLAGS,    ALIGN | MEMINFO //| GRAPHIQUE_FIELDS
.set MAGIC,    0x1BADB002       
.set CHECKSUM, -(MAGIC + FLAGS)
 
/* multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
header_addr:
.long 0
load_addr:
.long 0
load_end_addr:
.long 0
bss_end_addr:
.long 0
entry_addr:
.long 0
mode_type:
.long 0	
width:
.long 0 
height:
.long 0 
depth:
.long 0 
 
/* stack */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
 
 /* start */
.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp

	push %ebx
	push %eax

	call init_kernel

	call kernel_main
 
	cli
1:	hlt
	jmp 1b
 
/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start
