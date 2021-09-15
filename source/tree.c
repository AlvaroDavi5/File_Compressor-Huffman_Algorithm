#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"


struct sub_tree
{
	unsigned char character;
	unsigned int frequency;
	struct sub_tree *left;
	struct sub_tree *right;
};


SubTree * newSubTree(unsigned char charac, unsigned int frequency, SubTree *left, SubTree *right)
{
	SubTree *sub_tree = (SubTree *) malloc(sizeof(SubTree));

	sub_tree->character = charac;
	sub_tree->frequency = frequency;
	sub_tree->left = left;
	sub_tree->right = right;

	return sub_tree;
}

int itBelongs(SubTree *sub_tree, unsigned char charac)
{
	if (isEmpty(sub_tree))
		return 0;
	else
		return (sub_tree->character == charac) ||
		itBelongs(sub_tree->left, charac) ||
		itBelongs(sub_tree->right, charac);	
}

void displayPreOrder(SubTree *sub_tree)
{
	printf("<");
	if(isEmpty(sub_tree))
	{
		printf("");
	}
	else
	{
		if (sub_tree->character == '#')
			printf("");
		else
			printf("%c", sub_tree->character);
		displayPreOrder(sub_tree->left);
		displayPreOrder(sub_tree->right);
	}
	printf(">");
}

void freeSubTree(SubTree *sub_tree)
{
	if(isEmpty(sub_tree))
		return;
	else
	{
		freeSubTree(sub_tree->left);
		freeSubTree(sub_tree->right);

		free(sub_tree);
		sub_tree = NULL;
	}
}

char getCharacter(SubTree *sub_tree)
{
	return sub_tree->character;
}

unsigned int getFrequency(SubTree *sub_tree)
{
	return sub_tree->frequency;
}

int isEmpty(SubTree *sub_tree)
{
	if (sub_tree == NULL)
		return 1;
	else
		return 0;
}
