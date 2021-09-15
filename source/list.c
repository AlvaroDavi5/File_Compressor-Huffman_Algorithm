#include <stdio.h>
#include <stdlib.h>


struct node
{
	int index;
	int data;
	struct node *next; // only next Node pointer...
};

struct list
{
	int size;
	Node *head;
	Node *current; // [...] makes one-way List
	Node *tail;
};


LinkedList * initLinkedList(LinkedList *list)
{
	list = (LinkedList *) malloc(sizeof(LinkedList));

	list->size = 0;
	list->head = NULL;
	list->current = NULL;
	list->tail = NULL;

	return list;
}

void addNewHead(LinkedList *list, int value)
{
	Node *node = (Node *) malloc(sizeof(Node));
	node->data = value;

	if (list->head == NULL)
	{
		list->tail = node;
		node->next = NULL;
	}
	else
	{
		node->next = list->head;
	}

	list->head = node;
	list->size += 1;

	list->current = list->head;
	for (int i = 0; i < list->size; i++)
	{
		(list->current)->index = i;
		list->current = (list->current)->next;
	}
}

void addNewTail(LinkedList *list, int value)
{
	Node *node = (Node *) malloc(sizeof(Node));

	node->data = value;
	node->next = NULL;

	if (list->head == NULL)
	{
		list->head = node;
	}
	else
	{
		list->tail->next = node;
	}

	node->index = list->size;
	list->tail = node;
	list->size += 1;
}

Node * getNode(LinkedList *list, fptrCompare compareFunction, int position)
{
	list->current = list->head;

	while (list->current != NULL)
	{
		if (compareFunction((list->current)->index, position) == 0)
		{
			return list->current;
		}

		list->current = (list->current)->next;
	}

	return NULL;
}

void insertNextNode(LinkedList *list, Node *node)
{
	Node *newNode = (Node *) malloc(sizeof(Node));

	newNode->data = 0;
	newNode->next = node->next;

	if (list->head == NULL)
	{
		list->head = newNode;
	}
	else
	{
		node->next = newNode;
	}

	if (newNode->next != NULL)
	{
		newNode->index = newNode->next->index;
		list->current = newNode->next;
		for (int i = newNode->index; i < list->size; i++)
		{
			(list->current)->index = i+1;
			list->current = (list->current)->next;

			if (list->current == NULL)
				break;
		}
	}
	else
	{
		newNode->index = list->size;
	}
	list->size += 1;
}

void insertData(Node *node, int value)
{
	node->data = value;
}

void deleteNode(LinkedList *list, Node *node)
{
	list->current = list->head;

	if (node == list->head)
	{
		if (list->head->next == NULL)
		{
			list->head = list->tail;
		}
		else
		{
			list->head = list->head->next;
		}
	}
	else
	{
		while (list->current != NULL && (list->current)->next != node)
		{
			list->current = (list->current)->next;
		}
		if (list->current != NULL && (list->current)->next == node)
		{
			(list->current)->next = node->next;
			((list->current)->next)->index = node->index;
		}
	}

	free(node);
	list->size -= 1;

	Node *indexedNode = list->head;
	for (int i = 0; i < list->size; i++)
	{
		if (indexedNode != NULL)
		{
			indexedNode->index = i;
			indexedNode = indexedNode->next;
		}
	}
}


void destroyLinkedList(LinkedList *list)
{
	list->current = list->head;
	Node *next = NULL;

	while (list->current != NULL)
	{
		next = (list->current)->next;

		deleteNode(list, list->current);
		list->current = next;
	}

	free(list);
}

void displayLinkedList(LinkedList *list)
{
	list->current = list->head;

	while (list->current != NULL)
	{
		printf("%d:%d - ", (list->current)->index, (list->current)->data);
		list->current = (list->current)->next;
	}
}

int compareData(int d1, int d2)
{
	if (d1 == d2)
	{
		return 0;
	}
	else if (d2 > d1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
