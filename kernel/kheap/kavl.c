#include<kheap/kavl.h>
#include <stddef.h>

#define FIXER 1
#define NON_FIXER 0
void fixer(kAVL* avl,kNoeud* noeud);
void tri(kAVL* avl,kNoeud* noeud);
void rotation_droite(kAVL* avl,kNoeud* dessus);
void rotation_gauche(kAVL* avl,kNoeud* dessus);
void set_hauteur(kNoeud* noeud);
int get_diff_hauteur(kNoeud* noeud);
int get_hauteur(kNoeud* noeud);

kNoeud* trouver_remplacement(kNoeud* noeud);
kNoeud* remplacer(kAVL* avl,kNoeud* noeud,kNoeud* remplacement); // la sortie pour le tri

kAVL k_creer_avl(int (*test_tri)(void*,void*),kNoeud* tableau_noeud){
    kAVL avl;
    avl.debut = NULL;
    avl.test_tri = test_tri;
    avl.count = 0;
    avl.tableau_noeud = tableau_noeud;
    return avl;
}

kNoeud* k_ajouter_avl(kAVL* avl,kFreeSpace* freespace){
    kNoeud* nouveau = k_creer_kNoeud(freespace,avl->tableau_noeud,avl->count);
    fixer(avl,nouveau);
    tri(avl,nouveau);
    (avl->count)++;
    return nouveau;
}

kNoeud* k_trouver_noeud_avl(kAVL* avl,kFreeSpace* freespace){
    if(avl->debut == NULL)
        return NULL;
    kNoeud* return_ = NULL;
    kNoeud* actuel = avl->debut;
    while(actuel != NULL){
        if(avl->test_tri((void*)actuel->freespace,(void*)freespace)){
            return_ = actuel;
            actuel = actuel->droite;
        }
        else
            actuel = actuel->gauche;
    }
    return return_;
}

kFreeSpace* k_trouver_avl(kAVL* avl,kFreeSpace* freespace){
    kNoeud* return_ = k_trouver_noeud_avl(avl,freespace);
    if(return_ == NULL)
        return NULL;
    return (void*)return_->freespace;
}

kFreeSpace* k_retirer_noeud_avl(kAVL* avl,kNoeud* noeud){
    if(noeud == NULL)
        return NULL;
    
    tri(avl,remplacer(avl,noeud,trouver_remplacement(noeud)));
    (avl->count)--;
    return k_supprimer_kNoeud(noeud,avl,avl->tableau_noeud,avl->count + 1);
}

kFreeSpace* k_retirer_avl(kAVL* avl,kFreeSpace* freespace){
    return k_retirer_noeud_avl(avl,k_trouver_noeud_avl(avl,freespace));
}

void fixer(kAVL* avl,kNoeud* noeud){
    if(avl->debut == NULL)
        avl->debut = noeud;
    else{
        kNoeud* actuel = avl->debut;
        int fixe = NON_FIXER;
        while(fixe != FIXER){
            if(avl->test_tri((void*)noeud->freespace,(void*)actuel->freespace)){
                if(actuel->gauche == NULL){
                    noeud->precedent = actuel;
                    actuel->gauche = noeud;
                    fixe = FIXER;
                }
                else
                    actuel = actuel->gauche;
            }
            else{
                if(actuel->droite == NULL){
                    noeud->precedent = actuel;
                    actuel->droite = noeud;
                    fixe = FIXER;
                }
                else
                    actuel = actuel->droite;
            }
        }
    }
}

void tri(kAVL* avl,kNoeud* noeud){
    while(noeud != NULL){
        switch (get_diff_hauteur(noeud)){
        case -2:// plus haut a gauche
            if(get_diff_hauteur(noeud->gauche) == 1){// alors desequilibre a gauche puis droite
                noeud = noeud->gauche;
                rotation_gauche(avl,noeud);
                set_hauteur(noeud);
                noeud = noeud->precedent->precedent;
                rotation_droite(avl,noeud);
            }
            else
                rotation_droite(avl,noeud);
            break;
        case 2:// plus haut a droite
            if(get_diff_hauteur(noeud->droite) == -1){// alors desequilibre a droite puis gauche
                noeud = noeud->droite;
                rotation_droite(avl,noeud);
                set_hauteur(noeud);
                noeud = noeud->precedent->precedent;
                rotation_gauche(avl,noeud);
            }
            else
                rotation_gauche(avl,noeud);
            break;
        case -1:
        case 0: // cas normaux
        case 1:
            break;
        default:
            break;
        }
        set_hauteur(noeud);
        noeud = noeud->precedent;
    }
}

