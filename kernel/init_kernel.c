#include <tty.h>
#include <gdt.h>
#include <libk/stdio.h>
#include <kheap/kheap.h>


void init_kernel(void){
    terminal_initialize();
    printf("init : terminal\n");

    kinit_gdt();
    printf("init : gdt\n");

    k_init_heap();
    printf("init : heap\n");
}