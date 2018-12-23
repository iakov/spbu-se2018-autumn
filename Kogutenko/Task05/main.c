#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void close_file(FILE *file) {
	if(fclose(file) == EOF) {
		printf("%s", "\nFailed to close file correctly\n");
	}
}

/* Swap strings */
void swap(char **a, char **b) {
	char *temp = *a;
	*a = *b;
	*b = temp;
}

/* Bubble sort */
void bubble(char **strings, int n) {
	--n;
	for(int i = 0; i < n; ++i) {
		
		for(int j = 0; j < n - i; ++j) {
			
			if(strcmp(strings[j], strings[j+1]) > 0) {
				swap(&strings[j], &strings[j+1]);
			}
		}
	}
}

/* Insertion sort */
void insertion(char **strings, int n) {
	
	for(int i = 1; i < n; ++i) {
		
		for(int j = i-1; j >= 0; --j) {
			
			if(strcmp(strings[j], strings[j+1]) > 0) {
				swap(&strings[j], &strings[j+1]);
			}
		}
	}
}

/* Merge sort */
char** merge(char **up, char **down, int left, int right) {
	if(left == right) {
		down[left] = up[left];
		return down;
	}
	
	int middle = (left + right) / 2;
	
	char **l_buffer = merge(up, down, left, middle);
	char **r_buffer = merge(up, down, middle + 1, right);
	
	char **target;
	if(l_buffer == up) {
		target = down;
	} else {
		target = up;
	}
	
	int l_current = left, r_current = middle + 1;
	
	for(int i = left; i <= right; ++i) {
		if(l_current <= middle && r_current <= right) {
			
			if(strcmp(l_buffer[l_current], r_buffer[r_current]) < 0) {
				
				target[i] = l_buffer[l_current];
				++l_current;
			} else {
				
				target[i] = r_buffer[r_current];
				++r_current;
			}
		} else if(l_current <= middle) {
			
			target[i] = l_buffer[l_current];
			++l_current;
		} else {
			
			target[i] = r_buffer[r_current];
			++r_current;
		}
	}
	return target;
}

/* Quick sort */
void quick(char **strings, int first, int last) {
	if(first < last) {
		int left = first, right = last;
		char *middle = strings[(left + right) / 2];
		
		do {
			while(strcmp(strings[left], middle) < 0) ++left; 
			while(strcmp(strings[right], middle) > 0) --right;
			if(left <= right) {
				swap(&strings[left], &strings[right]);
				++left;
				--right;
			} 
		} while(left <= right);
		
		quick(strings, first, right);
		quick(strings, left, last);
	}
}

int *current_offset;

/* Radix sort */

#define CHARSET_SIZE 256

/* characters_count[]. Firstly, it used for count amounts of strings, that contain some symbol in needed position */
/* Secondly, it used for correct exit from loop, when strings with the same letters took their right positions */
/* characters_count[] has length CHARSET_SIZE + 1. Element with address CHARSET_SIZE helps to break loop, when strings with the last symbol in charset took right positions */
/* current_offset[] is used for tracking positions of letters */

void radix(char **strings, int n, int position) {
	
	int *characters_count = calloc(CHARSET_SIZE + 1, sizeof(int));
	
	if(characters_count == 0) {
		free(strings);
		free(current_offset);
		printf("Error: failed to allocate additional memory\n");
		exit(4);
	}
	
	for(int i = 0; i < n; ++i) {
		++characters_count[strings[i][position] + 1];
	}
	
	int offset = 0;
	
	for(int i = 1; i < CHARSET_SIZE + 1; ++i) {
		offset += characters_count[i];
		characters_count[i] = offset;
	}
	
	memcpy(current_offset, characters_count, CHARSET_SIZE * sizeof(int));
	
	int i = 0;
	for(int needed_symbol = 0; needed_symbol < CHARSET_SIZE; ++needed_symbol) {
		
		int limit = characters_count[(int)needed_symbol + 1];
		
		while(i != limit) {
		
			char current_symbol = strings[i][position];
			
			if(current_symbol != (char)needed_symbol) {
				
				int needed_position = current_offset[(int)current_symbol];
				swap(&strings[i], &strings[needed_position]);
				++current_offset[(int)current_symbol];
				
			} else ++i;
		}
	}
	
	++position;
	
	for(int i = 2; i < CHARSET_SIZE + 1; ++i) {
		if(characters_count[i] - characters_count[i-1] > 1) {
			radix(strings + characters_count[i-1], characters_count[i] - characters_count[i-1], position);
		}
	}
	
	free(characters_count);
}


