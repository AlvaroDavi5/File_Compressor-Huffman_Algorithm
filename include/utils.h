#ifndef _UTILS_H

	#define _UTILS_H

	#include "./tree.h"

	char * encode(char **dict, unsigned char *text);
	char * decode(SubTree *tree, unsigned char *code);

#endif

