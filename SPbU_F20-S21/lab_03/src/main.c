#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "mergesort.h"

int cmp_int(const void* a, const void* b) {
	char* x = *((char**) a);
	char* y = *((char**) b);

	return atoi(x) - atoi(y);
}

int cmp_char(const void* a, const void* b) {
	char* x = *((char**) a);
	char* y = *((char**) b);

	return *x - *y; // <=> x[0] - y[0]
}

int cmp_str(const void* a, const void* b) {
	char* x = *((char**) a);
	char* y = *((char**) b);

	return strcmp(x, y);
}

int main(int argc, char** argv) {
	if(argc == 2) return 0; //Do nothing when array is empty

	int (*cmp)(const void* a, const void* b);
	if(strcmp(argv[1], "int") == 0)
		cmp = *cmp_int;
	else if(strcmp(argv[1], "char") == 0)
		cmp = *cmp_char;
	else
		cmp = *cmp_str;

	if(mergesort((void*)(argv + 2), argc - 2, sizeof(char*), cmp) == -1) {
		printf("%s\n", "Error: memory allocation failed");
		return 1;
	}

	for(int i = 2; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");
	return 0;
}