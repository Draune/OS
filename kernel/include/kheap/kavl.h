#ifndef KERNEL_DRAUNE_STRUCT_AVL
#define KERNEL_DRAUNE_STRUCT_AVL

#include "knoeud.h"

typedef struct{
    kNoeud* debut;
    int (*test_tri)(void*,void*);// doit retourner 1 si le premier doit etre plus à gauche que le 2eme
    kNoeud* tableau_noeud;
    int count;
}kAVL;

kAVL k_creer_avl(int (*test_tri)(void*,void*),kNoeud* tableau_noeud);
kNoeud* k_ajouter_avl(kAVL* avl,kFreeSpace* freespace);
kNoeud* k_trouver_noeud_avl(kAVL* avl,kFreeSpace* freespace);//trouve le noeud le plus a droite qui serait a gauche de freespace
// retourne NULL si aucun ne peu etre a gauche de contenu
kFreeSpace* k_trouver_avl(kAVL* avl,kFreeSpace* freespace);
kFreeSpace* k_retirer_noeud_avl(kAVL* avl,kNoeud* noeud);
kFreeSpace* k_retirer_avl(kAVL* avl,kFreeSpace* freespace);

#endif