#ifndef _LIST_H

	#define _LIST_H

	#include "./tree.h"

	typedef struct node Node;
	typedef struct list LinkedList;


	LinkedList * initLinkedList();
	void addNewNodeInOrder(LinkedList *list, Node *node);
	Node * createNewNode(SubTree *sub_tree);
	Node * buildHuffmanTreeByList(LinkedList *list);
	SubTree * getSubTree(Node *node);
	void fillList(LinkedList *list, unsigned int *table, int size);
	void displayLinkedList(LinkedList *list);
	void initFrequencyTable(unsigned int *table, int size);
	void fillFrequencyTable(unsigned int *table, unsigned char *text);
	void printFrequencyTable(unsigned int *table, int size);
	char ** initEncodeDictionary(int row, int col);
	void fillEncodeDictionary(SubTree *tree, char **dict, char *path_code, int col);
	void displayDictionary(char **dict, int size);
	void freeDictionary(char **dict, int row);

#endif
