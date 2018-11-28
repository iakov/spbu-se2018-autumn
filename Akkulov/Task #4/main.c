#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

void other() {
    printf("Hacked!\n");
}

void input() {
    char buffer[8];
    printf("Enter a string: \n");
    scanf("%s", buffer);
    printf("You've entered: %s\n", buffer);
}

int main(int argc, char* argv[]) {
    input();
    return 0;
}