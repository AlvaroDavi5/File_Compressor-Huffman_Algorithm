#ifndef _FREQ_TABLE_H

	#define _FREQ_TABLE_H

	void initFrequencyTable(unsigned int *table, int size);
	void fillFrequencyTable(unsigned int *table, unsigned char *text, size_t fileSize);
	void printFrequencyTable(unsigned int *table, int size);

#endif
