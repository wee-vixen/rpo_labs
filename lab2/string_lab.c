#include <stdio.h>
#include <string.h>
/*заголовочный файл, в котором прописаны альтернативные 
 варианты написания логических операторов:*/
#include <iso646.h>
/*заголовочный файл, содержащий функции для классификации
отдельных символов*/
#include <ctype.h>
#include <stdlib.h>
#include "string_lab.h"
#define MAX(x, y) x > y ? x : y

char *_strremove(char *str, const char ch) { 
	if (str == NULL) {
		return NULL;
	}
	for (int i = 0; i < strlen(str); i++) {
		while (str[i] == ch) {
			memmove(&str[i], &str[i + 1], strlen(str));
		}
	}	
	return str;
}

int _strcountchar(const char *str, const char ch) {
	if (str == NULL or ch == '\0') {
		return -1;
	}
	int k = 0;
	char *string;
	string = strchr(str, ch);
	if (string == NULL) {
		return -1;
	}
	while (string not_eq NULL) {
		k++;
		string = strchr(string + 1, ch);
	}
	return k;
}

char *_strdelspaces(char *str) {
	if (str == NULL) {
		return NULL;
	}
	char space = ' ';
	int lenght = strlen(str);
	for (int i = 0; i < lenght; i++) {
		if (str[i] == space and str[i + 1] == space) {
			memmove(&str[i], &str[i + 1], lenght - i);
			lenght -= 1;
			i-=1;
		}
	}
	return str;
}

char *_strtolower(char *str) {
	if (str == NULL) {
		return NULL;
	}
	for (int i = 0; i < (strlen(str) + 1); i++) {
		int d = (int) str[i];
		if (d >= 65 and d <= 90) {
			str[i] = (char) (d + 32);
		}
	}
	return str;
}

char *_strtoupper(char *str) {
	if (str == NULL) {
		return NULL;
	}
	for (int i = 0; i < (strlen(str) + 1); i++) {
		int d = (int) str[i];
		if (d >= 97 and d <= 122) {
			str[i] = (char) (d - 32);
		}
	}
	return str;
}

int _strcmp(const char *str1, const char *str2) {
	if (str1 == NULL or str2 == NULL) {
		return 0;
	}
	int len, k;
	len = MAX(strlen(str1), strlen(str2));
	if ((strlen(str1) == strlen(str2)) or (strlen(str1) not_eq strlen(str2))) {
		for (int j = 0; j < len + 1; j++) {
			if ((int) str1[j] > (int) str2[j]) {
				return (int) str1[j] - (int) str2[j];
			}
			if ((int) str1[j] < (int) str2[j]) {
				return (int) str1[j] - (int) str2[j];
			}
		}
	}
	if (*str1 == *str2) {
		return 0;
	}			
}

char *_strreverse(const char *str1) {
	if (str1 == NULL) {
		return NULL;
	}
	int len = strlen(str1); 
	char *str = (char *) calloc((len + 1), sizeof(char));	
	strcpy(str, str1);
	for (int i = 0; i < (len / 2) ; i++) {
		char interim = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = interim;
	}
	str[len] = '\0';
	return str;
}		 
	
int _atoi(const char *str) {
	int num_str = 0;
	int sign_numb = 1;

	int n = 0;
	while (isblank(str[n])) {
		n++;
	}

	for (int i = n; i < strlen(str); i++) {
		if (str[i] == '-' or str[i] == '+') {
			if (str[i] == '-') {
				n++;
				sign_numb = -1;
			}
			if (str[i] == '+') {
				n++;
				sign_numb = 1;
			}
		}
	}
	for (n; n <strlen(str); n++) {
		if (((int) str[n] >= 48 and (int) str[n] <= 57)) {
			num_str = num_str * 10 + ((int) str[n] - 48);
			if (!isdigit(str[n + 1])) {
				return num_str * sign_numb;
			}
		}
	}
	num_str*=sign_numb;
	return num_str;
}

char *_strchr(char *str, int ch) {
	if (str == NULL) {
		return NULL;
	}
	int lenght = strlen(str);
	for (int i = 0; i < lenght; i++) {
		if (str[i] == ch) {
			return &str[i];
		}
	}
	return NULL;
}

char *_strstr(const char *str, const char *substr) {
	if (str == NULL) {
		return NULL;
	}
	
	int len_str = strlen(str);
	int len_substr = strlen(substr);
	int i, j;	
	for (i = 0; i < len_str; i++) {
		for (j = 0; j < len_substr; j++) 
			if (str[i + j] not_eq substr[j]) 
				break;
			if (j == len_substr) {
				return (char *) &str[i];
			}	
	}
	return NULL;
}
