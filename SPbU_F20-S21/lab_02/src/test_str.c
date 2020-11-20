#include "assert.h"
#include "str.h"
#include "stdio.h"
#include "string.h"

void test_strcpy() {
	char s1[] = {'t', 'e', 's', 't'};
	char* s2 = "";
	my_strcpy(s1, s2);
	assert(*s1 == '\0');

	char s3[] = {'b', 'r', 'a', 'v', 'i', 't'};
	char s4[] = {'c', 'o', 'o', 'l', '\0'};
	my_strcpy(s3, s4);
	assert(strcmp(s3, "cool") == 0);
}

void test_strcat() {
	char s1[] = {'t', 'e', 's', 't', '\0', 't', 'e', 's', 't'};
	char* s2 = "test";
	my_strcat(s1, s2);
	assert(strcmp(s1, "testtest") == 0);

	char s3[] = {'l', 'o', 'l', '\0'};
	char* s4 = "kek";
	my_strcat(s3, s4);
	assert(strcmp(s3, "lolkek") == 0);

	char s5[] = {'\0'};
	char* s6 = "nice";
	my_strcat(s5, s6);
	assert(strcmp(s5, "nice") == 0);
}

void test_strcmp() {
	char *s1 = "lol";
	char *s2 = "kek";
	assert(my_strcmp(s1, s2) == 1);
	assert(my_strcmp(s2, s1) == -1);

	char s3[] = {'t', 'e', 's', 't', '\0'};
	char* s4 = "test";
	assert(my_strcmp(s3, s4) == 0);
	assert(my_strcmp(s4, s3) == 0);

	char* s5 = "";
	char s6[] = {'a', '\0'};
	assert(my_strcmp(s5, s6) == -1);
	assert(my_strcmp(s6, s5) == 1);
}

void test_strlen() {
	char *s1 = "test string";
	assert(my_strlen(s1) == 11);

	char *s2 = "test";
	assert(my_strlen(s2) == 4);

	char *s3 = "";
	assert(my_strlen(s3) == 0);
}