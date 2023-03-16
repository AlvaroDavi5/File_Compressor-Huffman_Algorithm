#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../include/frequency_table.h"
#include "../include/dictionary.h"
#include "../include/list.h"
#include "../include/tree.h"
#include "../include/utils.h"


void compress(char *filePath, int verbose);
void decompress(char *filePath);

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Portuguese");

	int verbose = FALSE;

	if (argc >= 4)
	{
		if (strcmp(argv[3], "-v") == 0 || strcmp(argv[3], "--verbose") == 0)
			verbose = TRUE;
		else
			verbose = FALSE;
	}
	if (argc >= 3)
	{
		if (strcmp(argv[1], "zip") == 0)
		{
			compress(argv[2], verbose);
		}
		else if (strcmp(argv[1], "unzip") == 0)
		{
			decompress(argv[2]);
		}
		else
		{
			printf("Invalid argument! The first argument must be 'zip' or 'unzip'.\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("At least 2 arguments are required, please, try again!\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}

void compress(char *filePath, int verbose)
{
	unsigned char *text = readFile(filePath);
	const size_t fileContentSize = getFileContentSize(filePath);
	unsigned int frequency_table[ASCII_SIZE];
	LinkedList *list = NULL;
	Node *huffmanTree = NULL;
	char **dict = NULL;

	initFrequencyTable(frequency_table, ASCII_SIZE);
	fillFrequencyTable(frequency_table, text, fileContentSize);
	if (verbose)
	{
		printf("\n");
		printFrequencyTable(frequency_table, ASCII_SIZE);
	}

	list = initLinkedList();
	fillList(list, frequency_table, ASCII_SIZE);
	if (verbose)
	{
		printf("\n");
		displayLinkedList(list);
	}

	huffmanTree = buildHuffmanTreeByList(list);
	if (verbose)
	{
		printf("\n");
		printf("\t --- Huffman Tree (Pre-Order): --- \n");
		displayPreOrder(getSubTree(huffmanTree));
		printf("\n");
	}

	int heightTree = height(getSubTree(huffmanTree)) + 1;
	dict = initEncodeDictionary(ASCII_SIZE, heightTree);
	fillEncodeDictionary(getSubTree(huffmanTree), dict, "", heightTree);
	if (verbose)
	{
		printf("\n");
		displayDictionary(dict, ASCII_SIZE);
	}

	bitmap *bitmapFile = encode(dict, text, fileContentSize);
	if (verbose)
	{
		printf("\n");
		printf("\t --- Encoded Data --- \n");
		printf(" Bitmap length: %u\n", bitmapGetLength(bitmapFile));
		printf("\n");
	}

	zip(bitmapFile, filePath, "./temp/zipped.bin", fileContentSize, bitmapGetMaxSize(bitmapFile), frequency_table);

	bitmapLibera(bitmapFile);
	safeFree(text);
	freeDictionary(dict, ASCII_SIZE);
	freeSubTree(getSubTree(huffmanTree));
	freeLinkedList(list);

	return;
}

void decompress(char *filePath)
{
	unzip(filePath);

	return;
}
