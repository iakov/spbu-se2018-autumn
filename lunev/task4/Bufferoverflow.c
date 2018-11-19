#include <stdio.h>
void other()
{
    printf("you are in other function");

}

void input()
{
    char buffer[10];
    scanf("%s", buffer);
    printf("You entered: %s\n", buffer);
}

int main()
{
    input();

    return 0;
}
