#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "projet2019.h"

#define NTRANCHES 1024

size_t nb_blocs(size_t n){
    return ceil((double)n/(double)sizeof(align_data));
}

void * ld_create(size_t nboctets){
    tranche* tab_tranches =malloc(NTRANCHES * sizeof(tranche));
    head* res=malloc(sizeof(head));
    res->size=nb_blocs(nboctets)*sizeof(align_data);
    res->memory=malloc(res->size);
    res->first=0;
    res->last=0;
    res->libre=tab_tranches;
    res->nb_bloc_libre=nb_blocs(nboctets);
    res->nb_elem=0;
    tab_tranches[0].decalage=0;
    tab_tranches[0].nb_blocs=res->nb_bloc_libre;
    return res;

}

 void * ld_first(void* liste){
     head* head=liste;
     if(head->nb_elem=0){
         return NULL;
     }
     return (node*)(align_data*)(head->memory)+(head->first);
 }

 void* ld_last(void* liste){
     head* head=liste;
    if(head->nb_elem=0){
         return NULL;
    }
    return (node*)(align_data*)(head->memory)+(head->last);
 }

 void* ld_next(void* liste,void* current){
     head* head=liste;
     if(liste==current){
         return ld_first(liste);
     }
     node* noeud=current;
     if(noeud->next=0){
         return NULL;
     }else{
         return (node*)(align_data*)(head->memory)+(noeud->next);
     }
 }

 void* ld_previous(void* liste,void* current){
     head* head=liste;
     if(liste==current){
         return ld_first(liste);
     }
     node* noeud=current;
     if(noeud->previous=0){
         return NULL;
     }else{
         return (node*)(align_data*)(head->memory)+(noeud->previous);
     }
 }


int main()
{
    printf("%ld\n",sizeof(align_data));
    printf("%ld\n",nb_blocs(101));
    return 0;
}