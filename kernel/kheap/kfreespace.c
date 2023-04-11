#include <kheap/kfreespace.h>
#include <kheap/knoeud.h>
#include <stddef.h>

kFreeSpace* k_creer_freespace(KERNEL_INT adresse,KERNEL_INT taille,kFreeSpace* tableau_freespace,int* count){
    kFreeSpace* return_ = &(tableau_freespace[*count]);
    return_->adresse = adresse;
    return_->taille = taille;
    return_->noeud_adresse = NULL;
    return_->noeud_taille = NULL;

    (*count)++;

    return return_;
}

void k_supprimer_freespace(kFreeSpace* freespace,kFreeSpace* tableau_freespace,int* count){
    kFreeSpace* remplacement = &(tableau_freespace[*count - 1]);
    freespace->adresse = remplacement->adresse;
    freespace->taille = remplacement->taille;
    freespace->noeud_adresse = remplacement->noeud_adresse;
    ((kNoeud*)remplacement->noeud_adresse)->freespace = freespace;
    freespace->noeud_taille = remplacement->noeud_taille;
    ((kNoeud*)remplacement->noeud_taille)->freespace = freespace;

    (*count)--;
}

int test_tri_freespace_adresse(void* freespace1,void* freespace2){
    return (((kFreeSpace*)freespace1)->adresse <= ((kFreeSpace*)freespace2)->adresse)?1:0;
}

int test_tri_freespace_taille(void* freespace1,void* freespace2){
    return (((kFreeSpace*)freespace1)->taille >= ((kFreeSpace*)freespace2)->taille)?1:0;
}