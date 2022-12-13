#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

// Base : 32 bits

// limit : 20 bits

// flags : 4 bits : 
    //3 - G : granularity flag : 0 = limit in 1 byte block ; 1 = limit in 4KiB block
    //2 - DB : size flag : 0 = 16 bits protected mode ; 1 = 32 bits protected mode
    //1 - L : long mode flag : for 64-bit code segment
    //0 - reserved

// acces_byte : 8 bits  : 
    //7 - P : Present bit : 1 for a valid segment
    //6 & 5 - DPL : Descriptor privilege level field : 0 = highest and 3 = lowest
    //4 - S : Descriptor type bit : 0 = define a system segment ; 1 =  define a code or data segment
    //3 - E : Executable bit : 0 = Data segment ; 1 = Code segment
    //2 - DC : Direction bit/Conforming bit : 
        //for data selectors : 0 = segment growns up ; 1 = grows down
        //for code selectors : 
            // - 0 = code in this segment can only be executed from the ring set in DPL
            // - 1 = code in this segment can be executed from an equal or lower privilege level.
            // For example, code in ring 3 can far-jump to conforming code in a ring 2 segment.
            // The DPL field represent the highest privilege level that is allowed to execute the segment
    //1 - RW : Readable/Writable bit 
        //for code segment : Write never allowed ;  0 = read not allowed ; 1 = allowed
        //for code segment : Read always allowed ;  0 = write not allowed ; 1 = allowed
    //0 - A : Accessed bit : best 0, CPU handle it ;p


//  Base   |  flags  |  limit  |  acces_byte  |  Base  |  limit      
// 31 - 24    3 - 0    19 - 16       7 - 0      23 - 0    15 - 0
// 63 - 56   55 - 52   51 - 48      47 - 40     39 - 16   15 - 0
//    8         4         4            8           24        16

void kinit_gdt(void);

#endif // _KERNEL_GDT_H