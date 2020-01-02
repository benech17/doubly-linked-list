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

void create_data(int size,int first,align_data* data){
    for(int i=0;i<size;i++){
        (data+i)->a=first++;
    }
}

int main()
{
    const size_t size = 3;
    head *hd = ld_create(10000);
    align_data data1[size], data10[size], data20[size], data30[size], data40[size], data50[size], data60[size];
    align_data data70[size], data80[size], data90[size], data100[size], data110[size], data120[size];
    align_data data130[size], data140[size], data150[size],data160[size] ,data170[size];

    create_data(size,1,data1);
    create_data(size,11,data10);
    create_data(size,21,data20);
    create_data(size,31,data30);
    create_data(size,41,data40);
    create_data(size,51,data50);
    create_data(size,61,data60);
    create_data(size,71,data70);
    create_data(size,81,data80);
    create_data(size,91,data90);
    create_data(size,101,data100);
    create_data(size,111,data110);
    create_data(size,121,data120);
    create_data(size,131,data130);
    create_data(size,141,data140);
    create_data(size,151,data150);
    create_data(size,161,data160);
    create_data(size,171,data170);


    ld_insert_first(hd,size*sizeof(align_data),data1);
    ld_insert_last(hd,size*sizeof(align_data),data10);
    ld_insert_first(hd,size*sizeof(align_data),data20);
    ld_insert_last(hd,size*sizeof(align_data),data30);
    ld_insert_first(hd,size*sizeof(align_data),data40);
    ld_insert_first(hd,size*sizeof(align_data),data50);
    ld_insert_first(hd,size*sizeof(align_data),data60);
    ld_insert_last(hd,size*sizeof(align_data),data70);
    ld_insert_last(hd,size*sizeof(align_data),data80);
    ld_insert_first(hd,size*sizeof(align_data),data90);
    ld_insert_last(hd,size*sizeof(align_data),data100);
    ld_insert_first(hd,size*sizeof(align_data),data110);
    ld_insert_last(hd,size*sizeof(align_data),data120);
    ld_insert_first(hd,size*sizeof(align_data),data130);
    ld_insert_first(hd,size*sizeof(align_data),data140);
    ld_insert_first(hd,size*sizeof(align_data),data150);
    ld_insert_last(hd,size*sizeof(align_data),data160);
    ld_insert_last(hd,size*sizeof(align_data),data170);

    ld_delete_node(hd,dec_to_pointer(hd->memory,25)); //delete data50 
    ld_delete_node(hd,dec_to_pointer(hd->memory,35)); //delete data70
    ld_delete_node(hd,ld_last(hd)); //delete data170,last
    ld_delete_node(hd,ld_first(hd)); //delete data150,first
    ld_delete_node(hd,ld_first(hd)); //delete data140,first
    ld_delete_node(hd,ld_last(hd)); //delete data160,last
    
    print(hd);

    ld_destroy(hd);

    return 0;
}
