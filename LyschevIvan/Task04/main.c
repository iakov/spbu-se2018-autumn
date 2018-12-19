#include <stdio.h>
void hackFunc(){
    printf("you are hacker!!!");
}
void inputfunc(){
    char buffer[5];
    printf("please enter:");
    scanf("%s",buffer);
    printf("u entered:%s \n",buffer);

}

int main() {
    inputfunc();
    return 0;
}