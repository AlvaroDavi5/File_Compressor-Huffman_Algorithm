#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/tree.h"


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

	list->size = 0;
	list->head = NULL;

	return list;
}

void addNewNodeInOrder(LinkedList *list, Node *node)
{
	Node *aux = NULL;

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
		aux = list->head;
		while (aux->next && getFrequency((aux->next)->tree) <= getFrequency(node->tree))
		{
			aux = aux->next;
		}
		node->next = aux->next;
		aux->next = node;
	}
	list->size += 1;
}

Node * createNewNode(SubTree *sub_tree)
{
	Node *node = (Node *) malloc(sizeof(Node));

	node->tree = sub_tree;
	node->next = NULL;

	return node;
}

SubTree * removeFirstNode(LinkedList *list)
{
	Node *node = list->head;

	if (node == NULL)
		return NULL;

	list->head = node->next;
	node->next = NULL;
	list->size -= 1;

	free(node);
	return node->tree;
}

void fillList(LinkedList *list, unsigned int *table, int size)
{
	Node *new_node = NULL;

	for (int i = 0; i < size; i++)
	{
		if (table[i] > 0)
		{
			new_node = createNewNode(NULL);
			if (new_node)
			{
				new_node->tree = newSubTree(i, table[i], NULL, NULL);
				addNewNodeInOrder(list, new_node);
			}
			else
			{
				printf("Error to allocate memory");
				break;
			}
		}
	}
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
