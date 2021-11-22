#ifndef _UTILS_H

	#define _UTILS_H

	#include "./tree.h"

	char * encode(char **dict, unsigned char *text, int size);
	char * decode(SubTree *tree, unsigned char *code, int size);
	void safeFree(void *ptr);

#endif

