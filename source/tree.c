#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"
#include "../include/utils.h"


struct sub_tree
{
	unsigned char character;
	unsigned int frequency;
	struct sub_tree *left;
	struct sub_tree *right;
};

SubTree * newSubTree(unsigned char charac, unsigned int frequency, SubTree *left, SubTree *right)
{
	SubTree *subTree = (SubTree *) malloc(sizeof(SubTree));
	checkAllocation(subTree, "create tree");

	subTree->character = charac;
	subTree->frequency = frequency;
	subTree->left = left;
	subTree->right = right;

	return subTree;
}

int height(SubTree *subTree)
{
	int leftHeight, rightHeight;

	if (isEmpty(subTree))
		return -1;
	else
	{
		leftHeight = height(subTree->left) + 1;
		rightHeight = height(subTree->right) + 1;

		if (leftHeight > rightHeight)
			return leftHeight;
		else
			return rightHeight;
	}
}

void displayPreOrder(SubTree *subTree)
{
	printf("<");
	if (isEmpty(subTree))
	{
		printf("·");
	}
	else
	{
		if (subTree->character == '#')
			printf("_");
		else
			printf("%c", subTree->character);
		displayPreOrder(subTree->left);
		displayPreOrder(subTree->right);
	}
	printf(">");
}

void freeSubTree(SubTree *subTree)
{
	if (isEmpty(subTree))
		return;
	else
	{
		freeSubTree(subTree->left);
		freeSubTree(subTree->right);

		safeFree(subTree);
		subTree = NULL;
	}
}

unsigned char getCharacter(SubTree *subTree)
{
	return subTree->character;
}

unsigned int getFrequency(SubTree *subTree)
{
	return subTree->frequency;
}

SubTree * getLeftTree(SubTree *subTree)
{
	return subTree->left;
}
SubTree * getRightTree(SubTree *subTree)
{
	return subTree->right;
}

int isEmpty(SubTree *subTree)
{
	if (subTree == NULL)
		return 1;
	else
		return 0;
}
