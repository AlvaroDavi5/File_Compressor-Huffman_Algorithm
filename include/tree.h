#ifndef _TREE_H

	#define _TREE_H

	typedef struct node Node;
	typedef Node* Tree;


	Node * newNode(char *name, Node *left, Node *right);
	int itBelongs(Node *node, char *name);
	int leafsCount(Node *node);
	int occurrencesCount(Node *node, char *name);
	int height(Node *node);
	void displayPreOrder(Node *node); // starts at the root and goes first to the left branch and then to the right branch
	void displayInOrder(Node *node); // starts on the left branch, goes through the root and goes to the right branch
	void displayPostOrder(Node *node); // starts on the left branch and goes first to the right branch and then to the root
	void FreeNode(Node *node);
	int isEmpty(Node *node);

#endif
