#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "projet2019.h"

static int recherche_binaire(void* tab,int size,ptrdiff_t dec){
    int left=0;
    int right=size-1;
    tranche* tab_tranche=tab;
    while(1){
        int mid=(right+left)/2;
        if(mid==left || mid==right){
            return mid;
        } 
        else if(dec<tab_tranche[mid].decalage){
            right=mid;
        }
        else{
            left=mid;
        }
    }
    return -1;
}
void* dec_to_pointer(void* p, ptrdiff_t dec){
    return ((align_data*)(p) + dec);
}

static void delete_tranche_at(void* liste, int i){
    head* hd=liste;
    hd->nb_elem_tab_tranches--;
    tranche* tab_tranche = hd->libre;
    memmove(tab_tranche + i , tab_tranche + (i+1), sizeof(tranche)*(hd->nb_elem_tab_tranches - (i+1)));
}

static ptrdiff_t diff_node_AD(void* n1, void* n2){
    // difference entre de noeud en align_data
    return (align_data*) n1 - (align_data*) n2 ;
} 

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
    res->nb_elem_tab_tranches=1;
    res->tab_tranches_size=NTRANCHES;
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
     if((head*)liste==(head*)current){
         return ld_first(liste);
     }
     node* noeud=current;
     if(noeud->next==0){
         return NULL;
     }else{
        return (node*) (dec_to_pointer(noeud, noeud->next));
     }
 }

 void* ld_previous(void* liste,void* current){
     if((head*)liste==(head*)current){
         return ld_first(liste);
     }
     node* noeud=current;
     if(noeud->previous==0){
         return NULL;
     }else{
        return (node*) (dec_to_pointer(noeud, noeud->previous));
     }
 }

 void ld_destroy(void* liste){
     head* hd=liste;
     free(hd->memory);
     free(hd->libre);
     free(hd);
 }

 size_t ld_get(void* liste, void* current, size_t len, void* val){
     align_data* v=val;
     node* cur=current;
     len= min(len, sizeof(cur->len));
     memmove(v, cur->data , len);
     return len;
 }

void* ld_insert_first(void* liste, size_t len, void* p_data){
    // len :taille du data
    head* hd=liste;
    node* new_node;
    node* first_node = ld_first(hd);

    tranche* tab_tranche = hd->libre;

    for(int i=0;i< hd->nb_elem_tab_tranches ;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len +sizeof(node))){
            ptrdiff_t dec=tab_tranche[i].decalage;
            printf("dec: %ld\n",dec);
            new_node = (node*)(dec_to_pointer(hd->memory, dec)); 
              
            new_node->previous=0;
            if(first_node==NULL)    
                new_node->next= 0;
            else
                new_node->next= hd->first - dec;

            new_node->len= nb_blocs(sizeof(node) + len);

            memmove(new_node->data , (align_data*) p_data , len);

            if(first_node!=NULL){
                first_node->previous = dec - hd->first;
            }
          
            hd->first = dec;
          
            if(hd->nb_elem==0){
                hd->last= dec;
            }
            tab_tranche[i].decalage += new_node->len;
            tab_tranche[i].nb_blocs -= new_node->len;

            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                delete_tranche_at(hd,i);
            }

            hd->nb_elem++;
            hd->nb_bloc_libre-= new_node->len;

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
            tab_tranche[i].nb_blocs -= new_node->len;

            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                            delete_tranche_at(hd,i);
            }
            hd->nb_elem++;
            hd->nb_bloc_libre-= new_node->len;


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

    prev_node= (node*) ld_previous(hd,curr);

    tranche* tab_tranche = hd->libre;

    for(int i=0;i< hd->nb_elem_tab_tranches ;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len + sizeof(node))){
            ptrdiff_t dec=tab_tranche[i].decalage;
            printf("dec: %ld\n",dec);

            new_node = (node*)(dec_to_pointer(hd->memory, dec)); 
              
            new_node->previous= diff_node_AD(prev_node, new_node);
            new_node->next= diff_node_AD(curr, new_node);
            new_node->len= nb_blocs(len + sizeof(node));
            memmove(new_node->data , (align_data*) p_data , len);
             

            curr->previous= diff_node_AD(new_node, curr);

            prev_node->next = diff_node_AD(new_node, prev_node);

            tab_tranche[i].decalage += new_node->len;
            tab_tranche[i].nb_blocs -= new_node->len;
            
            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                delete_tranche_at(hd,i);
            }

            hd->nb_elem++;
            hd->nb_bloc_libre-= new_node->len;

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

    tranche* tab_tranche = hd->libre;

    for(int i=0;i< hd->nb_elem_tab_tranches ;i++){
        if( tab_tranche[i].nb_blocs> nb_blocs(len + sizeof(node))){
            ptrdiff_t dec=tab_tranche[i].decalage;
            new_node = (node*)(dec_to_pointer(hd->memory, dec)); 
              
            new_node->previous= diff_node_AD(curr, new_node);
            new_node->next= diff_node_AD(next_node, new_node);
            new_node->len= nb_blocs(len + sizeof(node));
            memmove(new_node->data , (align_data*) p_data , len);
             
            next_node->previous = diff_node_AD(new_node, next_node);

            curr->next = diff_node_AD(new_node, curr);

            tab_tranche[i].decalage += new_node->len;
            tab_tranche[i].nb_blocs -= new_node->len;

            if(tab_tranche[i].nb_blocs < nb_blocs(sizeof(node))){
                delete_tranche_at(hd,i);
            }

            hd->nb_elem++;
            hd->nb_bloc_libre-= new_node->len;

            return new_node;
             
        }
    }
    return NULL;
}

