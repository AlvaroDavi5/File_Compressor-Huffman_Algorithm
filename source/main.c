#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/utils.h"
#include "../include/bitmap.h"


#define MAX_TEXT_SIZE 1200
#define ASCII_SIZE 256 // to ASCII Table use 128 and to Extended ASCII Table use 256


void readTextFromFile(char *fileName, char *buffer, int size);


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Portuguese");

	unsigned char text[MAX_TEXT_SIZE] = "";
	unsigned int frequency_table[ASCII_SIZE];
	LinkedList *list = NULL;
	Node *h_tree = NULL;
	char **dict = NULL;
	int height_tree = 0;
	unsigned char *code = NULL, *decod = NULL;

	if (argc > 2)
	{
		if (strcmp(argv[1], "zip") == 0)
		{
			readTextFromFile(argv[2], (char *) text, MAX_TEXT_SIZE);
			printf("%s\n", text);
		}
		else if (strcmp(argv[1], "unzip") == 0)
		{
			/* code */
		}
		else
		{
			printf("%s\n", "Invalid argument!");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("2 arguments are required, please, try again!\n");
		exit(EXIT_FAILURE);
	}

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

	code = (unsigned char *) encode(dict, text);
	printf("\n");
	printf("\t --- Encoded Data --- \n");
	printf("  %s\n", code);
	printf("\n");
	decod = (unsigned char *) decode(getSubTree(h_tree), code);
	printf("\t --- Decoded Data --- \n");
	printf("  %s\n", decod);
	printf("\n");

	safeFree(list);
	freeDictionary(dict, ASCII_SIZE);
	freeSubTree(getSubTree(h_tree));
	safeFree(h_tree);
	safeFree(code);
	safeFree(decod);


	return 0;
}

void readTextFromFile(char *fileName, char *buffer, int size)
{
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("%s\n", "File not found!");
		exit(EXIT_FAILURE);
	}
	fgets(buffer, size, file);
	fclose(file);

	return;
}

int bitmapTester(void) {
	puts("teste"); /* prints  */

	bitmap* bm=bitmapInit(10);
	printf("size=%d bits\n", bitmapGetMaxSize(bm));
	bitmapAppendLeastSignificantBit(bm, 1);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 1);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 1);
	bitmapAppendLeastSignificantBit(bm, 0);
	bitmapAppendLeastSignificantBit(bm, 1);

	printf("%0xh\n", bitmapGetContents(bm)[0]);			
	printf("%0xh\n", bitmapGetContents(bm)[1]);
	printf("length=%0d\n", bitmapGetLength(bm));

	for (unsigned int i=0; i<bitmapGetLength(bm); i++) {
		printf("bit #%d = %0xh\n", i, bitmapGetBit(bm, i));
	}

    
    bitmapLibera(bm);
    
	puts("teste2");
	return EXIT_SUCCESS;

}
