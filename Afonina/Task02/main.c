#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern int sort(int *arr, int n);

int main(int argc, char **argv) {
    bool has_to = false, has_from = false;
    int from = INT_MIN, to = INT_MAX, input_cnt = 0, to_sort_cnt = 0;
    int input_array[100] = {0}, array_to_sort[100] = {0};

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-' && argv[i][2] == 'f') {
            from = atoi(argv[i] + 7);
            has_from = true;
        } else if (argv[i][0] == '-' && argv[i][2] == 't') {
            to = atoi(argv[i] + 5);
            has_to = true;
        }
    }
    char chr;
    while (scanf("%d%c", &input_array[input_cnt++], &chr) && chr != '\n') { }
    for (int i = 0; i < input_cnt; ++i) {
        if (has_from && input_array[i] < from) {
            printf("%d ", input_array[i]);
        } else if (has_to && input_array[i] > to) {
            fprintf(stderr, "%d ", input_array[i]);
        } else {
            array_to_sort[to_sort_cnt++] = input_array[i];
        }
    }
    return sort(array_to_sort, to_sort_cnt);
}

