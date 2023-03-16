#ifndef _TREE_H

	#define _TREE_H

	typedef struct sub_tree SubTree;


	SubTree * newSubTree(unsigned char charac, unsigned int frequency, SubTree *left, SubTree *right);
	int height(SubTree *subTree);
	void displayPreOrder(SubTree *subTree);
	void freeSubTree(SubTree *subTree);
	unsigned char getCharacter(SubTree *subTree);
	unsigned int getFrequency(SubTree *subTree);
	SubTree * getLeftTree(SubTree *subTree);
	SubTree * getRightTree(SubTree *subTree);
	int isEmpty(SubTree *subTree);

#endif