int main(int argc, char **argv) {
	
	/* Checking quantity of arguments */
	if(argc != 4) {
		printf("Error: invalid quantity of arguments\n");
		exit(1);
	}
	
	/* Checking the correctness of the number */
	char *p = argv[1];
	while(*p >= '0' && *p <= '9') {
		++p;
	}
	
	if(*p != '\0') {
		printf("Error: specified number of elements is not correct\n");
		exit(1);
	}
	
	int n = atoi(argv[1]);
	
	/* Checking if file exists */
	if(access(argv[2], R_OK) == -1) {
		printf("Error: file with specified name does not exist\n");
		exit(2);
	}
	
	/* Opening file */
	FILE *input = fopen(argv[2], "r");
	if(input == NULL) {
		printf("Error: failed to open file with specified name\n");
		exit(4);
	}
	
	/* Allocating memory for strings pointers */
	char **strings = malloc(n * sizeof(char*));
	if(strings == NULL) {
		close_file(input);
		printf("Error: failed to allocate memory for strings pointers\n");
		exit(4);
	}
	char *string;
	
	/* Buffer for input strings */
	char *buffer = malloc(65 * sizeof(char));
	
	/* Loading strings */
	int i;
	for(i = 0; (i < n) && !feof(input); ++i) {
		
		char current_symbol;
		char *p = buffer;
		
		current_symbol = fgetc(input);
		
		/* Break if empty line */
		if(feof(input)) {
			break;
		}
		
		while(!feof(input) && current_symbol != '\n') {
			*p = current_symbol;
			++p;
			current_symbol = fgetc(input);
		}
		
		*p = '\0';
		++p;
		
		string = malloc((p - buffer) * sizeof(char));
		if(string == NULL) {
			close_file(input);
			printf("Error: failed to allocate memory for string\n");
			exit(4);
		}
		memcpy(string, buffer, p - buffer);
		strings[i] = string;
		
	}
	
	free(buffer);
	
	n = i;
	
	/* Sorting */
	if(strcmp(argv[3], "bubble") == 0) {
		
		bubble(strings, n);
		
	} else if(strcmp(argv[3], "insertion") == 0) {
		
		insertion(strings, n);
		
	} else if(strcmp(argv[3], "merge") == 0) {
		
		char **merge_buffer = malloc(n * sizeof(char*));
		
		if(merge_buffer == NULL) {
			close_file(input);
			free(strings);
			printf("Error: failed to allocate additional memory for merge sort\n");
			exit(4);
		}
		
		if(merge(strings, merge_buffer, 0, n-1) == merge_buffer) {
			free(strings);
			strings = merge_buffer;
		} else {
			free(merge_buffer);
		}
		
	} else if(strcmp(argv[3], "quick") == 0) {
		
		quick(strings, 0, n-1);
		
	} else if(strcmp(argv[3], "radix") == 0) {
		
		current_offset = malloc(256 * sizeof(int));
		
		if(current_offset == NULL) {
			close_file(input);
			free(strings);
			printf("Error: failed to allocate additional memory\n");
			exit(4);
		}
		
		radix(strings, n, 0);
		free(current_offset);
		
	} else {
		printf("Error: unknown sort specified\n");
		exit(1);
	}
	
	/* Printing sorted strings */
	for(int i = 0; i < n; ++i) {
		puts(strings[i]);
		free(strings[i]);
	}
	
	free(strings);
	close_file(input);
	return 0;
}
