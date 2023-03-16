#ifndef _DICTIONARY_H

	#define _DICTIONARY_H

	#include "./tree.h"

	char ** initEncodeDictionary(int row, int col);
	void fillEncodeDictionary(SubTree *tree, char **dict, char *path_code, int col);
	void displayDictionary(char **dict, int size);
	void freeDictionary(char **dict, int row);

#endif
