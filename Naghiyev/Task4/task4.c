#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void bubblesort(char **string, int n){
int i, j;
for (i = 0; i < n; i++){
    for (j = 0; j < n - i - 1; ++j){
        if (strcmp(string[j], string[j + 1]) == 1) {
                char *buf = string[j];
                string[j] = string[j + 1];
                string[j + 1] = buf;
    }
}
}
}



int main (int argc, char* argv[]){
 FILE *file = fopen(argv[2], "r");
 int i, n;
 n = atoi(argv[1]);
 printf ("%d", n);
 char* string[n];
 for (i = 0; i < n; ++i) {
        string[i] = (char*) malloc(1025 * sizeof(char));
        fgets(string[i], 1024, file);
        //printf("%s", string[i]);
 }
 switch (argv[3][0]) {
        case 'b': {
            bubblesort(string, n);
            break;
        }
      //  case 'i': {
        //    insertionsort(string, n);
          //  break;
        //}
        default: break;
 }
for (i = 0; i < n; ++i) printf("%s", string[i]);
return 0;
}
