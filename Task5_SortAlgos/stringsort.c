#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 10000000;
const int hMOD = 1000000007;
const int hP = 357;

char *input[MAX];

int _Myhash(char *str) {
 	long long hashStr = 0;
	for (int i = 0; i < strlen(str); i++) {
	 	hashStr = (hashStr * hP + str[i]) % hMOD;
	}
	return (int)hashStr;
}
// hashes of their names
// ..idk why I did this...but this is kinda beautiful:)
#define __debug    327053052
#define bubble     188005939
#define insertion  512995672
#define merge      123970735
#define quick      823800909
#define radix      156427448
//for some reason "const int" does not work with switch-case

void swapString(char **a, char **b) {
 	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

void swapInt(int *a, int *b) {
 	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void forcedExit(char* message) {   
 	printf("%s\n\n", message);
	exit(-1);
}

void radixSort(int fileSize, int stringSize) {
	int dictSize = 256;
 	int numOfWords[dictSize];
	int nextWordIndex[dictSize];
	int *sortedIndexes = malloc(fileSize * sizeof(int));
	int *stringLen = malloc(fileSize * sizeof(int));
	if (stringLen == NULL)
		forcedExit("no memory");
	for (int i = 0; i < fileSize; i++) {
	 	stringLen[i] = strlen(input[i]);
	}
	
	char getStringChar(int stringId, int charId) {
	 	if (charId < stringLen[stringId]) return input[stringId][charId];
		return 0;
	}

	for (int digit = stringSize - 1; digit >= 0; digit--) {
		for (int i = 0; i < dictSize; i++) numOfWords[i] = 0;
		for (int i = 0; i < fileSize; i++) {
		 	numOfWords[getStringChar(i, digit)]++;
		}
		nextWordIndex[0] = 0;
		for (int i = 1; i < dictSize; i++) {
		        nextWordIndex[i] = nextWordIndex[i - 1] + numOfWords[i - 1];
		}
		for (int i = 0; i < fileSize; i++) {
		 	sortedIndexes[i] = nextWordIndex[getStringChar(i, digit)];
			nextWordIndex[getStringChar(i, digit)]++;
		}
		for (int i = 0; i < fileSize; i++) {
			while (i != sortedIndexes[i]) {
		 		swapString((input + i), (input + sortedIndexes[i]));
				swapInt(&stringLen[i], &stringLen[sortedIndexes[i]]);
				swapInt(&sortedIndexes[i], &sortedIndexes[sortedIndexes[i]]);
			}
		}
	}
	free(sortedIndexes);
	free(stringLen);
}

void bubbleSort(int fileSize) {
 	for (int i = 0; i < fileSize; i++) {
 	 	for (int j = 0; j < fileSize; j++) {
 	 	 	if (strcmp(input[i], input[j]) < 0) {
 	 	 	 	swapString((input + i), (input + j));
			}
		}
	}
}

void insertionSort(int fileSize) {
 	for (int i = 1; i < fileSize; i++) {
 	 	int j = i;
		while (j > 0 && strcmp(input[j], input[j - 1]) < 0) {
		 	swapString((input + j - 1), (input + j));
			j--;
		}
	}
}

void mergeSort(int l, int r) {
 	if (r - l <= 1) {
		return;
	}
	int mid = (l + r) / 2;
	mergeSort(l, mid);
	mergeSort(mid, r);
	int *sortedIndexes = malloc((r - l) * sizeof(int));
	if (sortedIndexes == NULL)
		forcedExit("no memory");
	int lSorted = l;
	int rSorted = mid;
	int nextIndex = 0;
	while (lSorted < mid && rSorted < r) {
	 	if (strcmp(input[lSorted], input[rSorted]) < 0) {
	 	 	sortedIndexes[lSorted - l] = nextIndex;
			lSorted++;
			nextIndex++;
		}
		else {
		 	sortedIndexes[rSorted - l] = nextIndex;
			rSorted++;
			nextIndex++;
		}
	}
	while (lSorted < mid) {
	 	sortedIndexes[lSorted - l] = nextIndex;
		nextIndex++;
		lSorted++;
	}
	while (rSorted < r) {
	 	sortedIndexes[rSorted - l] = nextIndex;
		nextIndex++;
		rSorted++;
	}
	for (int i = l; i < r; i++) {
	 	while (sortedIndexes[i - l] != i - l) {
	 	 	swapString((input + i), (input + sortedIndexes[i - l] + l));
			swapInt(&sortedIndexes[i - l], &sortedIndexes[sortedIndexes[i - l]]);
		}
	}
	free(sortedIndexes);
}

void quickSort(int l, int r, int strLen) {
 	if (r - l <= 1)
		return;
	char *sep = (char*)malloc(strLen * sizeof(char));
	if (sep == NULL)
		forcedExit("no memory");
	strcpy(sep, input[(rand() % (r - l)) + l]);
	int lSepIndex = l;
	int rSepIndex = r - 1;
	while (lSepIndex <= rSepIndex) {
	 	while (strcmp(input[lSepIndex], sep) < 0) {
	 	 	lSepIndex++;
		}
		while (strcmp(sep, input[rSepIndex]) < 0) {
		 	rSepIndex--;
		}
		if (lSepIndex <= rSepIndex) {
			swapString((input + lSepIndex), (input + rSepIndex));
			lSepIndex++;
			rSepIndex--;
		}
	}
	free(sep);
	quickSort(l, rSepIndex + 1, strLen);
	quickSort(rSepIndex + 1, r, strLen);
}

int main(int argc, char* argv[]) {
 	FILE *file = fopen(argv[2], "r");
	int maxStringLen = 16;
	int fileSize = atoi(argv[1]);
	if (file == NULL) {
	 	forcedExit("File name is incorrect");
	}
	char *buf = (char*)malloc((maxStringLen) * sizeof(char));
	for (int i = 0; i < fileSize; i++) {
	 	if (fgets(buf, maxStringLen, file) == NULL)
			forcedExit("Failed when reading");
		input[i] = (char*)malloc((strlen(buf)) * sizeof(char));
		if (input[i] == NULL) 
			forcedExit("no memory");
		strcpy(input[i], buf);
		int strLen = strlen(input[i]);
		if (input[i][strLen - 1] == '\n')
			input[i][strlen(input[i]) - 1] = '\0'; // just to erase '\n' from the end of the string
	}
	free(buf); 
	switch (_Myhash(argv[3])) {
	 	case radix:
			radixSort(fileSize, maxStringLen);
			break;
		case merge:
			mergeSort(0, fileSize);
			break;
		case bubble:
			bubbleSort(fileSize);
			break;
		case insertion:
			insertionSort(fileSize);
			break;
		case quick:
			quickSort(0, fileSize, maxStringLen);
			break;
		case __debug:  
			//__debug
			break;
		default:
			forcedExit("Sorting algorithm which was given is not supported or its name was written incorrectly\n");
			break;
	}
	for (int i = 0; i < fileSize; i++) {
	 	printf("%s\n", input[i]);
		free(input[i]);
	}
	fclose(file);
	return 0;
}               
