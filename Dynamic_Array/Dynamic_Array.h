#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

 typedef struct{
 void* data;
 size_t size_of_data; 
 size_t capacity;
 size_t length;
 int (*equals)(const void *,const void *); // Compare Element functions
 void (*print)(const void *,const int );
 int (*compare)(const void *,const void *);
} dynamic_array_t;


#define EXPAND 2
#define SHRINK_BOUND 0.5
#define DEFUALT 256
#define DEFAULT_SIZE 10

#define da_append(xs, value)                                      \
do {                                                              \
    dynamic_array_t *_da = (xs);                                  \
    if (_da->length >= _da->capacity) {                           \
        if (_da->capacity == 0) _da->capacity = DEFUALT;          \
        expand(_da);                                             \
		printf("Expanding...\n");								  \
    }                                                             \
    memcpy( (char*)_da->data +                                    \
            _da->length * _da->size_of_data,                      \
            &(value),                                             \
           _da->size_of_data );                                  \
    _da->length++;                                                \
} while(0)


#define da_remove(xs,value)                                 \
do{                                                         \
        void *element = (void *)&(value);                    \
        remove_element(xs,element);                          \
}while(0)                                                    \


#define LOADERR fprintf(stderr,"Failed Allocation")



dynamic_array_t* init_list(size_t, size_t, int(const void *, const void *),void(const void *,const int),
int(const void *,const void *));
void expand(dynamic_array_t *);
void destructor_arraylist(dynamic_array_t **);
void shrink(dynamic_array_t *);

void print_array(const dynamic_array_t *);
void remove_element(dynamic_array_t *,void *value);
int contains(dynamic_array_t *, const void *value);
void remove_all(dynamic_array_t *,const void *value);
int swap_elements(dynamic_array_t *,void *,void *);





//array general operations
void sort(dynamic_array_t *);


// int strategy
int int_cmp_elements(const void *, const void *);
int int_equal(const void *, const void * );
void print_int(const void*,int);
void print_int_default(const void *, const char*);

//string strategy
void print_string(const void *,int);
int string_equal(const void *,const void *);
void print_string_default(const void *, const char *);
int string_cmp_elements(const void *, const void *);
