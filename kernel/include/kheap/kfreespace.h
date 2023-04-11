#ifndef KERNEL_FREESPACE
#define KERNEL_FREESPACE

#include <stdint.h>
#include <arch_const.h>

typedef struct kFreeSpace{
    KERNEL_INT adresse,taille;
    void* noeud_adresse;
    void* noeud_taille;
}kFreeSpace;

kFreeSpace* k_creer_freespace(KERNEL_INT adresse,KERNEL_INT taille,kFreeSpace* tableau_freespace,int* count);
void k_supprimer_freespace(kFreeSpace* freespace,kFreeSpace* tableau_freespace,int* count);
int test_tri_freespace_adresse(void* freespace1,void* freespace2);
int test_tri_freespace_taille(void* freespace1,void* freespace2);

#endif