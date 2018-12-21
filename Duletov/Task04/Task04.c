#include <stdio.h>

void other()
{
    printf("You have entered function @OTHER@\n");
}

void input()
{
    char buffer[5];
    scanf("%s",buffer);
    printf("You entered: %s\n", buffer);    
}

int main()
{
    input();
    return 0;
}
