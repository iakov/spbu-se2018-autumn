#include <stdio.h>

void other()
{
    printf("You finally have come to the secret function!!!");
}

void input()
{
    char buff[17];
    printf("Write something here: \n");
    scanf("%s", buff);
    printf("You have written something like \"%s\"\n", buff);
}

int main()
{
    input();
    return 0;
}
