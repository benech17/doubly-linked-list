#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "projet2019.h"

#define min(a,b) (a<=b?a:b)
#define NTRANCHES 1024
#define nsize(x) (sizeof(x) + sizeof(node))

size_t nb_blocs(size_t n){
    return ceil((double)n/(double)sizeof(align_data));
}

void* ld_create(size_t nboctets){
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

 void* ld_first(void* liste){
     head* hd=liste;
     if(hd->nb_elem==0){
         return NULL;
     }
     return (node*)(align_data*)(hd->memory + hd->first);
 }

 void* ld_last(void* liste){
    head* hd=liste;
    if(hd->nb_elem==0){
         return NULL;
    }
    return (node*)(align_data*)(hd->memory + hd->last);
 }

 void* ld_next(void* liste,void* current){
     head* hd=liste;
     if((head*)liste==(head*)current){
         return ld_first(liste);
     }
     node* noeud=current;
     if(noeud->next==0){
         return NULL;
     }else{
         return (node*)(align_data*)(noeud + noeud->next);
     }
 }

 void* ld_previous(void* liste,void* current){
     head* hd=liste;
     if((head*)liste==(head*)current){
         return ld_first(liste);
     }
     node* noeud=current;
     if(noeud->previous==0){
         return NULL;
     }else{
         return (node*)(align_data*)(noeud + noeud->previous);
     }
 }

 void ld_destroy(void* liste){
     head* hd=liste;
     free(hd->memory);
     free(hd->libre);
     free(hd);
 }

 size_t ld_get(void* liste, void* current, size_t len, void* val){
     head* hd=liste;
     align_data* v=val;
     node* cur=current;
     len= min(len, cur->len);
     memmove(v, cur->data , len*sizeof(align_data));
     return len*sizeof(align_data);
 }

static int index_of_node(void* liste, void* n){
    head* hd=liste;
    node* nd=n;
    node* curr=(node*)(align_data*)(hd->memory + hd->first);

    int i=1;
    while(curr!=NULL && curr!=nd){
        //i+=curr->next;
        curr=(node*)(align_data*)(hd->memory + curr->next);
    }
    return i;
}

void* ld_insert_first(void* liste, size_t len, void* p_data){
    // len :taille du node
    head* hd=liste;
    node* new_node;
    node* first_node = ld_first(hd);

    
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i<NTRANCHES;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len)){
            int dec=tab_tranche[i].decalage;
            printf("dec: %d\n",dec);
            new_node = (node*)(align_data*)(hd->memory + dec); 
              
            if(first_node!=NULL)
                    printf("t1 %ld\n",first_node->len); //print la bonne valeur!
            new_node->previous=0;
            
            if(first_node!=NULL)
                    printf("t2 %ld\n",first_node->len); //print la mauvaise valeur 0 !

            new_node->next= hd->first - dec;
            
            new_node->len=len;
            
            memmove(new_node->data , (align_data*) p_data , len-sizeof(node));

            if(first_node!=NULL){
                first_node->previous = dec - hd->first;
            }
          
            hd->first = dec;
          
            if(hd->nb_elem==0){
                hd->last= dec;
            }
            tab_tranche[i].decalage = dec + nb_blocs(len);
            tab_tranche[i].nb_blocs -= nb_blocs(len);

            hd->nb_elem++;
            hd->nb_bloc_libre--;

       
            return new_node;
             
        }
    }
    return NULL;
}

void* ld_insert_last(void* liste, size_t len, void* p_data){
    // len :taille du node
    head* hd=liste;
    node* new_node;
    node* last_node = ld_last(hd);
    
   
   //le champ nb_bloc_libre me semble inutile??
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i<NTRANCHES;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len)){
            int dec=tab_tranche[i].decalage;
            new_node = (node*)(align_data*)(hd->memory+dec); 
              
            new_node->previous= hd->last - dec;
            new_node->next= 0;
            new_node->len=len;
            memmove(new_node->data , (align_data*) p_data , len-sizeof(node));

            if(last_node!=NULL)
                last_node->next = dec - hd->last;

            hd->last = dec;

            if(hd->nb_elem==0){
                hd->first= dec;
            }
            tab_tranche[i].decalage = dec + nb_blocs(len);
            tab_tranche[i].nb_blocs -= nb_blocs(len);

            hd->nb_elem++;
            hd->nb_bloc_libre--;

            return new_node;
             
        }
    }
    return NULL;
}

