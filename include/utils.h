#ifndef _UTILS_H

	#define _UTILS_H

	#include "../include/bitmap.h"

	#define FALSE 0
	#define TRUE 1
	#define ASCII_SIZE 256 // to ASCII Table use 128 and to Extended ASCII Table use 256

	unsigned char * readFile(char *fileName);
	size_t getFileContentSize(char *fileName);
	bitmap * encode(char **dictionary, unsigned char *text, size_t fileSize);
	void zip(bitmap *bitmapFile, char *originalFileName, char *fileName, size_t fileSize, size_t amountBits, unsigned int *frequencyTable);
	void unzip(char *fileName);
	void safeFree(void *ptr);
	void checkAllocation(void *pointer, char *location);

#endif
