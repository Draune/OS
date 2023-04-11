#include<libk/stdlib.h>
#include<kheap/kheap.h>
#include<libk/string.h>

void* realloc(void* pointer, size_t memory_size){
    if(pointer == NULL)
        return malloc(memory_size);
    size_t original_size = (size_t)(*(KERNEL_INT*)(pointer-sizeof(KERNEL_INT)));
    free(pointer);
    void* return_ = malloc(memory_size);
    if(return_ != pointer)
        memcpy(return_,pointer,(original_size<memory_size)?original_size:memory_size);
    return return_;
}