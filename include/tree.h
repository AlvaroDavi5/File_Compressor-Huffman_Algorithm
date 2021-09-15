#ifndef _TREE_H

	#define _TREE_H

	typedef struct sub_tree SubTree;
	typedef SubTree* Tree;


	SubTree * newSubTree(unsigned char charac, unsigned int frequency, SubTree *left, SubTree *right);
	int itBelongs(SubTree *sub_tree, unsigned char charac);
	void displayPreOrder(SubTree *sub_tree);
	void freeSubTree(SubTree *sub_tree);
	char getCharacter(SubTree *sub_tree);
	unsigned int getFrequency(SubTree *sub_tree);
	int isEmpty(SubTree *sub_tree);

#endif
