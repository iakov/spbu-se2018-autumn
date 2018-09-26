#include <stdio.h>
int main(void) {

	int a[28], i, count = 0, Lucky_ticket = 0;
	for (i = 0; i < 28; i++) a[i] = 0;
	for (i = 0; i < 1000; i++) {
		a[i / 100 + i / 10 % 10 + i % 10]++;
	}
	for (i = 0; i < 28; i++) Lucky_ticket+= a[i] * a[i];
	printf("%d", Lucky_ticket);

	return 0;
}