void* ld_delete_node(void* liste, void* n){
    head* hd =liste;
    node* curr=n;
    node* prev_node=ld_previous(hd,curr);
    node* next_node=ld_next(hd,curr);
    tranche* tab_tranche=hd->libre;
    ptrdiff_t dec = diff_node_AD(curr,hd->memory);
    int pos=recherche_binaire(tab_tranche,hd->nb_elem_tab_tranches,dec);

    hd->nb_bloc_libre += curr->len;
    hd->nb_elem--;
    
    if( (tab_tranche[pos].decalage + tab_tranche[pos].nb_blocs) >=dec){  //fusion des tranches,elargissement
        tab_tranche[pos].nb_blocs+= curr->len;
    }
    else{
        if(hd->tab_tranches_size == hd->nb_elem_tab_tranches){  //tableau de tranches remplie
            hd->tab_tranches_size*=2; //double la taille
        }       
        memmove(  tab_tranche+pos+1  , tab_tranche+pos , hd->nb_elem_tab_tranches - pos );
        hd->nb_elem_tab_tranches++;
        tab_tranche[pos+1].decalage=dec;
        tab_tranche[pos+1].nb_blocs= curr->len;
    }


    if(curr->previous==0 && curr->next==0){
        hd->first=0;
        hd->last=0;
        hd->nb_elem=0;
    }
    else if(curr->previous==0){
        hd->first=dec + curr->next;
        next_node->previous=0;
    }
    else if(curr->next==0){
        hd->last=dec+curr->previous;
        prev_node->next=0;
    }
    else{
        prev_node->next=diff_node_AD(next_node,prev_node);
        next_node->previous=diff_node_AD(prev_node,next_node);
    }
    return hd;
}

size_t ld_total_free_memory(void* liste){
    head* hd= liste;
    return (size_t)(hd->nb_bloc_libre * sizeof(align_data));
}

size_t ld_total_useful_memory(void* liste){
    head* hd= liste;
    tranche* tab_tranche= hd->libre;
    size_t res=0;
    for(int i=0;i< hd->nb_elem_tab_tranches ;i++){
        if( tab_tranche[i].nb_blocs >= sizeof(node))
            res+= tab_tranche[i].nb_blocs * sizeof(align_data) ;
    }
    return res;
}

void *ld_add_memory(void* liste, size_t nboctets){
    head* hd= liste;
    tranche* tab_tranche = hd->libre;
    if(nboctets<0)
        return NULL;
    size_t no = nb_blocs(nboctets) * sizeof(align_data);
    size_t tab_size = hd->nb_elem_tab_tranches;
    tab_tranche[tab_size].decalage= nb_blocs(hd->size);
    tab_tranche[tab_size].nb_blocs= nb_blocs(no);
    hd->size += no;
    hd->nb_elem++;
    hd->nb_bloc_libre += nb_blocs(no);
    return hd;
}

void *ld_compactify(void* liste){
    head* hd= liste;
    tranche* tab_tranche = hd->libre;
    node* curr = ld_first(hd);
    
    void* new_memory = malloc(hd->size);
    if(new_memory==NULL)
        return NULL;
    
    ptrdiff_t pos=0;
    while(curr != NULL){
        memmove( ((align_data*) (new_memory) + pos) , curr , (curr->len)*sizeof(align_data));
        pos+= curr->len ;
        curr = ld_next(hd, curr);
    }
    tab_tranche[0].decalage = pos + curr->len;
    tab_tranche[0].nb_blocs = hd->nb_bloc_libre;
    hd->memory = new_memory;
    hd->first= 0;
    hd->last = pos;
    hd->nb_elem_tab_tranches= 1;

    return hd;
}