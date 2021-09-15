#ifndef _LIST_H

	#define _LIST_H

	typedef int (* fptrCompare)(int, int);
	typedef struct node Node;
	typedef struct list LinkedList;


	LinkedList * initLinkedList(LinkedList *list);
	void addNewHead(LinkedList *list, int value);
	void addNewTail(LinkedList *list, int value);
	Node * getNode(LinkedList *list, fptrCompare compareFunction, int position);
	void insertNextNode(LinkedList *list, Node *node);
	void insertData(Node *node, int value);
	void deleteNode(LinkedList *list, Node *node);
	void destroyLinkedList(LinkedList *list);
	void displayLinkedList(LinkedList *list);
	int compareData(int d1, int d2);

#endif
