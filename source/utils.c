#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/list.h"
#include "../include/tree.h"


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
			printf("%d - |%c| freq: %u \n", i, i, table[i]);
	}
}
