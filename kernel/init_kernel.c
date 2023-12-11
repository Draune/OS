#include <tty.h>
#include <gdt.h>
#include <libk/stdio.h>
#include <kheap/kheap.h>
#include <multiboot.h>

void init_kernel(uint32_t magic, uint32_t multiboot_info_ptr){
    terminal_initialize();
    printf("init : terminal\n");

    test_multiboot(magic,multiboot_info_ptr);

    kinit_gdt();
    printf("init : gdt\n");

    k_init_heap();
    printf("init : heap\n");
}