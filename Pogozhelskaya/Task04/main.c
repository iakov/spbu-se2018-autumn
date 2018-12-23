#include <stdio.h>

void other()
{
    printf("Ha-ha!\n You turned out to be too snoopy!\n Sorry, you can't visit us since this moment:(\n");
}

void input()
{
    char buffer[20];

    printf("Hi! I'm a peaceful resident of Mars named QwertyQwerty!\nAnd what's your name?");
    scanf("%s", buffer);
	printf("We'll wait for you to visit us, %s!\n", buffer);    
}

int main()
{
    input();

    return 0;
}
