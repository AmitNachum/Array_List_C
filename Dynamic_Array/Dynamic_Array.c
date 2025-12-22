#include "Dynamic_Array.h"



/*----------------------General Operations With the Array list----------------------*/
dynamic_array_t* init_list(size_t size, size_t cap,int equal(const void *, const void *),
void print(const void *,const int),int cmp(const void *, const void *)){
	 if(cap == 0) cap = DEFUALT;
		dynamic_array_t *ret = malloc(sizeof(dynamic_array_t));

		if(!ret){
			LOADERR;
			return NULL;
		}

	ret->data = malloc(size * cap);

	if(!(ret->data)){
		LOADERR;
		return NULL;
	}

	ret->capacity = cap;
	ret->length = 0;
	ret->size_of_data = size;
	ret->equals = equal;
	ret->print = print;
	ret->compare = cmp;
	return ret;
	
}

void shrink(dynamic_array_t * _da){
	if(_da->capacity <= 1) return;
	size_t bytes_to_realloc = (_da)->capacity / 2;

	if(bytes_to_realloc < _da->length) return;
	void *new_data = realloc(_da->data,(_da)->size_of_data * bytes_to_realloc);
	if(!new_data){
		fprintf(stderr,"Reallocation faild for member [DATA]");
		return;
	}

	(_da)->capacity = bytes_to_realloc;
	(_da)->data = new_data;
}


void expand(dynamic_array_t *da){
	
	size_t new_capacity = (da)->capacity == 0 ? (DEFUALT) :(EXPAND * (da)->capacity);
	if(new_capacity < da->length + 1) return;
	size_t size = (da)->size_of_data;
	void *new_data = realloc((da)->data,size * new_capacity);
	

	if(!new_data){
		fprintf(stderr,"Reallocation faild for member [DATA]");
		return;
	}

	(da)->capacity = new_capacity;
	(da)->data = new_data;

	
}



void remove_element(dynamic_array_t *_da, void *value){
	
	if(_da->capacity < 1) return;
	
	int removed = 0;                                             
    for(size_t i = 0; i < _da->length; ++i){                             
        const void *element = (char*)(_da->data) + i * _da->size_of_data;

        if(_da->equals(value,element)){                                   
            size_t target_index = i;

            while(target_index < _da->length - 1){                       
                char *ith_element = (char*)_da->data + target_index * _da->size_of_data; 
                char *ith_plus_one = (char*)_da->data + (target_index + 1) * _da->size_of_data;
                memcpy(ith_element,ith_plus_one, _da->size_of_data);    
                target_index++;                                         
            }                                                           
            _da->length--;
			removed = 1;                                             
            break;                                                       
            }                                                            
    }
	if(!removed){return;}

	float shrink_relation = (float)_da->length / (float)_da->capacity; 
	if(shrink_relation < SHRINK_BOUND) shrink(_da);                                                                          
}

void print_array(const dynamic_array_t *da){
	size_t len = da->length;
	printf("{ ");
	int yes = 1;
	int no = 0;

	for(size_t i = 0; i < len ; ++i){
		void * element = (char *)da->data + i * da->size_of_data;
		if(i != len - 1){
			da->print(element,yes);
		}else{
			da->print(element,no);
		}
	}
	printf("}\n");

}





int contains(dynamic_array_t *da, const void *value){
	for(size_t i = 0; i < da->length; ++i){
		const void *elem = (const char *)da->data + i * da->size_of_data;
		if(da->equals(elem,value) == 1){
			return i;
		}
	}
	return 0;
}

void remove_all(dynamic_array_t *da,const void *value){

	for(size_t i = 0; i < da->length;){
		 void *elem = (char *)da->data + i * da->size_of_data;
		if(da->equals(elem,value) == 1){
			size_t last_index = da->length - 1;
			void * last_element = (char *)da->data + last_index * da->size_of_data;
			swap_elements(da,elem,last_element);
			da->length--; 
		} else{++i;}
	}
}


int swap_elements(dynamic_array_t *da,void *elem1, void *elem2){
	if(da->size_of_data > DEFAULT_SIZE){
		void *temp = malloc(da->size_of_data); // How can I avoid Malloc
		if(temp == NULL){
			return -1;	
		}

		memcpy(temp,elem1,da->size_of_data);
		memcpy(elem1,elem2,da->size_of_data);
		memcpy(elem2,temp,da->size_of_data);

		free(temp);
		return 0;
	} else{
		size_t size_of_buf = da->size_of_data;
		char buffer[size_of_buf];

		memcpy(buffer,elem1,size_of_buf);
		memcpy(elem1,elem2,size_of_buf);
		memcpy(elem2,buffer,size_of_buf);
	}
	return 0;
}

void sort(dynamic_array_t *da){
	qsort(da->data,da->length,da->size_of_data,da->compare);
}



void destructor_arraylist(dynamic_array_t **da){
	free((*da)->data);
	free((*da));
    *da = NULL;
	printf("Destructor Invoked'Array List destroyed\n");
}

/*----------------------General Operations With the Array list----------------------*/

/*----------------------Strings Operations With the Array list----------------------*/

void print_string(const void *p,int def){
	if(def == 1){
		print_string_default(p,", ");
	} else{
		print_string_default(p," ");
	}
}



int string_equal(const void *elem1, const void *elem2){
	const char *str1 = (char *)(elem1);
	const char *str2 = (char *)(elem2);	
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);

	if(len1 != len2){
		return 0;
	}

	size_t i = 0;
	while(i < len1){
		int strings_are_equal = str1[i] ==  str2[i];
		if(!strings_are_equal) return 0;
		++i;
	}

	return 1;
}

void print_string_default(const void *arg, const char *comma)
{
	printf("%s%s",((const char *)(arg)),comma);
}

int string_cmp_elements(const void *arg1, const void *arg2)
{
    size_t length_str1 = strlen((const char *)arg1);
	size_t length_str2 = strlen((const char *)arg2);

	if(length_str1 > length_str2){
		return 1;
	} else if( length_str1 < length_str2){
		return -1;
	} else return 0;
}


/*----------------------Strings Operations With the Array list----------------------*/


/*----------------------Integers Operations With the Array list----------------------*/


int int_cmp_elements(const void *num1, const void *num2)
{
	const int *elem1 = (const int *)num1;
	const int *elem2 = (const int *)num2;

	if(*elem1 > *elem2){
		return 1;
	} else if(*elem2 > *elem1){
		return -1;
	} else return 0;
}


int int_equal(const void *elem1, const void *elem2 ){
	return *(const int *)(elem1) == *(const int *)(elem2);
}





void print_int(const void *p, int def) {
	if(def == 1){
    	print_int_default(p,", ");
	}
	else{
		print_int_default(p," ");
	}
}


void print_int_default(const void *element, const char* ch){
	printf("%d%s",*(int*)(element),ch);
}


/*----------------------Integers Operations With the Array list----------------------*/