#include <multiboot.h>
#include <libk/stdio.h>

void test_multiboot(uint32_t magic,multiboot_info_t* info){
    printf("multiboot : magic = %x\n",magic);
    printf("multiboot : flags = %x\n",info->flags);
    if(info->flags & MULTIBOOT_INFO_MEMORY)
        printf("multiboot : mem_lower = %d & mem_upper = %d\n",info->mem_lower,info->mem_upper);

}
