#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include "projet2019.h"

int main()
{
    const size_t SZ = 3;
    head *hd = ld_create(10000);
    align_data data1[SZ], data10[SZ], data20[SZ], data30[SZ], data40[SZ], data50[SZ], data60[SZ];
    align_data data70[SZ], data80[SZ], data90[SZ], data100[SZ], data110[SZ], data120[SZ];
    align_data data130[SZ], data140[SZ], data150[SZ],data160[SZ] ,data170[SZ];

    create_data(SZ,1,data1);
    create_data(SZ,11,data10);
    create_data(SZ,21,data20);
    create_data(SZ,31,data30);
    create_data(SZ,41,data40);
    create_data(SZ,51,data50);
    create_data(SZ,61,data60);
    create_data(SZ,71,data70);
    create_data(SZ,81,data80);
    create_data(SZ,91,data90);
    create_data(SZ,101,data100);
    create_data(SZ,111,data110);
    create_data(SZ,121,data120);
    create_data(SZ,131,data130);
    create_data(SZ,141,data140);
    create_data(SZ,151,data150);
    create_data(SZ,161,data160);
    create_data(SZ,171,data170);


    ld_insert_first(hd,SZ*sizeof(align_data),data1);
    ld_insert_last(hd,SZ*sizeof(align_data),data10);
    ld_insert_first(hd,SZ*sizeof(align_data),data20);
    ld_insert_last(hd,SZ*sizeof(align_data),data30);
    ld_insert_first(hd,SZ*sizeof(align_data),data40);
    ld_insert_first(hd,SZ*sizeof(align_data),data50);
    ld_insert_first(hd,SZ*sizeof(align_data),data60);
    ld_insert_last(hd,SZ*sizeof(align_data),data70);
    ld_insert_last(hd,SZ*sizeof(align_data),data80);
    ld_insert_first(hd,SZ*sizeof(align_data),data90);
    ld_insert_last(hd,SZ*sizeof(align_data),data100);
    ld_insert_first(hd,SZ*sizeof(align_data),data110);
    ld_insert_last(hd,SZ*sizeof(align_data),data120);
    ld_insert_first(hd,SZ*sizeof(align_data),data130);
    ld_insert_first(hd,SZ*sizeof(align_data),data140);
    ld_insert_first(hd,SZ*sizeof(align_data),data150);
    ld_insert_last(hd,SZ*sizeof(align_data),data160);
    ld_insert_last(hd,SZ*sizeof(align_data),data170);

    ld_delete_node(hd,dec_to_pointer(hd->memory,25)); //delete data50 
    ld_delete_node(hd,dec_to_pointer(hd->memory,35)); //delete data70
    ld_delete_node(hd,ld_last(hd)); //delete data170,last
    ld_delete_node(hd,ld_first(hd)); //delete data150,first
    ld_delete_node(hd,ld_first(hd)); //delete data140,first
    ld_delete_node(hd,ld_last(hd)); //delete data160,last
    
    print_list(hd);

    ld_compactify(hd);

    print_list(hd);

    printf("p %ld \n", ((node*) get_node_at(hd,4))->data[0].a); //print data40
    
    ld_destroy(hd);

    return 0;
}
