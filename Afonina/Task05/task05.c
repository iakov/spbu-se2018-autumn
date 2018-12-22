#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void swap(char **str1, char **str2) {
    char *tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

void merge(int left, int middle, int right, char **base) {
    char **buffer = (char**)malloc((right - left + 2) * sizeof(char*));
    int left_ptr = left;
    int right_ptr = middle;
    int buf_ptr = 0;
    while (left_ptr <  middle && right_ptr < right) {
        if (strcmp(base[left_ptr], base[right_ptr]) < 0) {
            buffer[buf_ptr] = base[left_ptr];
            ++left_ptr;
        } else {
            buffer[buf_ptr] = base[right_ptr];
            ++right_ptr;
        }
        ++buf_ptr;
    }
    while (left_ptr < middle) {
        buffer[buf_ptr++] = base[left_ptr++];
    }
    while (right_ptr < right) {
        buffer[buf_ptr++] = base[right_ptr++];
    }
    for (int i = left; i < right; ++i) {
        base[i] = buffer[i - left];
    }
    free(buffer);
}

void merge_sort(int left, int right, char **base) {
    if (right - left <= 1) return;
    int middle = (left + right) / 2;
    merge_sort(left, middle, base);
    merge_sort(middle, right, base);
    merge(left, middle, right, base);
}

void insertion_sort(char **str, int cnt) {
    for (int i = 1; i < cnt; ++i) {
        int j = i;
        while(j > 0 && strcmp(str[j], str[j - 1]) < 0) {
                swap(&str[j], &str[j - 1]);
                --j;
        }
    }
}

void bubble_sort(char **str, int cnt) {
    for (int i = 0; i < cnt - 1; ++i) {
        for (int j = 0; j < cnt - i - 1; ++j) {
            if ((strcmp(str[j], str[j + 1])) > 0) {
                swap(&str[j], &str[j + 1]);
            }
        }
    }
}

void quick_sort(int left, int right, char **base) {
    if (left >= right) {
        return;
    }
    int left2 = left, right2 = right;
    int middle = (right + left) / 2;
    char *pivot = base[middle];
    while (left2 <= right2) {
        while (strcmp(base[left2], pivot) < 0) {
            ++left2;
        }
        while (strcmp(base[right2], pivot) > 0) {
            --right2;
        }
        if (left2 <= right2) {
            swap(&base[left2++], &base[right2--]);
        }
    }
    if(left<right2) quick_sort(left, right2, base);
    if(left2<right) quick_sort(left2, right, base);
}

void sift_down(char **base, int root, int bottom) {
    int max_ind;
    while ((root * 2 <= bottom)) {
        if (root * 2 == bottom) {
            max_ind = root * 2;
        } else if (strcmp(base[root * 2], base[root * 2 + 1]) > 0) {
            max_ind = root * 2;
        } else {
            max_ind = root * 2 + 1;
        }
        if (strcmp(base[root], base[max_ind]) < 0) {
            swap(&base[root], &base[max_ind]);
            root = max_ind;
        } else {
            break;
        }
    }
}

void heap_sort(char **base, int n) {
    for (int i = (n / 2) - 1; i >= 0; --i) {
        sift_down(base, i, n - 1);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(&base[0], &base[i]);
        sift_down(base, 0, i - 1);
    }
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Wrong number of arguments!\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    FILE *f = fopen(argv[2], "r");
    char *algorithm_name = argv[3];
    if (f == NULL) {
        printf("Cannot open file\n");
        exit(2);
    }

    int str_cnt = 0;
    const int MAX_STR_LEN = 1000000;
    char **arr_of_str = (char**)malloc(n * sizeof(char*));
    if (arr_of_str == NULL) {
        printf("Do not have enough memory\n");
        exit(4);
    }
    char *buf = (char*)malloc(MAX_STR_LEN * sizeof(char));
    if (buf == NULL) {
        printf("Do not have enough memory\n");
        exit(4);
    }
    for (int i = 0; i < n; str_cnt = ++i) {
        if (fgets(buf, MAX_STR_LEN, f) == NULL) {
            --str_cnt;
            break;
        }
        int str_len = strlen(buf);
        arr_of_str[i] = (char*)malloc((str_len + 1) * sizeof(char));
        if (arr_of_str[i] == NULL) {
            printf("Do not have enough memory\n");
            for(int i = 0; i < str_cnt; ++i) {
                free(arr_of_str[i]);
            }
            free(arr_of_str);
            exit(4);
        }
        strcpy(arr_of_str[i], buf);
    }
    fclose(f);
    free(buf);

    if (!strcmp(algorithm_name, "bubble")) {
            bubble_sort(arr_of_str, str_cnt);
    } else if (!strcmp(algorithm_name, "insertion")) {
        insertion_sort(arr_of_str, str_cnt);
    } else if (!strcmp(algorithm_name, "merge")) {
        merge_sort(0, str_cnt, arr_of_str);
    } else if (!strcmp(algorithm_name, "quick")) {
        quick_sort(0, str_cnt - 1, arr_of_str);
    } else if (!strcmp(algorithm_name, "radix")) {
        heap_sort(arr_of_str, str_cnt);
    } else {
        printf("Unknown algorithm!\n");
        exit(1);
    }

    for(int i = 0; i < str_cnt; ++i) {
        printf("%s", arr_of_str[i]);
        free(arr_of_str[i]);
    }
    free(arr_of_str);
}
