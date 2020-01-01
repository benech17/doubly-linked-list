#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "projet2019.h"

<<<<<<< HEAD
static void* dec_to_pointer(void* p, ptrdiff_t dec){
    return ((align_data*)(p) + dec);
}

static void delete_tranche_at(void* liste, int i){
    head* hd=liste;
    tranche* tab_tranche = hd->libre;
    memmove(tab_tranche + i , tab_tranche + (i+1), sizeof(tranche)*(hd->nb_elem_tab_tanches - (i+1)));
}

static ptrdiff_t diff_node_AD(void* n1, void* n2){
    // difference entre de noeud en align_data
    return (align_data*) n1 - (align_data*) n2 ;
} 
=======
#define min(a,b) (a<=b?a:b)
#define NTRANCHES 1024
#define nsize(x) (sizeof(x) + sizeof(node))
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8

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
    res->nb_elem_tab_tanches=1;
    tab_tranches[0].decalage=0;
    tab_tranches[0].nb_blocs=res->nb_bloc_libre;
    return res;

}

 void* ld_first(void* liste){
     head* hd=liste;
     if(hd->nb_elem==0){
         return NULL;
     }
     return (node*)(dec_to_pointer(hd->memory, hd->first));
 }

 void* ld_last(void* liste){
    head* hd=liste;
    if(hd->nb_elem==0){
         return NULL;
    }
    return (node*)(dec_to_pointer(hd->memory, hd->last));
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
<<<<<<< HEAD
        return (node*) (dec_to_pointer(noeud, noeud->next));
=======
         return (node*)(align_data*)(noeud + noeud->next);
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8
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
<<<<<<< HEAD
        return (node*) (dec_to_pointer(noeud, noeud->previous));
=======
         return (node*)(align_data*)(noeud + noeud->previous);
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8
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

<<<<<<< HEAD


=======
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8
void* ld_insert_first(void* liste, size_t len, void* p_data){
    // len :taille du data
    head* hd=liste;
    node* new_node;
    node* first_node = ld_first(hd);
<<<<<<< HEAD
   
   //le champ nb_bloc_libre me semble inutile??
=======

    
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i< hd->nb_elem_tab_tanches ;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len)){
<<<<<<< HEAD
            ptrdiff_t dec=tab_tranche[i].decalage;
            printf("dec: %ld\n",dec);
            new_node = (node*)(dec_to_pointer(hd->memory, dec)); 
=======
            int dec=tab_tranche[i].decalage;
            printf("dec: %d\n",dec);
            new_node = (node*)(align_data*)(hd->memory + dec); 
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8
              
            if(first_node!=NULL)
                    printf("t1 %ld\n",first_node->len); //print la bonne valeur!
            new_node->previous=0;
<<<<<<< HEAD
            if(first_node==NULL)    
                new_node->next= 0;
            else
                new_node->next= hd->first - dec;

            new_node->len= nb_blocs(sizeof(node) + len);

            memmove(new_node->data , (align_data*) p_data , len);

=======
            
            if(first_node!=NULL)
                    printf("t2 %ld\n",first_node->len); //print la mauvaise valeur 0 !

            new_node->next= hd->first - dec;
            
            new_node->len=len;
            
            memmove(new_node->data , (align_data*) p_data , len-sizeof(node));

>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8
            if(first_node!=NULL){
                first_node->previous = dec - hd->first;
            }
          
            hd->first = dec;
          
            if(hd->nb_elem==0){
                hd->last= dec;
            }
            tab_tranche[i].decalage += new_node->len;
            tab_tranche[i].nb_blocs -= nb_blocs(len);

            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                delete_tranche_at(hd,i);
            }

            hd->nb_elem++;
            hd->nb_bloc_libre--;

       
            return new_node;
             
        }
    }
    return NULL;
}

void* ld_insert_last(void* liste, size_t len, void* p_data){
    // len :taille du data
    head* hd=liste;
    node* new_node;
    node* last_node = ld_last(hd);
    
   
   //le champ nb_bloc_libre me semble inutile??
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i<NTRANCHES;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len + sizeof(node))){
            ptrdiff_t dec=tab_tranche[i].decalage;
            new_node = (node*) dec_to_pointer(hd->memory, dec); 
              
            
            new_node->next= 0;
            if(last_node==NULL)    
                new_node->previous= 0;
            else
                new_node->previous= hd->last - dec;

            new_node->len= nb_blocs(len + sizeof(node));
            memmove(new_node->data , (align_data*) p_data , len);

            if(last_node!=NULL)
                last_node->next = dec - hd->last;

            hd->last = dec;

            if(hd->nb_elem==0){
                hd->first= dec;
            }
            tab_tranche[i].decalage += new_node->len;
            tab_tranche[i].nb_blocs -= nb_blocs(len);

            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                            delete_tranche_at(hd,i);
            }
            hd->nb_elem++;
            hd->nb_bloc_libre--;

            return new_node;
             
        }
    }
    return NULL;
}

