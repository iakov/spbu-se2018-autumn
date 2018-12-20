#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_string;

void swap(char* str1, char* str2) {
    char* tmp = (char*)malloc(sizeof(char) * max_string);
    if (tmp == NULL) {
    fprintf(stderr, "%s\n", "Allocation error in swap");
    exit(4);
    }
    strcpy(tmp, str1);
    strcpy(str1, str2);
    strcpy(str2, tmp);
    free(tmp);
}

void bubble_sort(char** strings, int N)  {
    for(int i = 0; i < N - 1; i++)
        for(int j = 0; j < N - i - 1; j++)
            if (strcmp(strings[j + 1], strings[j]) <  0)
                swap(strings[j], strings[j + 1]);
} 

void insertion_sort(char** strings, int N) {
    for(int i  = 0; i < N - 1; i++)
        for(int j = i + 1; j < N; j++)
            if (strcmp(strings[i], strings[j]) > 0)
                swap(strings[i], strings[j]);
}

void merge(char** strings, int left, int mid, int right) {
    int it1 = 0, it2 = 0;
    char** result = (char**)malloc((right - left) * sizeof(char*));
    if (result == NULL) {
        fprintf(stderr, "%s\n", "Allocation error in merge");
        exit(4);
    }
    for(int i = 0; i < (right - left); i++) {
        result[i] = (char*)malloc(sizeof(char) * max_string);
        if (result[i] == NULL) {
            fprintf(stderr, "%s\n", "Allocation error in merge");
            exit(4);
        }
    }
    while (left + it1 < mid && mid + it2 < right) {
        if (strcmp(strings[left + it1], strings[mid + it2]) < 0) {
            strcpy(result[it1 + it2], strings[left + it1]);
            it1++;
        } else { 
            strcpy(result[it1 + it2], strings[mid + it2]);
            it2++;
        }
    }
    while (left + it1 < mid) {
        strcpy(result[it1 + it2], strings[left + it1]);
        it1++;
    }
    while (mid + it2 < right) {
        strcpy(result[it1 + it2], strings[mid + it2]);
        it2++;
    } 
    for(int i = 0; i < (it1 + it2); i++)
        strcpy(strings[left + i], result[i]);
    for(int i = 0; i < (right - left); i++)
        free(result[i]);
    free(result);
}  

void merge_sort(char** strings, int left, int right) {
    if (left + 1 >= right)
        return;
    int mid = (left + right) / 2;
    merge_sort(strings, left, mid);
    merge_sort(strings, mid, right);
    merge(strings, left, mid, right);
}

int partition(char** strings, int left, int right) {
        int l = left - 1, r = right + 1;
        char* pivot = strings[left];
        while(1) {
            do {
                l++;
            } while (strcmp(strings[l], pivot) < 0);
            do {
                r--;
            } while (strcmp(strings[r], pivot) > 0);
            if (l >= r) return r;
            swap(strings[l], strings[r]);
        }
}

void quick_sort(char** strings, int left, int right) {
    if (left < right) {
        int pivot = partition(strings, left, right);
        quick_sort(strings, left, pivot);
        quick_sort(strings, pivot + 1, right);
    }
}

void heapify(char** strings, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && strcmp(strings[l], strings[largest]) > 0)
        largest = l;
    if (r < n && strcmp(strings[r], strings[largest]) > 0)
        largest = r;
    if (largest != i) {
        if(strings[i] != strings[largest])       
            swap(strings[i], strings[largest]);
        heapify(strings, n, largest);
    }
}

void heap_sort(char** strings, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(strings, n, i);
    for (int i = n - 1; i >= 0; i--) {
        if(strings[0] != strings[i]) 
            swap(strings[0], strings[i]);
        heapify(strings, i, 0);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 4) {
        FILE* f;
        int N = atoi(argv[1]);
        const char* file = (const char*)argv[2];
        char* sort_name = argv[3];
        f = fopen(file, "r");
        char** strings = (char**)malloc(N * sizeof(char*));
        if (strings == NULL) {
            fprintf(stderr, "%s\n", "Allocation error");
            fflush(stdout);
            exit(4);
        }
        if (f != NULL) {
            for (int i = 0; i < N; i++) {
		        strings[i] = (char*)malloc(1 * sizeof(char));
                if (strings[i] == NULL) {
                    fprintf(stderr, "%s\n", "Allocation error");
                    fflush(stdout);
                    exit(4);
                }
		        int j = 0;
		        while ((strings[i][j++] = fgetc(f)) != '\n') {
			      strings[i] = (char*)realloc(strings[i], (j + 1) * sizeof(char));
                    if (strings[i] == NULL) {
                        fprintf(stderr, "%s\n", "Allocation error");
                        fflush(stdout);
                        exit(4);
                    }
                }
		        if (j > max_string)
			        max_string = j;
	        }
        } else {
            printf("%s\n", "Unable to open the file"); 
            fflush(stdout);
            exit(2);
        }
        if (strcmp(sort_name, "bubble") == 0)
            bubble_sort(strings, N);
        else if (strcmp(sort_name, "insertion") == 0)
            insertion_sort(strings, N);
        else if (strcmp(sort_name, "merge") == 0)
            merge_sort(strings, 0, N);
        else if (strcmp(sort_name, "quick") == 0)
            quick_sort(strings, N - 1);
        else if (strcmp(sort_name, "heap") == 0)
            heap_sort(strings, N);
        else if (strcmp(sort_name, "radix") == 0)
            heap_sort(strings, N);
        else {
            printf("%s\n", "invalid sort name");
            fflush(stdout);
            exit(1);
        }
        for(int i = 0; i < N; i++)
            printf("%s", strings[i]);
        fflush(stdout);
        fclose(f);
        for(int i = 0; i < N; i++)
            free(strings[i]);
        free(strings);
    } else {
        printf("%s\n", "invalid number of arguments");
        exit(1);
    }
    return 0;
}

