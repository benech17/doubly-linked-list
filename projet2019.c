#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "projet2019.h"

#define min(a,b) (a<=b?a:b)
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
     return (node*)(align_data*)(head->memory + head->first);
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

 void ld_destroy(void *liste){
     head* hd=liste;
     free(hd->memory);
     free(hd->libre);
     free(hd);
 }

 size_t ld_get(void *liste, void *current, size_t len, void *val){
     head* hd=liste;
     align_data* v=val;
     node* cur=current;
     len= min(len, cur->len);
     memmove(v, cur->data , len*sizeof(align_data));
     return len*sizeof(align_data);
 }

void * ld_insert_first(void *liste, size_t len, void *p_data){
    // len :taille du node
    head* hd=liste;
    node* new_node;
    node* first_node = malloc(sizeof(node));
    first_node->len=sizeof(node);
    first_node->previous=0;
    first_node->next=0;
    memmove(new_node->data , (align_data*) p_data , len-sizeof(node));
    new_node->len=len;
    
    if(hd->nb_bloc_libre < len){
        return NULL;
    }
    tranche* tab_tranche = hd->libre;

    for(int i=0;i<NTRANCHES;i++){
        if(10000000>= nb_blocs(len)){
            tab_tranche[i].nb_blocs-=len;
            int dec=tab_tranche[i].decalage;
            new_node->previous=0;
            new_node->next= hd->first - dec;
            first_node->previous = dec - hd->first;
            hd->first = dec;
            tab_tranche[i].decalage = dec + len;
            tab_tranche[i].nb_blocs -= len;
            hd->nb_elem++;
            hd->nb_bloc_libre--;
            memmove((align_data*) hd->memory+dec , new_node , len);
            break;
             
        }
    }
    return new_node;
}