void* ld_insert_before(void* liste, void* n, size_t len, void* p_data){
    // len :taille du data
    head* hd=liste;
    node* new_node;
    node* curr = n;
    node* prev_node;
    if(curr->previous==0)
        return ld_insert_first(hd,len,p_data);
    //donc prev n'est pas NULL

<<<<<<< HEAD
    prev_node= (node*) ld_previous(hd,curr);
=======
    prev= (node*)ld_previous(hd,curr);
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8
   
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i< hd->nb_elem_tab_tanches ;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len)){
            ptrdiff_t dec=tab_tranche[i].decalage;
            printf("dec: %ld\n",dec);

            new_node = (node*)(dec_to_pointer(hd->memory, dec)); 
              
<<<<<<< HEAD
            new_node->previous= diff_node_AD(prev_node, new_node);
            new_node->next= diff_node_AD(curr, new_node);
            new_node->len= nb_blocs(len + sizeof(node));
            memmove(new_node->data , (align_data*) p_data , len);
             

            curr->previous= diff_node_AD(new_node, curr);

            prev_node->next = diff_node_AD(new_node, prev_node);
=======
            new_node->previous= curr->previous + (curr-new_node);
            new_node->next= curr-new_node;
            new_node->len=len;
            memmove(new_node->data , (align_data*) p_data , len-sizeof(node));
             

            curr->previous= new_node-curr;
            
            prev->next -= (curr - new_node); //la ligne qui provoque segmentation fault!
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8

            tab_tranche[i].decalage += new_node->len;
            tab_tranche[i].nb_blocs -= nb_blocs(len);
            
            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                delete_tranche_at(hd,i);
            }

            hd->nb_elem++;
            hd->nb_bloc_libre--;

            return new_node;
             
        }
    }
    return NULL;
}

void* ld_insert_after(void* liste, void* n, size_t len, void* p_data){
    // len :taille du data
    head* hd=liste;
    node* new_node;
    node* curr = n;
    node* next_node;
    if(curr->next==0)
        return ld_insert_last(hd,len,p_data);

    next_node= (node*) ld_next(hd, curr);
   
    if((hd->nb_bloc_libre) < nb_blocs(len)){
        return NULL;
    }

    tranche* tab_tranche = hd->libre;

    for(int i=0;i< hd->nb_elem_tab_tanches ;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len)){
            ptrdiff_t dec=tab_tranche[i].decalage;
            new_node = (node*)(dec_to_pointer(hd->memory, dec)); 
              
            new_node->previous= diff_node_AD(curr, new_node);
            new_node->next= diff_node_AD(next_node, new_node);
            new_node->len=len;
            memmove(new_node->data , (align_data*) p_data , len);
             
            next_node->previous = diff_node_AD(new_node, next_node);

            curr->next = diff_node_AD(new_node, curr);

            tab_tranche[i].decalage += new_node->len;
            tab_tranche[i].nb_blocs -= nb_blocs(len);

            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                delete_tranche_at(hd,i);
            }

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

<<<<<<< HEAD
    align_data data4[4];
    data4->a=41;
    (data4+1)->a=42;
    (data4+2)->a=43;
    (data4+3)->a=44;


    ld_insert_first(hd,sizeof(data1),data1);
    node* n = (node*) dec_to_pointer(hd->memory, 0);
    printf("%ld\n",n->previous);


    //printf("last->len: %ld \n", ((node*) ld_last(hd)) -> len); print 7

    //printf("%ld \n", ((node*) ld_first(hd)) -> data[3].a); //print 4

    ld_insert_first(hd,sizeof(data2),data2);
    //printf("last->len: %ld \n", ((node*) ld_last(hd)) -> len);  print 7

    printf("%ld\n",n->previous);
    //printf("%ld \n", ((node*) ld_last(hd)) -> data[2].a);
    

    //printf("%ld \n", ((node*) ld_first(hd)) -> data[2].a); //print 30

    ld_insert_first(hd,sizeof(data3),data3);
    //printf("%ld \n", ((node*) ld_first(hd)) -> data[4].a); //print -5
    //printf("last->len: %ld \n", ((node*) ld_last(hd)) -> len); //print 7


   printf("%ld\n",n->previous);
    //  printf("%d\n",index_of_node(hd,n));
    
    ld_insert_before(hd,n,sizeof(data4),data4);
    
    node* nn = (node*) ld_previous(hd,n);
    printf("prevv : %ld\n",nn->data[2].a); // print 43
=======
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
>>>>>>> 21bed873226f1b4a41ed6594fa546313d42208a8

   printf("%ld\n",n->len); //bug
    
   // ld_insert_before(hd,n,nsize(data2),data2);
    return 0;
}
