#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dictionary.h"
#include "../include/utils.h"


char **initEncodeDictionary(int row, int col)
{
	char **dict = NULL;
	dict = malloc(row * sizeof(char *));
	checkAllocation(dict, "create dictionary");

	for (int i = 0; i < row; i++) {
		dict[i] = calloc(col, sizeof(char));
		checkAllocation(dict[i], "create dict");
	}
	return dict;
}

void fillEncodeDictionary(SubTree *tree, char **dict, char *codePath, int col)
{
	char left[col], rigth[col];
	if (isEmpty(getLeftTree(tree)) && isEmpty(getRightTree(tree)))
	{
		unsigned char c = getCharacter(tree);
		strcpy(dict[c], codePath);
	}
	else
	{
		strcpy(left, codePath);
		strcpy(rigth, codePath);

		strcat(left, "0");
		strcat(rigth, "1");

		fillEncodeDictionary(getLeftTree(tree), dict, left, col);
		fillEncodeDictionary(getRightTree(tree), dict, rigth, col);
	}
}

void displayDictionary(char **dict, int size)
{
	printf("\t --- Encode Dictionary --- \n");

	for (int i = 0; i < size; i++)
	{
		if (strlen(dict[i]) > 0)
			printf("%3d - %c - %s\n", i, i, dict[i]);
	}
}

void freeDictionary(char **dict, int row)
{
	if (dict == NULL)
		return;

	for (int i = 0; i < row; i++)
		safeFree(dict[i]);

	safeFree(dict);
}
