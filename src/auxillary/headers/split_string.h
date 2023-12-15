#include <stdlib.h>

unsigned int strlento(char const * string, char const endsymb) {
	unsigned int res = 0;
	char const * symb = string;
	while (*symb != endsymb && *symb != '\0') {
		++symb;
		++res;
	}
	return res;
}

unsigned int count_char(char const * string, char search) {
	unsigned int res = 0;
	for (char const * symb = string; *symb != '\0'; ++symb)
		if (*symb == search)
			++res;
	return res;
}

// for resv nested freeing required
void split_string(char const * string, char const delimiter, unsigned int * resc, char *** resv) {
	if (string[0] == '\0') {
		*resc = 0;
		*resv = NULL;
		return;
	}

	*resc = count_char(string, delimiter) + 1;
	char const * symb = string;
	*resv = (char **)calloc(*resc, sizeof(char *));
	unsigned int resv_count = 0;
	unsigned int symb_count = 0;

	(*resv)[resv_count] = (char *)calloc(strlento(symb, delimiter) + 1, sizeof(char));
	while (*symb != '\0') {
		if (*symb == delimiter) {
			symb_count = 0;
			(*resv)[++resv_count] = (char *)calloc(strlento(symb + 1, delimiter) + 1, sizeof(char));
		} else {
			(*resv)[resv_count][symb_count++] = *symb;
		}
		++symb;
	}
}
