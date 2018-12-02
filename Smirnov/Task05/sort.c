#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *sorted[100000000], *data[100000000];
int len[100000000], lenSorted[100000000];

void mergeSort(char **arr, int l, int r) {
    if (l == r - 1)
        return;
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid, r);
    char **tmp_copy = malloc((r - l) * sizeof(char*));

    int ptr_l = l, ptr_r = mid, ptr = 0;
    while (ptr < r - l && ptr_l < mid && ptr_r < r) {
        if (strcmp(arr[ptr_l], arr[ptr_r]) == -1) {
            tmp_copy[ptr++] = arr[ptr_l++];
        }
        if (strcmp(arr[ptr_r], arr[ptr_l]) <= 0) {
            tmp_copy[ptr++] = arr[ptr_r++];
        }
    }
    while (ptr_l < mid)
        tmp_copy[ptr++] = arr[ptr_l++];
    while (ptr_r < r)
        tmp_copy[ptr++] = arr[ptr_r++];

    for (int i = 0; i < r - l; ++i)
        arr[l + i] = tmp_copy[i];
    free(tmp_copy);
}

void bubbleSort(char **arr, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (strcmp(arr[j], arr[j + 1]) == 1) {
                char *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void insertionSort(char **arr, int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (strcmp(arr[j], arr[j + 1]) == 1) {
                char *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void quickSort(char **arr, int l, int r) {
    if (l >= r)
        return;
    int ptr_l = l, ptr_r = r;
    char *mid = arr[(l + r) / 2];

    while (ptr_l <= ptr_r) {
        while (strcmp(mid, arr[ptr_l]) == 1)
            ptr_l++;
        while (strcmp(arr[ptr_r], mid) == 1)
            ptr_r--;
        if (ptr_l <= ptr_r) {
            char *tmp = arr[ptr_l];
            arr[ptr_l] = arr[ptr_r];
            arr[ptr_r] = tmp;
            ptr_l++;
            ptr_r--;
        }
    }
    if (l < ptr_r) quickSort(arr, l, ptr_r);
    if (ptr_l < r) quickSort(arr, ptr_l, r);
}

void radixSort(char **arr, int n) {
    int maxLen = 0, maxCode = 0;

    for (int i = 0; i < n; ++i) {
        len[i] = strlen(arr[i]);
        for (int j = 0; j < len[i]; ++j)
            if ((int) arr[i][j] > maxCode)
                maxCode = (int) arr[i][j];
        if (maxLen < len[i])
            maxLen = len[i];
    }

    maxCode++;
    int *dict = calloc(maxCode, sizeof(int));

    for (int cnt = maxLen - 1; cnt >= 0; --cnt) {
        for (int i = 0; i < maxCode; ++i)
            dict[i] = 0;
        for (int i = 0; i < n; ++i) {
            int x = (cnt >= len[i]) ? 0 : (int) arr[i][cnt];
            dict[x]++;
        }
        int sum = 0;
        for (int i = 0; i < maxCode; ++i) {
            int temp = dict[i];
            dict[i] = sum;
            sum += temp;
        }
        for (int i = 0; i < n; ++i) {
            int x = (cnt >= len[i]) ? 0 : ((int) arr[i][cnt]);
            sorted[dict[x]] = arr[i];
            lenSorted[dict[x]] = len[i];
            dict[x]++;
        }

        for (int i = 0; i < n; ++i)
            len[i] = lenSorted[i];
        for (int i = 0; i < n; ++i)
            arr[i] = sorted[i];
    }

    free(dict);
}

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[2], "r");
    int n = atoi(argv[1]);
    for (int i = 0; i < n; ++i) {
        data[i] = malloc(sizeof(char));
        char input;
        int len = 0, size = 1;
        while ((input = fgetc(file)) != '\n') {
            if (input == EOF) break;
            len++;
            if (size <= len) {
                size <<= 1;
                data[i] = (char*) realloc(data[i], size * sizeof(char));
            }
            data[i][len - 1] = input;
            data[i][len] = '\0';
        }
    }
    char *type = argv[3];
    //clock_t t1 = clock();
    switch (type[0]) {
        case 'b': {
            bubbleSort(data, n);
            break;
        }
        case 'i': {
            insertionSort(data, n);
            break;
        }
        case 'm': {
            mergeSort(data, 0, n);
            break;
        }
        case 'q': {
            quickSort(data, 0, n - 1);
            break;
        }
        case 'r': {
            radixSort(data, n);
            break;
        }
        default:
            break;
    }
    //clock_t t2 = clock();
    for (int i = 0; i < n; ++i) {
        printf("%s\n", data[i]);
        free(data[i]);
    }
    //printf("Time: %.20f\n", ((double) (t2 - t1) / CLOCKS_PER_SEC));
    fclose(file);
    return 0;
}
