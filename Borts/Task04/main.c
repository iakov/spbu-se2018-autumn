#include <stdio.h>

void other()
{
    printf("!! READ TO THE END !!\nI'm just a harmless function, printed some text. But if you read it,\nthen you want to change the state of the cell in the column < HW Attack of the stack > to green for my creator.\n");
    printf("\tWell, I have to go, have a nice day!\n");
}

void input()
{
    char buff[20];

    printf("Enter text:\n");
    scanf("%s", buff);
    printf("Entered: %s\n", buff);
}

int main()
{
    input();

    return 0;
}