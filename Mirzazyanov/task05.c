#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void sChars(char **a, char **b) //swap pointers of char
{
	char *temp = *a;
	*a = *b;
	*b = temp;
}


void qs(char **array, int first, int last)
{

	if (first < last)
	{
		int left = first, right = last;
		char *middle = array[(left + right) / 2];
		while (left <= right){
		
			while (strcmp(array[left], middle) < 0) {
				left++;
			}
			while (strcmp(array[right], middle) > 0) {
				right--;
			}
			if (left <= right)
			{
				sChars(&array[left], &array[right]);
				left++;
				right--;
			}
		} 
		qs(array, first, right);
		qs(array, left, last);
	}

}



void mergeSort(char **array, int first, int second) {
	if (first == second - 1)
		return;
	int mid = (first + second) / 2;
	mergeSort(array, first, mid);
	mergeSort(array, mid, second);
	char **tmp_copy = malloc((second - first) * sizeof(char*));
	int ptr_l = first, ptr_r = mid, ptr = 0;
	while (ptr < second - first && ptr_l < mid && ptr_r < second) {
		if (strcmp(array[ptr_l], array[ptr_r]) == -1) {
			tmp_copy[ptr++] = array[ptr_l++];
		}
		if (strcmp(array[ptr_r], array[ptr_l]) <= 0) {
			tmp_copy[ptr++] = array[ptr_r++];
		}
	}
	while (ptr_l < mid)
		tmp_copy[ptr++] = array[ptr_l++];
	while (ptr_r < second)
		tmp_copy[ptr++] = array[ptr_r++];
	for (int i = 0; i < second - first; ++i)
		array[first + i] = tmp_copy[i];
	free(tmp_copy);
}

void bubble_sort(char **array, int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size - i; j++)
		{
			if (strcmp(array[j], array[j + 1]) > 0) {
				sChars(&array[j], &array[j + 1]);
			}
		}
	}
}

void make_heap(char **array, int root, int bottom) {
	int max_kid;
	while ((root * 2 <= bottom)) {
		if (root * 2 == bottom) {
			max_kid = root * 2;
		}
		else if (strcmp(array[root * 2], array[root * 2 + 1]) > 0) {
			max_kid = root * 2;
		}
		else {
			max_kid = root * 2 + 1;
		}
		if (strcmp(array[root], array[max_kid]) < 0) {
			sChars(&array[root], &array[max_kid]);
			root = max_kid;
		}
		else {
			break;
		}
	}
}
void heapSort(char **array, int size) {
	for (int i = (size / 2) - 1; i >= 0; --i) {
		make_heap(array, i, size - 1);
	}
	for (int i = size - 1; i > 0; --i) {
		sChars(&array[0], &array[i]);
		make_heap(array, 0, i - 1);
	}
}

void insertionSort(char **array, int size) 
{
	for (int i = 1; i < size; i++) 
	{
		for (int j = i; j > 0; j--) 
		{
			if (strcmp(array[j - 1], array[j]) > 0) 
			{
				sChars(&array[j - 1], &array[j]);
			}
		}
	}
}




int main(int argc, char *argv[]) {
	FILE *fp;
	int numofstr = atoi(argv[1]); 
	if (numofstr < 0) 
	{
		printf("Error, incorrect count of strings");
		exit(1);
	}
	int strlenght = 1000000;
	char **str = (char**)malloc(numofstr * sizeof(char*));
	if (str == NULL) {
		printf("No mem");
		exit(3);
	}
	char *buffer = (char*)malloc(strlenght * sizeof(char));
	if (buffer == NULL) {
		printf("No mem");
		exit(3);
	}
	fp = fopen(argv[2], "r");
	char kindofsort = argv[3][0];

	//file check
	if (NULL == fp) 
	{
		printf("Error, no file");
		exit(2);
	}

	//argc check
	if (argc != 4) 
	{
		printf("Error, you should have 4 arguments");
		exit(1);
	}

	for (int i = 0; i < numofstr; i++) 
	{
		if (fgets(buffer, strlenght, fp) == NULL) 
		{
			break;		
		}
		str[i] = malloc((strlen(buffer) + 1) * sizeof(char));
		if (str[i] == NULL){
		printf("No mem");
			int errvar = i;
			for (int j = 0; j < errvar; j++){
			free(str[j]);
			}
			exit(3);
		}
		strcpy(str[i], buffer);
	    	
		
	}
	free(buffer);

	switch (kindofsort)
	{
	case 'q':
		qs(str, 0, numofstr - 1);
		break;
	case 'm':
		mergeSort(str, 0, numofstr);
		break;
	case 'b':
		bubble_sort(str, numofstr);
		break;
	case 'i':
		insertionSort(str, numofstr);
		break;
	case 'h':
		heapSort(str, numofstr);
		break;
	default:
		break;
	}
	for (int i = 0; i < numofstr; ++i) {
		/*printf("%s\n", str[i]);*/
		free(str[i]);
	}
	free(str);
	fclose(fp);
	
	return 0;
}
