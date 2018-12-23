#include <stdio.h>

void other()
{
    printf("WOW!\n");
    printf("You succesfully did buffer overflow exploit!\n");
}

void input()
{
    char buffer[10];

    printf("Enter text here:\n");
    scanf("%s", buffer);
    printf("You entered: %s\n", buffer);    
}

int main()
{
    input();
    return 0;
}