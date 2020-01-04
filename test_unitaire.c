#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "projet2019.h"

int main(){
    head* hd= ld_create(1000);
    align_data data1[5];
    data1->a=11;
    (data1+1)->a=12;
    (data1+2)->a=13;
    (data1+3)->a=14;
    (data1+4)->a=15;

    align_data data2[3];
    data2->a=21;
    (data2+1)->a=22;
    (data2+2)->a=33;

    align_data data3[6];
    data3->a=31;
    (data3+1)->a=32;
    (data3+2)->a=33;
    (data3+3)->a=34;
    (data3+4)->a=35;
    (data3+5)->a=36;

    align_data data4[4];
    data4->a=41;
    (data4+1)->a=42;
    (data4+2)->a=43;
    (data4+3)->a=44;
    node* n = (node*) dec_to_pointer(hd->memory, 0);

    ld_insert_first(hd,sizeof(data1),data1);
    ld_insert_first(hd,sizeof(data2),data2);
    ld_insert_first(hd,sizeof(data3),data3);
    ld_insert_before(hd,n,sizeof(data4),data4);


    print_list(hd);
    
    ld_delete_node(hd,dec_to_pointer(hd->memory,20));

    print_list(hd);

    ld_add_memory(hd, 2000);

    print_list(hd);

    ld_destroy(hd);

    return 0;
}