#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string[100000000];

void bubblesort(char **string, int n){
int i, j;
for (i = 0; i < n; i++){
    for (j = 0; j < n - i - 1; j++){
        if (strcmp(string[j], string[j + 1]) == 1) {
                char *buf = string[j];
                string[j] = string[j + 1];
                string[j + 1] = buf;
    }}}}

void insertionsort(char **string, int n){
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = i - 1; j >= 0; j--) {
            if (strcmp(string[j], string[j + 1]) == 1) {
                char *buf = string[j];
                string[j] = string[j + 1];
                string[j + 1] = buf;
}}}}

void quicksort(char **string, int l, int r){
    if (l >= r) return;
    int pl = l, pr = r, m = (l + r) / 2;
     do {
        while (strcmp(string[m], string[pl]) == 1) pl++;
        while (strcmp(string[m], string[pr]) == -1) pr--;
        if (pl <= pr){
        char *buf = string[pl];
        string[pl] = string[pr];
        string[pr] = buf;
        pl++;
        pr--;
        }
    } while (pl <= pr);
 quicksort (string, l, pr);
 quicksort (string, pl, r);
}
void mergesort (char** string, int l, int r){
 if (l == r - 1) return;
 int m = (l + r) / 2, i;
 mergesort (string, l, m);
 mergesort (string, m, r);
 char** buf = malloc((r - l) * sizeof(char*));
 int pl = l, pr = m, newp = 0;
 while (pl < m && pr < r){
    if (strcmp (string[pr], string[pl]) == 1) {
        buf[newp] = string [pl];
        newp++;
        pl++;
    }
    else {
        buf[newp] = string [pr];
        newp++;
        pr++;
    }
 }
 while (pl < m){
    buf[newp] = string [pl];
    newp++;
    pl++;
 }
 while (pr < r){
    buf[newp] = string [pr];
    newp++;
    pr++;
 }
for (i = l; i < r; i++) string[i] = buf[i - l];
free(buf);
}

void heap (char** string, int i, int n){
int max = i;
while (1){
    int child = 2 * i + 1;
    if (child < n && strcmp(string[child], string[max]) == 1) max = child;
    child++;
    if (child < n && strcmp(string[child], string[max]) == 1) max = child;
    if(max == i) break;
    else {
        char *buf = string[max];
        string[max] = string[i];
        string[i] = buf;
        i = max;
    }
}
}

void heapsort (char** string, int n){
int i;
for (i = n / 2; i >= 0; i--) heap(string, i, n);
for (i = n - 1; i >= 1; i--){
    char *buf = string[0];
    string[0] = string[i];
    string[i] = buf;
    heap(string, 0, i);
}
}


int main (int argc, char* argv[]){
 FILE *file = fopen(argv[2], "r");
 int i, n;
 n = atoi(argv[1]);
 for (i = 0; i < n; ++i) {
        string[i] = (char*) malloc(1025 * sizeof(char));
        fgets(string[i], 1024, file);
 }
 switch (argv[3][0]) {
        case 'b': {
            bubblesort(string, n);
            break;
        }
        case 'i': {
            insertionsort(string, n);
            break;
        }
        case 'q': {
            quicksort(string, 0, n - 1);
            break;
        }
        case 'm': {
            mergesort(string, 0, n);
            break;
        }
        case 'h': {
            heapsort(string, n);
            break;
        }
        default: break;
 }
for (i = 0; i < n; i++) printf("%s\n", string[i]);
for (i = 0; i < n; i++) free (string[i]);
fclose (file);
return 0;
}
