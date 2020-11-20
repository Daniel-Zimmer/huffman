#include "bit.h"

char BIT_read(char *buffer, int idx) {
	int byte = idx/8;
	int bit  = idx%8;

	return (buffer[byte] >> (7 - bit)) & 1;
}

void BIT_write(char *buffer, int idx, char val) {
	int byte = idx/8;
	int bit  = idx%8;

	if (val == 1) {
		buffer[byte] |=  (1 << (7 - bit));
	} else {
		buffer[byte] &= ~(1 << (7 - bit));
	}
}