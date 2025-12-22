#include "Dynamic_Array.h"


int main(void){ 
    size_t size = sizeof(int); 
    dynamic_array_t *da = init_list(size,DEFAULT_SIZE,int_equal,print_int,int_cmp_elements); 
    for(size_t i = 0; i <= 15; ++i){
        da_append(da,i);
    }
    printf("\nArray content after adding Elements\n");
    print_array(da);
    printf("\n");

    printf("Array after removing elements\n");
    int val = 15;
    da_remove(da,val);

    print_array(da);
    printf("\n");

    destructor_arraylist(&da);

    return 0;

}