void* ld_insert_before(void* liste, void* n, size_t len, void* p_data){
      // len :taille du node
    head* hd=liste;
    node* new_node;
    node* curr = n;
    node* prev;
    if(curr->previous==0)
        return ld_insert_first(hd,len,p_data);
    //donc prev n'est pas NULL

    prev= (node*)ld_previous(hd,curr);
   
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i<NTRANCHES;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len)){
            int dec=tab_tranche[i].decalage;
            new_node = (node*)(align_data*)(hd->memory + dec); 
              
            new_node->previous= curr->previous + (curr-new_node);
            new_node->next= curr-new_node;
            new_node->len=len;
            memmove(new_node->data , (align_data*) p_data , len-sizeof(node));
             

            curr->previous= new_node-curr;
            
            prev->next -= (curr - new_node); //la ligne qui provoque segmentation fault!

            tab_tranche[i].decalage = dec + nb_blocs(len);
            tab_tranche[i].nb_blocs -= nb_blocs(len);

            hd->nb_elem++;
            hd->nb_bloc_libre--;

            return new_node;
             
        }
    }
    return NULL;
}

void* ld_insert_after(void* liste, void* n, size_t len, void* p_data){
      // len :taille du node
    head* hd=liste;
    node* new_node;
    node* curr = n;
    node* next;
    if(curr->next==0)
        return ld_insert_last(hd,len,p_data);

    next= (node*)(align_data*)(curr + curr->next);
    int curr_index=index_of_node(hd,curr);
   
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i<NTRANCHES;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len)){
            int dec=tab_tranche[i].decalage;
            new_node = (node*)(align_data*)(hd->memory + dec); 
              
            new_node->previous= curr_index - dec;
            new_node->next= curr->next - (dec - curr_index);
            new_node->len=len;
            memmove(new_node->data , (align_data*) p_data , len-sizeof(node));
             
            next->previous = -(new_node->next);

            curr->next = dec - curr_index;

            tab_tranche[i].decalage = dec + nb_blocs(len);
            tab_tranche[i].nb_blocs -= nb_blocs(len);

            hd->nb_elem++;
            hd->nb_bloc_libre--;

            return new_node;
             
        }
    }
    return NULL;
}

size_t ld_total_free_memory(void *liste){
    head* hd= liste;
    return (size_t)(hd->nb_bloc_libre * sizeof(align_data));
}

int main(){
    head* hd= ld_create(1000);
    align_data data1[5];
    data1->a=1;
    (data1+1)->a=2;
    (data1+2)->a=3;
    (data1+3)->a=4;
    (data1+4)->a=5;

    align_data data2[3];
    data2->a=10;
    (data2+1)->a=20;
    (data2+2)->a=30;

    align_data data3[6];
    data3->a=-1;
    (data3+1)->a=-2;
    (data3+2)->a=-3;
    (data3+3)->a=-4;
    (data3+4)->a=-5;
    (data3+5)->a=-6;

    node* n = (node*)(align_data*)(hd->memory + 0);

    ld_insert_first(hd,nsize(data1),data1);
    printf("%ld\n",n->len);


    //printf("last1 :%ld \n", ((node*) ld_last(hd)) -> len); 

    //printf("%ld \n", ((node*) ld_first(hd)) -> data[3].a); //print 4

    ld_insert_first(hd,nsize(data2),data2);

    //printf("last2: %ld \n", ((node*) ld_last(hd)) -> len); bug
    printf("%ld\n",n->len); //bug

    //printf("%ld \n", ((node*) ld_first(hd)) -> data[2].a); //print 30

    ld_insert_first(hd,nsize(data3),data3);
    //printf("%ld \n", ((node*) ld_first(hd)) -> data[4].a); //print -5

    //printf("last3 : %ld \n", ((node*) ld_last(hd)) -> len); bug

   printf("%ld\n",n->len); //bug
    
   // ld_insert_before(hd,n,nsize(data2),data2);
    return 0;
}
