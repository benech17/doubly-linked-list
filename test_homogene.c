#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "projet2019.h"

void print_data(int n,void* data){
    align_data* d=data;
    printf("[");
    for(int i=0;i<n-1;i++){
        printf("%ld, ", d[i].a);
    }
    printf("%ld]", d[n-1].a);
}

void print(void* liste){
    head* hd=liste;
    node* noeud=ld_first(liste);
    int i=1;
    printf("\n Head : ||first: %ld |last: %ld |size: %lu |nb_elem: %lu |nb_bloc_libre: %lu |tab_tranches_size: %lu |nb_elem_tab_tanches: %lu ||\n",
        hd->first, hd->last, hd->size, hd->nb_elem, hd->nb_bloc_libre, hd->tab_tranches_size, hd->nb_elem_tab_tranches );

    while(noeud!=NULL){
        printf("node%d {",i++);
        printf("next : %ld | prev: %ld | len: %lu | data: ", noeud->next, noeud->previous, noeud->len);
        print_data(noeud->len - nb_blocs(sizeof(node)), noeud->data);
        printf(" }\n");
        noeud= ld_next(liste,noeud);
    }

    printf("total_free_memory: %lu Byte | total_useful_memory: %lu Byte \n", ld_total_free_memory(hd), ld_total_useful_memory(hd));
}

align_data* create_data(int size,int first){
    align_data* data= malloc(size * sizeof(align_data));
    for(int i=0;i<size;i++){
        (data+i)->a=first++;
    }
    return data;
}

int main()
{
    head *hd = ld_create(10000);

    align_data* data1 =create_data(3,1);
    align_data* data10 =create_data(3,11);
    align_data* data20 =create_data(3,21);
    align_data* data30 =create_data(3,31);
    align_data* data40 =create_data(3,41);
    align_data* data50 =create_data(3,51);
    align_data* data60 =create_data(3,61);
    align_data* data70 =create_data(3,71);
    align_data* data80 =create_data(3,81);
    align_data* data90 =create_data(3,91);
    align_data* data100 =create_data(3,101);
    align_data* data110 =create_data(3,111);
    align_data* data120 =create_data(3,121);
    align_data* data130 =create_data(3,131);
    align_data* data140 =create_data(3,141);
    align_data* data150 =create_data(3,151);
    align_data* data160 =create_data(3,161);
    align_data* data170 =create_data(3,171);

    ld_insert_first(hd,3*sizeof(align_data),data1);
    ld_insert_last(hd,3*sizeof(align_data),data10);
    ld_insert_first(hd,3*sizeof(align_data),data20);
    ld_insert_last(hd,3*sizeof(align_data),data30);
    ld_insert_first(hd,3*sizeof(align_data),data40);
    ld_insert_first(hd,3*sizeof(align_data),data50);
    ld_insert_first(hd,3*sizeof(align_data),data60);
    ld_insert_last(hd,3*sizeof(align_data),data70);
    ld_insert_last(hd,3*sizeof(align_data),data80);
    ld_insert_first(hd,3*sizeof(align_data),data90);
    ld_insert_last(hd,3*sizeof(align_data),data100);
    ld_insert_first(hd,3*sizeof(align_data),data110);
    ld_insert_last(hd,3*sizeof(align_data),data120);
    ld_insert_first(hd,3*sizeof(align_data),data130);
    ld_insert_first(hd,3*sizeof(align_data),data140);
    ld_insert_first(hd,3*sizeof(align_data),data150);
    ld_insert_last(hd,3*sizeof(align_data),data160);
    ld_insert_last(hd,3*sizeof(align_data),data170);

    ld_delete_node(hd,dec_to_pointer(hd->memory,25)); //delete data50 
    ld_delete_node(hd,dec_to_pointer(hd->memory,35)); //delete data70
    ld_delete_node(hd,ld_last(hd)); //delete data170,last
    ld_delete_node(hd,ld_first(hd)); //delete data150,first
    ld_delete_node(hd,ld_first(hd)); //delete data140,first
    ld_delete_node(hd,ld_last(hd)); //delete data160,last
    





    print(hd);

    return 0;
}
