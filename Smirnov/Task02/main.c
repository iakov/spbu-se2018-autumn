#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int sort(int *arr, int size);

/**  Bubble sort

int sort(int *arr, int size) {
    int copy[100], transposCount = 0;
    for (int i = 0; i < size; ++i)
        copy[i] = arr[i];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        if (arr[size - i - 1] != copy[size - i - 1])
            transposCount++;
    }
    return transposCount;
}

*/

int to = 0, from = 0;
_Bool existTo = 0, existFrom = 0;

void parse(char *str) {
    int i = 0, cnt;
    char substr[4], number[1000];
    for ( ; i < strlen(str); ) {
        if (i < strlen(str) - 4)
            memcpy(substr, str + i, 4 * sizeof(char));
        else
            memcpy(substr, str + i, 2 * sizeof(char));
        if (substr[0] == 'f' && substr[1] == 'r' && substr[2] == 'o' && substr[3] == 'm') {
            i += 5;
            existFrom = 1;
            cnt = 0;
            memset(number, ' ', 1000 * sizeof(char));
            for ( ; i < strlen(str) && '0' <= str[i] && str[i] <= '9'; ++i)
                number[cnt++] = str[i];
            from = atoi(number);
        }
        else if (substr[0] == 't' && substr[1] == 'o') {
            i += 3;
            existTo = 1;
            cnt = 0;
            memset(number, ' ', 1000 * sizeof(char));
            for ( ; i < strlen(str) && '0' <= str[i] && str[i] <= '9'; ++i)
                number[cnt++] = str[i];
            to = atoi(number);
        }
        else {
            ++i;
        }
    }
}

int main(int argc, char *argv[]) {

    // Parsing argv
    char argvConcat[1000];
    for (int i = 1; i < argc; ++i)
        strcat(argvConcat, argv[i]);
    parse(argvConcat);

    // Reading numbers
    int data[100], arr[100], count = 0, arrSize = 0;
    char spaceSymbol = ' ';
    while (spaceSymbol != '\n') {
        scanf("%d%c", &data[count], &spaceSymbol);
        if (existFrom && data[count] <= from) {
            fprintf(stdout, "%d ", data[count]);
        }
        else {
            if (existTo && data[count] >= to)
                fprintf(stderr, "%d ", data[count]);
            else
                arr[arrSize++] = data[count];
        }
    }
    int ans = sort(arr, arrSize);
    //printf("%d", ans);
    return ans;
}
