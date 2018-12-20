#include <stdio.h>
#include <string.h>

void other()
{
    printf("You are inside\n");
}

void input()
{
    char string[32];

    scanf("%s", string);
    printf("String length is '%d'\n", strlen(string));
}

int main()
{
    input();
    return 0;
}
