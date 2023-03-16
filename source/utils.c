#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/frequency_table.h"
#include "../include/tree.h"
#include "../include/tree.h"
#include "../include/utils.h"


void replaceWord(char *str, char *oldWord, char *newWord)
{
	char *pos, temp[100];
	int index = 0;
	int oldLen = strlen(oldWord);

	while ((pos = strstr(str, oldWord)) != NULL) {
		strcpy(temp, str);

		index = pos - str;
		str[index] = '\0';

		strcat(str, newWord);
		strcat(str, temp + index + oldLen);
	}
}

unsigned char * readFile(char *fileName)
{
	FILE *file = fopen(fileName, "rb");
	if (file == NULL)
	{
		printf("%s\n", "File not found!");
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	size_t fileLenght = ftell(file);
	rewind(file);

	unsigned char *buffer = calloc(fileLenght, sizeof(unsigned char));
	fread(buffer, sizeof(unsigned char), fileLenght, file);
	fclose(file);

	return buffer;
}

size_t getFileContentSize(char *fileName)
{
	FILE *file = fopen(fileName, "rb");

	if (!file)
	{
		printf("Unable to open file!");
		exit(EXIT_FAILURE);
	}

	fseek(file, 0, SEEK_END);
	size_t fileLenght = ftell(file);
	rewind(file);

	fclose(file);

	return fileLenght;
}

size_t getStringSize(char **dictionary, unsigned char *text, size_t fileSize)
{
	size_t i = 0, size = 0;

	for (i = 0; i < fileSize; i++) {
		size += strlen(dictionary[text[i]]);
	}

	return size + 1;
}

bitmap * encode(char **dictionary, unsigned char *text, size_t fileSize)
{
	const size_t fileTextSize = getStringSize(dictionary, text, fileSize);
	bitmap *bitMap = bitmapInit(fileTextSize);

	for (size_t i = 0; i < fileSize; i++)
	{
		for (int j = 0; j < (int)strlen(dictionary[text[i]]); j++)
		{
			bitmapAppendLeastSignificantBit(bitMap, dictionary[text[i]][j]);
		}
	}

	return bitMap;
}

void zip(bitmap *bitmapFile, char *originalFileName, char *fileName, size_t fileSize, size_t amountBits, unsigned int *frequencyTable)
{
	FILE *file = fopen(fileName, "wb");

	if (!file)
	{
		printf("Unable to open file!");
		exit(EXIT_FAILURE);
	}

	fwrite(&fileSize, sizeof(size_t), 1, file);
	fwrite(&amountBits, sizeof(size_t), 1, file);
	fwrite(originalFileName, sizeof(char), 100, file);
	fwrite(frequencyTable, sizeof(unsigned int), ASCII_SIZE, file);

	unsigned char byte = 0x0;
	int j = 7;

	for (int i = 0; i < (int)bitmapGetLength(bitmapFile); i++)
	{
		if (bitmapGetBit(bitmapFile, i))
		{
			byte = byte | (0x1 << j);
		}

		j--;

		if (j < 0)
		{
			fwrite(&byte, sizeof(unsigned char), 1, file);
			byte = 0x0;
			j = 7;
		}
	}

	if (j != 7)
	{
		fwrite(&byte, sizeof(unsigned char), 1, file);
	}

	fclose(file);
}

void unzip(char *fileName)
{
	FILE *file = fopen(fileName, "rb");
	if (!file)
	{
		printf("Unable to open file!");
		exit(EXIT_FAILURE);
	}

	size_t fileSize = 0;
	size_t amountBits = 0;
	char originalFileName[100];
	unsigned int frequencyTable[ASCII_SIZE];

	fread(&fileSize, sizeof(size_t), 1, file);
	fread(&amountBits, sizeof(size_t), 1, file);
	fread(originalFileName, sizeof(char), 100, file);
	fread(frequencyTable, sizeof(unsigned int), ASCII_SIZE, file);

	char newFileName[100] = "";
	strcpy(newFileName, originalFileName);
	replaceWord(newFileName, "input", "output");
	FILE *unzipped = fopen(newFileName, "wb");
	if (!unzipped)
	{
		printf("Unable to unzip file!");
		exit(EXIT_FAILURE);
	}

	LinkedList *sortedList = initLinkedList();
	fillList(sortedList, frequencyTable, ASCII_SIZE);

	Node *huffmanTree = buildHuffmanTreeByList(sortedList);
	SubTree *tree = getSubTree(huffmanTree);
	unsigned char byte = 0x0;

	int count = 0;
	while (fread(&byte, sizeof(unsigned char), 1, file))
	{
		for (int j = 7; j >= 0; j--)
		{
			count++;

			if (count > (int)amountBits)
			{
				break;
			}

			if (byte & (0x1 << j))
			{
				tree = getRightTree(tree);
			}
			else
			{
				tree = getLeftTree(tree);
			}

			if (isEmpty(getLeftTree(tree)) && isEmpty(getRightTree(tree)))
			{
				unsigned char character = getCharacter(tree);
				fwrite(&character, sizeof(unsigned char), 1, unzipped);
				tree = getSubTree(huffmanTree);
			}
		}
	}

	fclose(unzipped);
	fclose(file);

	freeSubTree(getSubTree(huffmanTree));
	freeLinkedList(sortedList);
}

void safeFree(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;

	return;
}

void checkAllocation(void *pointer, char *location)
{
	if (!pointer)
	{
		printf("allocation error at: %s\n", location);
		exit(EXIT_FAILURE);
	}
}
