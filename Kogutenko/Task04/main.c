#include <stdio.h>

void other() {
	printf("other()\n");
}

void input() {
	printf("What is your name?\n");
	char name[15];
	scanf("%s", name);
	printf("Welcome to... ");
}

int main() {
	input();
	printf("main()\n");
	return 0;
}
