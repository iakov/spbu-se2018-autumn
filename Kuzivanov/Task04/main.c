#include <stdio.h>

void other()
{
    puts("ERROR!!!\n");
}

void input()
{
    char s[10];
    gets(s);
    puts(s);
}

int main()
{
    input();
}
