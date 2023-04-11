#ifndef KERNEL_DRAUNE_STRUCT_NOEUD
#define KERNEL_DRAUNE_STRUCT_NOEUD

#include "kfreespace.h"

typedef struct kNoeud{
    kFreeSpace* freespace;
    int count;
    struct kNoeud* gauche;
    struct kNoeud* droite;
    struct kNoeud* precedent;
}kNoeud;

kNoeud* k_creer_kNoeud(kFreeSpace* freespace,kNoeud* tableau_noeud,int count);

kFreeSpace* k_supprimer_kNoeud(kNoeud* noeud,void* avl,kNoeud* tableau_noeud,int count);

#endif