#include <kheap/kheap.h>

kHeap heap;

void k_init_heap(){
    heap.nb_freespaces = 0;

    heap.avl_adresse = k_creer_avl(test_tri_freespace_adresse,heap.tableau_noeud_adresse);
    heap.avl_taille = k_creer_avl(test_tri_freespace_taille,heap.tableau_noeud_taille);
    kFreeSpace* init = k_creer_freespace((KERNEL_INT)(heap.ram),TAILLE_RAM,heap.tableau_freespace,&(heap.nb_freespaces));
    init->noeud_adresse = k_ajouter_avl(&(heap.avl_adresse),init);
    init->noeud_taille = k_ajouter_avl(&(heap.avl_taille),init);
}

void* k_malloc(size_t Memory_size){
    void* return_;
    kFreeSpace recherche;
    recherche.taille = (KERNEL_INT)Memory_size;

    kFreeSpace* space = k_retirer_avl(&(heap.avl_taille),&recherche);

    if(space == NULL)
        return_ = NULL;
    else if(space->taille == recherche.taille){
        k_retirer_noeud_avl(&(heap.avl_adresse),space->noeud_adresse);
        return_ = (void*)space->adresse;
        k_supprimer_freespace(space,heap.tableau_freespace,&(heap.nb_freespaces));
    }
    else{
        space->taille -= recherche.taille;
        return_ = (void*)(space->adresse + space->taille);
        space->noeud_taille = k_ajouter_avl(&(heap.avl_taille),space);
    }

    return return_;
}

void k_free(void * pointer,size_t Memory_size){
    if(pointer != NULL){
        kFreeSpace recherche;
        recherche.adresse = (KERNEL_INT)pointer + (KERNEL_INT)Memory_size;
        kFreeSpace* trouver = k_trouver_avl(&(heap.avl_adresse),&recherche);

        if(trouver == NULL || (trouver->adresse + trouver->taille) < (KERNEL_INT)pointer){
            kFreeSpace* nouveau = k_creer_freespace((KERNEL_INT)pointer,(KERNEL_INT)Memory_size,heap.tableau_freespace,&(heap.nb_freespaces));
            nouveau->noeud_adresse = k_ajouter_avl(&(heap.avl_adresse),nouveau);
            nouveau->noeud_taille = k_ajouter_avl(&(heap.avl_taille),nouveau);
        }
        else if(trouver->adresse == recherche.adresse){
            k_retirer_noeud_avl(&(heap.avl_adresse),trouver->noeud_adresse);
            k_retirer_noeud_avl(&(heap.avl_taille),trouver->noeud_taille);
            kFreeSpace* retrouver = k_trouver_avl(&(heap.avl_adresse),&recherche);
            if(retrouver != NULL && (retrouver->adresse + retrouver->taille) == (KERNEL_INT)pointer){
                retrouver->taille += trouver->taille + (KERNEL_INT)Memory_size;
                k_retirer_noeud_avl(&(heap.avl_taille),retrouver->noeud_taille);
                retrouver->noeud_taille = k_ajouter_avl(&(heap.avl_taille),retrouver);
            }
            else{
                kFreeSpace* nouveau = k_creer_freespace((KERNEL_INT)pointer,(KERNEL_INT)Memory_size + trouver->taille,heap.tableau_freespace,&(heap.nb_freespaces));
                nouveau->noeud_adresse = k_ajouter_avl(&(heap.avl_adresse),nouveau);
                nouveau->noeud_taille = k_ajouter_avl(&(heap.avl_taille),nouveau);
            }
            k_supprimer_freespace(trouver,heap.tableau_freespace,&(heap.nb_freespaces));
        }
        else{// <=> (trouver->adresse + trouver->taille) == (KERNEL_INT)pointer
            trouver->taille += (KERNEL_INT)Memory_size;
            k_retirer_noeud_avl(&(heap.avl_taille),trouver->noeud_taille);
            trouver->noeud_taille = k_ajouter_avl(&(heap.avl_taille),trouver);
        }
    }
}