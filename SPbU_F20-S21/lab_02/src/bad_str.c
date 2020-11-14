/*Должна существовать реализация задания, 
при которой ваши автоматические тесты не проходят или приводят к UB.*/

char* my_strcpy(char* s1, char* s2){
	char* res = s1;
	while(*s1++ = *s2++){}
	return res;
}

char* my_strcat(char* s1, char* s2){
	char* res = s1;
	while(*s1++){}
	while(*s1++ = *s2++){}
	return res;
}

int my_strcmp(char* s1, char* s2){
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

int my_strlen(char* s){
	int res = 0;
	while(*s++)
		res++;
	return res;	
}