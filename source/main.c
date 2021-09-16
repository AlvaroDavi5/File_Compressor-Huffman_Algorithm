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
	char **dict = NULL;
	int height_tree = 0;
	char *code = NULL;

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

	height_tree = height(getSubTree(h_tree))+1;
	dict = initEncodeDictionary(ASCII_SIZE, height_tree);
	fillEncodeDictionary(getSubTree(h_tree), dict, "", height_tree);
	printf("\n");
	displayDictionary(dict, ASCII_SIZE);

	code = encode(dict, text);
	printf("\n");
	displayEncode(code);
	printf("\n");

	free(list);
	freeDictionary(dict, ASCII_SIZE, height_tree);
	freeSubTree(getSubTree(h_tree));
	free(h_tree);
	free(code);

	return 0;
}
