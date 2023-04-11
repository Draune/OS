#include<libk/stdlib.h>
#include<kheap/kheap.h>

void* malloc(size_t memory_size){
    memory_size += sizeof(KERNEL_INT);
    void* return_ = k_malloc(memory_size);
    if(return_ != NULL){
        *((KERNEL_INT*)return_) = (KERNEL_INT)memory_size;
        return_ = &(((KERNEL_INT*)return_)[1]);
    }  
    return return_;
}