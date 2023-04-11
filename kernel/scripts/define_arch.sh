num_arch=0
if test "i686" = "$1"
then
    num_arch=1
fi

echo "#ifndef KERNEL_ARCH_H\n#define KERNEL_ARCH_H\n#define KERNEL_ARCH "$num_arch"\n#endif" > ./include/arch.h 
# juste ./ car appelé depuis /kernel/Makefile