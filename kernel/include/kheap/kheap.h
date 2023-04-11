#ifndef KERNEL_HEAP
#define KERNEL_HEAP

#include <stddef.h>
#include "kavl.h"

#define NB_MAX_FREESPACES 1048576
#define TAILLE_RAM 1073741824 //1 GB

typedef struct kHeap{
    kAVL avl_adresse;
    kAVL avl_taille;
    kNoeud tableau_noeud_adresse[NB_MAX_FREESPACES];
    kNoeud tableau_noeud_taille[NB_MAX_FREESPACES];
    kFreeSpace tableau_freespace[NB_MAX_FREESPACES];
    int nb_freespaces;
    uint64_t ram[TAILLE_RAM/8];
}kHeap;

void k_init_heap();
void* k_malloc(size_t Memory_size);
void k_free(void * pointer,size_t Memory_size);

#endif