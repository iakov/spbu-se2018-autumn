#include <stdlib.h>
#include <stdio.h>

 void other() {
	printf("Here comes the hacking!\n");
}
 void input() {
	char buffer[6];
	scanf("%s", buffer);
	printf("You entered: %s\n", buffer);	
}
 int main() 
{
	printf("%s\n", "Here you can type something:");
	input();		
	return 0;
}