void rotation_droite(kAVL* avl,kNoeud* dessus){
    kNoeud* gauche = dessus->gauche;

    if(dessus->precedent != NULL){
        if(dessus->precedent->gauche == dessus)
            dessus->precedent->gauche = gauche;
        else
            dessus->precedent->droite = gauche;
    }
    else
        avl->debut = gauche;
    gauche->precedent = dessus->precedent;

    if(gauche->droite != NULL)
        gauche->droite->precedent = dessus;
    dessus->gauche = gauche->droite;

    dessus->precedent = gauche;
    gauche->droite = dessus;
}

void rotation_gauche(kAVL* avl,kNoeud* dessus){
    kNoeud* droite = dessus->droite;

    if(dessus->precedent != NULL){
        if(dessus->precedent->gauche == dessus)
            dessus->precedent->gauche = droite;
        else
            dessus->precedent->droite = droite;
    }
    else
        avl->debut = droite;
    droite->precedent = dessus->precedent;

    if(droite->gauche != NULL)
        droite->gauche->precedent = dessus;
    dessus->droite = droite->gauche;

    dessus->precedent = droite;
    droite->gauche = dessus;
}

void set_hauteur(kNoeud* noeud){
    noeud->count = (get_hauteur(noeud->droite) > get_hauteur(noeud->gauche))? get_hauteur(noeud->droite):get_hauteur(noeud->gauche);
    (noeud->count)++;
}

int get_diff_hauteur(kNoeud* noeud){
    return get_hauteur(noeud->droite) - get_hauteur(noeud->gauche);
}

int get_hauteur(kNoeud* noeud){
    if(noeud == NULL)
        return 0;
    else
        return noeud->count;
}

kNoeud* trouver_remplacement(kNoeud* noeud){
    if(noeud->droite == NULL && noeud->gauche == NULL)
        return NULL;
    kNoeud* return_;
    if(noeud->droite == NULL){
        return_ = noeud->gauche;
        if(return_->gauche != NULL)
            return_->gauche->precedent = noeud;
        noeud->gauche = return_->gauche;

        if(return_->droite != NULL)
            return_->droite->precedent = noeud;
        noeud->droite = return_->droite;
    }
    else if(noeud->gauche == NULL){
        return_ = noeud->droite;
        if(return_->gauche != NULL)
            return_->gauche->precedent = noeud;
        noeud->gauche = return_->gauche;

        if(return_->droite != NULL)
            return_->droite->precedent = noeud;
        noeud->droite = return_->droite;
    }
    else{
        return_ = noeud->gauche;
        while(return_->droite != NULL)
            return_ = return_->droite;
        
        if(return_->precedent->droite == return_)
            return_->precedent->droite = return_->gauche;
        else
            return_->precedent->gauche = return_->gauche;
        if(return_->gauche != NULL)
            return_->gauche->precedent = return_->precedent;
    }
    return return_;
}

kNoeud* remplacer(kAVL* avl,kNoeud* noeud,kNoeud* remplacement){
    kNoeud* return_;
    if(noeud->precedent != NULL){
        if(noeud->precedent->gauche == noeud)
            noeud->precedent->gauche = remplacement;
        else 
            noeud->precedent->droite = remplacement;
    }
    else
        avl->debut = remplacement;

    if(remplacement == NULL)
        return_ = noeud->precedent;
    else{
        if(remplacement->precedent != noeud)
            return_ = remplacement->precedent;
        else
            return_ = remplacement;

        remplacement->precedent = noeud->precedent;

        if(noeud->gauche != NULL)
            noeud->gauche->precedent = remplacement;
        remplacement->gauche = noeud->gauche;

        if(noeud->droite != NULL)
            noeud->droite->precedent = remplacement;
        remplacement->droite = noeud->droite;
    }
    return return_;
}