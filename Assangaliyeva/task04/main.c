#include <stdio.h>

void other()
{
    printf("Hacker!\n");
}
void input()
{
    char buffer[10];
    
    printf("Enter some text:\n");
    scanf("%s",&buffer);
    printf("You entered: %s\n", buffer);  
}
int main()
{
    input();
    return 0;
}
