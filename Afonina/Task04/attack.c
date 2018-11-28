#include <stdio.h> 
#include <string.h>

void input() {
    char buf[32];
    printf("Enter a string\n");
    scanf("%s", buf);
    printf("You've entered: %s\n", buf);
}

void other() {
    printf("Augh! I've been hacked!\n");
}

int main(int argc, char* argv[]) {
    input();
    return 0;
}

