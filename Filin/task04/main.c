#include <stdio.h>

void other()
{
    printf("\nWell done!\n");
    printf("You have entered in  other function!\n");
}

void input()
{
    char buf[20];
    printf("Input: ");
    scanf("%s", &buf);
    printf("\nYour input: %s", buf);
}

int main()
{
    input();
    return 0;
}
