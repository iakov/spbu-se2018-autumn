#include <stdio.h>

void other()
{
    printf("Congratulations!\n");
    printf("Wait, wait, Houston we have a problem...\n");
}

void input()
{
    char buffer[20];

    printf("Enter some text:\n");
    scanf("%s", buffer);
    printf("You entered: %s\n", buffer);    
}

int main()
{
    input();

    return 0;
}
