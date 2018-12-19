#include<stdio.h>

void input()
{
    char buffer[20];
    printf("Hi! My name is Thaurissan! What is your name?\n");
    scanf("%s", buffer);
    printf("Nice to meet you, %s!\n", buffer);
}

void other()
{
    printf("MORTAL INSECTS!\nYOU DARE TRESPASS INTO MY DOMAIN?\nBY FIRE BE PURGED!!!");
    fflush(stdout);
}

int main()
{
    input();
    printf("can you get here?\n");
    return 0;
}
