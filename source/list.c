#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/tree.h"
#include "../include/utils.h"


struct node
{
	SubTree *tree;
	Node *next;
};

struct list
{
	int size;
	Node *head;
};


LinkedList * initLinkedList()
{
	LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
	checkAllocation(list, "create list");

	list->size = 0;
	list->head = NULL;

	return list;
}

void addNewNodeInOrder(LinkedList *list, Node *node)
{
	if (list->head == NULL)
	{
		node->next = NULL;
		list->head = node;
	}
	else if (getFrequency(node->tree) < getFrequency((list->head)->tree))
	{
		node->next = list->head;
		list->head = node;
	}
	else
	{
		Node *current = list->head;
		while (current->next && (getFrequency((current->next)->tree) <= getFrequency(node->tree)))
		{
			current = current->next;
		}
		node->next = current->next;
		current->next = node;
	}
	list->size += 1;
}

Node * createNewNode(SubTree *subTree)
{
	Node *node = (Node *) malloc(sizeof(Node));
	checkAllocation(node, "create new node");

	node->tree = subTree;
	node->next = NULL;

	return node;
}

SubTree * removeFirstNode(LinkedList *list)
{
	Node *node = list->head;
	SubTree *subTree = NULL;

	if (node == NULL)
		return NULL;

	list->head = node->next;
	node->next = NULL;
	list->size -= 1;

	subTree = node->tree;
	safeFree(node);
	return subTree;
}

Node * buildHuffmanTreeByList(LinkedList *list)
{
	Node *newNode = NULL;
	SubTree *tree = NULL, *leftTree = NULL, *rightTree = NULL;

	while (list->size > 1)
	{
		leftTree = removeFirstNode(list);
		rightTree = removeFirstNode(list);

		tree = newSubTree(
			'#',
			getFrequency(leftTree) + getFrequency(rightTree),
			leftTree,
			rightTree
		);
		newNode = createNewNode(tree);
		addNewNodeInOrder(list, newNode);
	}

	return list->head;
}

void fillList(LinkedList *list, unsigned int *table, int size)
{
	Node *newNode = NULL;

	for (int i = 0; i < size; i++)
	{
		if (table[i] > 0)
		{
			newNode = createNewNode(NULL);
			if (newNode)
			{
				newNode->tree = newSubTree((unsigned char)i, table[i], NULL, NULL);
				addNewNodeInOrder(list, newNode);
			}
			else
			{
				printf("Error to allocate memory");
				break;
			}
		}
	}
}

void freeLinkedList(LinkedList *list)
{
	if (list)
	{
		Node *current = list->head;

		while (current)
		{
			Node *aux = current;
			current = current->next;
			safeFree(aux);
		}
		safeFree(list);
	}
}

SubTree * getSubTree(Node *node)
{
	return (node->tree);
}

void displayLinkedList(LinkedList *list)
{
	Node *current = list->head;

	printf("\t --- Node List: size %u --- \n", list->size);
	while (current != NULL)
	{
		printf("%c:%u, ", getCharacter(current->tree), getFrequency(current->tree));
		current = current->next;
	}
	printf("\n");
}
