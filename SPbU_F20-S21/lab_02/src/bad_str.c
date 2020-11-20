char* my_strcpy(char* restrict s1, const char* restrict s2) {
	char* res = s1;
	while(*s1++ = *s2++){}
	return res;
}

char* my_strcat(char* restrict s1, const char* restrict s2) {
	char* res = s1;
	while(*s1++){}
	while(*s1++ = *s2++){}
	return res;
}

int my_strcmp(const char* s1, const char* s2) {
	while(1){
		if(*s1 > *s2)
			return 1;
		if(*s1 < *s2)
			return -1;
		s1++;
		s2++;
	}
	return 0;
}

int my_strlen(const char* s) {
	int res = 0;
	while(*s++)
		res++;
	return res;	
}