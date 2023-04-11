#ifndef KERNEL_ARCH_CONST_H
#define KERNEL_ARCH_CONST_H

#include<arch.h>
#include<stdint.h>

#define ARCH_I686 1

#if ARCH_I686 == KERNEL_ARCH
#define KERNEL_INT  uint32_t
#endif

#endif