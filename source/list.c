#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	SubTree *sub_tree = NULL;

	if (node == NULL)
		return NULL;

	list->head = node->next;
	node->next = NULL;
	list->size -= 1;

	sub_tree = node->tree;
	free(node);
	return sub_tree;
}

Node * buildHuffmanTreeByList(LinkedList *list)
{
	Node *new_node = NULL;
	SubTree *tree = NULL, *left_tree = NULL, *right_tree = NULL;

	while (list->size > 1)
	{
		left_tree = removeFirstNode(list);
		right_tree = removeFirstNode(list);

		tree = newSubTree(
			'#',
			getFrequency(left_tree) + getFrequency(right_tree),
			left_tree,
			right_tree
		);
		new_node = createNewNode(tree);
		addNewNodeInOrder(list, new_node);
	}

	return list->head;
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

void initFrequencyTable(unsigned int *table, int size)
{
	for (int i = 0; i < size; i++)
	{
		*(table+i) = 0;
	}
}

void fillFrequencyTable(unsigned int *table, unsigned char *text)
{
	int i = 0;

	while (*(text+i) != '\0')
	{
		*(table+text[i]) += 1;
		i++;
	}
}

void printFrequencyTable(unsigned int *table, int size)
{
	printf("\t --- Frequency Table --- \n");

	for (int i = 0; i < size; i++)
	{
		if (table[i] > 0)
			printf("%3d - |%c| freq: %u \n", i, i, table[i]);
	}
}

char ** initEncodeDictionary(int row, int col)
{
	char **dict = NULL;

	dict = malloc(row * sizeof(char *));

	for (int i = 0; i < row; i++)
		dict[i] = calloc(col, sizeof(char));

	return dict;
}

void fillEncodeDictionary(SubTree *tree, char **dict, char *path_code, int col)
{
	char left[col], rigth[col];

	if (isEmpty(getLeftTree(tree)) && isEmpty(getRightTree(tree)))
	{
		int i = (int)getCharacter(tree);
		strcpy(dict[i], path_code);
	}
	else
	{
		strcpy(left, path_code);
		strcpy(rigth, path_code);

		strcat(left, "0");
		strcat(rigth, "1");

		fillEncodeDictionary(getLeftTree(tree), dict, left, col);
		fillEncodeDictionary(getRightTree(tree), dict, rigth, col);
	}
}

void displayDictionary(char **dict, int size)
{
	printf("\t --- Encode Dictionary --- \n");

	for (int i = 0; i < size; i++)
	{
		if (strlen(dict[i]) > 0)
			printf("%3d - %c - %s\n", i, i, dict[i]);
	}
}

void freeDictionary(char **dict, int row, int col)
{
	for (int i = 0; i < row; i++)
		free(dict[i]);

	free(dict);
}
