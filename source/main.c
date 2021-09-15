#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/list.h"
#include "../include/tree.h"


#define ASCII_SIZE 256 // to ASCII Table use 128 and to Extended ASCII Table use 256


int main(int argc, char *argv[])
{
	unsigned char text[] = "Hello World";
	unsigned int frequency_table[ASCII_SIZE];
	LinkedList *list = NULL;
	Node *h_tree = NULL;

	printf("\n");
	initFrequencyTable(frequency_table, ASCII_SIZE);
	fillFrequencyTable(frequency_table, text);
	printFrequencyTable(frequency_table, ASCII_SIZE);

	printf("\n");
	list = initLinkedList();
	fillList(list, frequency_table, ASCII_SIZE);
	displayLinkedList(list);

	printf("\n");
	h_tree = buildHuffmanTreeByList(list);
	printf("\t --- Huffman Tree: --- \n");
	displayPreOrder(getSubTree(h_tree));
	printf("\n");

	free(list);
	freeSubTree(getSubTree(h_tree));
	free(h_tree);

	return 0;
}
