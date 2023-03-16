#include <stdio.h>
#include "../include/frequency_table.h"


void initFrequencyTable(unsigned int *table, int size)
{
	for (int i = 0; i < size; i++)
	{
		*(table + i) = 0;
	}
}

void fillFrequencyTable(unsigned int *table, unsigned char *text, size_t fileSize)
{
	int i = 0;

	for (i = 0; i < (int)fileSize; ++i) {
		*(table + text[i]) += 1;
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
