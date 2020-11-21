#include "stdlib.h"
#include "stdio.h"

char* get(void* a, int i, size_t element_size) {
	return (((char*) a) + i * element_size);
}

void copy(void* a, size_t i, void* b, size_t j, size_t element_size) {
	for(int k = 0; k < element_size; k++) {
		get(a, i, element_size)[k] = get(b, j, element_size)[k];
	}
}

int merge(void *array, size_t elements_left, size_t elements_right, size_t element_size, int (*comparator)(const void*, const void*)) {
	void *result = malloc((elements_left + elements_right) * element_size);
	if(result == NULL) 
		return -1;
	
	size_t left = 0, right = 0;
	while(left < elements_left || right < elements_right){
		if(left == elements_left) { 
			copy(result, left + right, array, elements_left + right, element_size);
			right++;
		} else if(right == elements_right) { 
			copy(result, left + right, array, left, element_size);
			left++; 
		} else if((*comparator)(get(array, left, element_size), get(array,elements_left + right, element_size)) <= 0) {
			copy(result, left + right, array, left, element_size);
			left++;
		} else {
			copy(result, left + right, array, elements_left + right, element_size);
			right++;
		}
	}

	for(size_t i = 0; i < elements_left + elements_right; i++)
		copy(array, i, result, i, element_size);

	free(result);
	return 0;
}

int min(size_t a, size_t b) {
	if(a <= b)
		return a;
	return b;
}

int mergesort(void* array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
	for(size_t i = 1; i <= elements; i *= 2) {
		for(size_t j = 0; j <= (elements - i); j += 2 * i) {
			if(merge(array + j * element_size, i, min(i, elements - j - i), element_size, comparator) == -1)
				return -1;
		}
	}
	return 0;
}