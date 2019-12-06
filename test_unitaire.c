#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "projet2019.h"

void print_data(int n,void* data){
    long int* d=data;
    for(int i=0;i<n;i++){
        printf("|%ld", d[i]);
    }
}

void print(void* liste){
    node* noeud=ld_first(liste);
    while(ld_next(liste,noeud)!=NULL){
        printf("next : %ld | prev: %ld | size: %lu|", noeud->next, noeud->previous,noeud->len);
        print_data(noeud->len, noeud->data);
        print("|\n");
    }
}
int main(){
    head* hd= ld_create(100);
    align_data data[5]= {1,2,3,4,5};

    ld_insert_first(hd,sizeof(node)+5*sizeof(align_data),data);
   // printf("%d \n",hd->first);
    printf("%ld \n", ((node*) ld_first(hd)) -> data[1]);
    return 0;
}