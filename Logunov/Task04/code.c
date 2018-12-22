#include <stdio.h>

void other() {
 	printf("ok you won :c\n");
}

void input() {
	char buffer[15];
	printf("here's your guess: \n");
	scanf("%s", &buffer);
	printf("nice try with %s!\n", buffer);
}

int main() {
	printf("huh, wanna catch me? wish you luck;)\n");
	input();
	return 0;
}