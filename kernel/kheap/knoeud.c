#include <kheap/knoeud.h>
#include <kheap/kavl.h>
#include <stddef.h>

kNoeud* k_creer_kNoeud(kFreeSpace* freespace,kNoeud* tableau_noeud,int count){
    kNoeud* return_ = &(tableau_noeud[count]);
    return_->freespace = freespace;
    return_->gauche = NULL;
    return_->droite = NULL;
    return_->precedent = NULL;
    return return_;
}

kFreeSpace* k_supprimer_kNoeud(kNoeud* noeud,void* avl,kNoeud* tableau_noeud,int count){
    kFreeSpace* return_ = noeud->freespace;
    
    kNoeud* remplacement = &(tableau_noeud[count-1]);
    if(noeud != remplacement){
        noeud->droite = remplacement->droite;
        if(remplacement->droite != NULL)
            remplacement->droite->precedent = noeud;
        noeud->gauche = remplacement->gauche;
        if(remplacement->gauche != NULL)
            remplacement->gauche->precedent = noeud;
        noeud->precedent = remplacement->precedent;
        if(remplacement->precedent != NULL){
            if(remplacement->precedent->droite == remplacement)
                remplacement->precedent->droite = noeud;
            else
                remplacement->precedent->gauche = noeud;
        }
        else
            ((kAVL*)avl)->debut = noeud;
        noeud->freespace = remplacement->freespace;
    }

    return return_;
}