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

char * encode(char **dict, unsigned char *text, int size)
{
	int i = 0;

	char *code = calloc(size, sizeof(char));

	while (text[i] != '\0')
	{
		strcat(code, dict[text[i]]);
		i++;
	}

	return code;
}

char * decode(SubTree *tree, unsigned char *code, int size)
{
	int i = 0;
	SubTree *current = tree;
	char buffer[2] = "";
	char *text = calloc(size, sizeof(char));

	while (code[i] != '\0')
	{
		if (code[i] == '0')
			current = getLeftTree(current);
		else
			current = getRightTree(current);

		if (getLeftTree(current) == NULL && getRightTree(current) == NULL)
		{
			buffer[0] = getCharacter(current);
			buffer[1] = '\0';
			strcat(text, buffer);
			current = tree;
		}

		i++;
	}

	return text;
}

void safeFree(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;

	return;
}
