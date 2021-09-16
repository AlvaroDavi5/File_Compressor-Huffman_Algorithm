#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/tree.h"


int getStringSize(char **dict, unsigned char *text)
{
	int i = 0, size = 0;

	while (text[i] != '\0')
	{
		size += strlen(dict[text[i]]);
		i++;
	}

	return size+1;
}

char * encode(char **dict, unsigned char *text)
{
	int i = 0, size = getStringSize(dict, text);

	char *code = calloc(size, sizeof(char));

	while (text[i] != '\0')
	{
		strcat(code, dict[text[i]]);
		i++;
	}

	return code;
}

char * displayEncode(unsigned char *code)
{
	printf("\t --- Encoded Data --- \n");
	printf("  %s\n", code);
}
