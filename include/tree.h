#ifndef _TREE_H

	#define _TREE_H

	typedef struct sub_tree SubTree;
	typedef SubTree* Tree;


	SubTree * newSubTree(unsigned char charac, unsigned int frequency, SubTree *left, SubTree *right);
	int height(SubTree *sub_tree);
	void displayPreOrder(SubTree *sub_tree);
	void freeSubTree(SubTree *sub_tree);
	char getCharacter(SubTree *sub_tree);
	unsigned int getFrequency(SubTree *sub_tree);
	SubTree * getLeftTree(SubTree *sub_tree);
	SubTree * getRightTree(SubTree *sub_tree);
	int isEmpty(SubTree *sub_tree);

#endif
