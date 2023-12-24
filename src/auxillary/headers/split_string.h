#ifndef SPLIT_STRING_H
#define SPLIT_STRING_H

#include <stdlib.h>

inline unsigned int strlento(char const * string, char const endsymb) {
	unsigned int res = 0;
	char const * symb = string;
	while (*symb != endsymb && *symb != '\0') {
		++symb;
		++res;
	}
	return res;
}

inline unsigned int strlento_screened(char const * string, char const endsymb, char const screen_symbol) {
	unsigned int res = 0;
	char const * symb = string;
	char screened = 0;
	while (*symb != '\0' && (screened || *symb != endsymb)) {
		if (*symb == screen_symbol)
			screened = !screened;
		++symb;
		++res;
	}
	return res;
}

inline unsigned int count_char(char const * string, char search) {
	unsigned int res = 0;
	for (char const * symb = string; *symb != '\0'; ++symb)
		if (*symb == search)
			++res;
	return res;
}

inline unsigned int count_char_screened(char const * string, char search, char const screen_symbol) {
	unsigned int res = 0;
	char screened = 0;
	for (char const * symb = string; *symb != '\0'; ++symb) {
		if (*symb == screen_symbol)
			screened = !screened;
		else if (!screened && *symb == search)
			++res;
	}
	return res;
}

// for resv nested freeing required
inline void split_string(char const * string, char const delimiter, unsigned int * resc, char *** resv) {
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

inline void split_string_screened(char const * string, char const delimiter, char const screen_symbol, unsigned int * resc, char *** resv) {
	if (string[0] == '\0') {
		*resc = 0;
		*resv = NULL;
		return;
	}

	*resc = count_char_screened(string, delimiter, screen_symbol) + 1;
	char const * symb = string;
	*resv = (char **)calloc(*resc, sizeof(char *));
	unsigned int resv_count = 0;
	unsigned int symb_count = 0;
	char screened = 0;

	(*resv)[resv_count] = (char *)calloc(strlento_screened(symb, delimiter, screen_symbol) + 1, sizeof(char));
	while (*symb != '\0') {
		if (*symb == screen_symbol)
			screened = !screened;
		if (!screened && *symb == delimiter) {
			symb_count = 0;
			(*resv)[++resv_count] = (char *)calloc(strlento_screened(symb + 1, delimiter, screen_symbol) + 1, sizeof(char));
		} else {
			(*resv)[resv_count][symb_count++] = *symb;
		}
		++symb;
	}
}

inline unsigned int count_char_multiscreened(char const * string, char search, char const * screen_symbols) {
	unsigned int res = 0;
	char screened = 0;
	char last_screen_symb = '\0';
	for (char const * symb = string; *symb != '\0'; ++symb) {
		if (screened)
			screened = last_screen_symb != *symb;
		else {
			if (count_char(screen_symbols, *symb)) {
				screened = 1;
				last_screen_symb = *symb;
			}
			else
				res += *symb == search;
		}
	}
	return res;
}

inline unsigned int strlento_multiscreened(char const * string, char const endsymb, char const * screen_symbols) {
	unsigned int res = 0;
	char screened = 0;
	char last_screen_symb = '\0';
	for (char const * symb = string; *symb != '\0' && (screened || *symb != endsymb); ++symb) {
		if (screened)
			screened = last_screen_symb != *symb;
		else {
			if (count_char(screen_symbols, *symb)) {
				screened = 1;
				last_screen_symb = *symb;
			}
		}
		++res;
	}

	return res;
}

inline void split_string_multiscreened(char const * string, char const delimiter, char const * screen_symbols, unsigned int * resc, char *** resv) {
	if (string[0] == '\0') {
		*resc = 0;
		*resv = NULL;
		return;
	}

	*resc = count_char_multiscreened(string, delimiter, screen_symbols) + 1;
	*resv = (char **)calloc(*resc, sizeof(char *));

	unsigned int resv_count = 0;
	unsigned int symb_count = 0;
	char screened = 0;
	char last_screen_symb = '\0';
	char const * symb = string;

	(*resv)[resv_count] = (char *)calloc(strlento_multiscreened(symb, delimiter, screen_symbols) + 1, sizeof(char));
	while (*symb != '\0') {
		if (screened)
			screened = *symb != last_screen_symb;
		else {
			if (count_char(screen_symbols, *symb)) {
				screened = 1;
				last_screen_symb = *symb;
			}
			else if (*symb == delimiter) {
				symb_count = 0;
				(*resv)[++resv_count] = (char *)calloc(strlento_multiscreened(symb + 1, delimiter, screen_symbols) + 1, sizeof(char));
			}
		}

		if (screened || *symb != delimiter)
			(*resv)[resv_count][symb_count++] = *symb;
		++symb;
	}
}

#endif
