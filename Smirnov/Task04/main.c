#include <stdio.h>

void other() {
	printf("%s", "Congratultions! You are hacker!");
}

void input() {
	char buffer[5];
	scanf("%s", buffer);
	printf("You entered: %s. Sorry, but not today :(\n", buffer);	
}

int main() {
	printf("%s\n", "Hack me, please. Enter smth:");
	input();		
	return 0;
}