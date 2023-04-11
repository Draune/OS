#include<libk/stdlib.h>
#include<kheap/kheap.h>

void free(void* pointer){
    if(pointer != NULL){
        pointer -= sizeof(KERNEL_INT);
        size_t memory_size = (size_t)(*(KERNEL_INT*)pointer) + sizeof(KERNEL_INT);
        k_free(pointer,memory_size);
    }
}