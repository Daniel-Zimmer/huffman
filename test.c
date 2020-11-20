#include <stdio.h>

#include "bit.h"

int main() {

	char buffer[4];

	for (int i = 0; i < 4*8; i++) {
		BIT_write(buffer, i, (i%2)==0);
	}

	for (int i = 0; i < 4*8; i++) {
		printf("%d ", BIT_read(buffer, i));
	}
	printf("\n");

	return 0;
}