#include <stdio.h>

void other()
{
    printf("You finally came to the secret function!!!");
}

void input()
{
    char buff[17];
    printf("Write something here: \n");
    scanf("%s", buff);
    printf("You wrote something like \"%s\"\n", buff);
}

int main()
{
    input();
    return 0;
}
