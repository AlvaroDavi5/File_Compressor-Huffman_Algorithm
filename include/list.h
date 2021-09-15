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

#endif
