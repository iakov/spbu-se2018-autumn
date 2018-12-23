#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define true 1

int MaxStringSize = 256;

void PrintError(char* Message, int ExitCode) {
	printf("%s\n", Message);
	fflush(stdin);
	exit(ExitCode);
}

void swap(char** FirstString, char** SecondString) {
	char* Temp = *FirstString;
	*FirstString = *SecondString;
	*SecondString = Temp;
}

void BubbleSort(char** Strings, int NumberStrings) {
    for(int i = 0; i < NumberStrings - 1; ++i)
        for(int j = 0; j < NumberStrings - i - 1; ++j)
            if (strcmp(Strings[j + 1], Strings[j]) <  0)
				swap(&Strings[j + 1], &Strings[j]);
}

void InsertionSort(char** Strings, int NumberStrings) {
    for(int i = 0; i < NumberStrings - 1; ++i)
        for(int j = i + 1; j < NumberStrings; ++j)
            if (strcmp(Strings[i], Strings[j]) > 0)
                swap(&Strings[i], &Strings[j]);
}

void MergeSort(char** Strings, int Left, int Right) {
	if (Left == Right - 1) 
		return;
	int Middle = (Left + Right) >> 1;
	MergeSort(Strings, Left, Middle);
	MergeSort(Strings, Middle, Right);
	int IteratorFirst = Left, 
		IteratorSecond = Middle;
	char** Buffer = (char**)malloc(Right * sizeof(char*));
	if (Buffer == NULL) 
		PrintError("Error Memory Allocation at MergeSort!", 4);
	for(int i = 0; i < Right; ++i) {
		Buffer[i] = (char*)malloc(MaxStringSize * sizeof(char));
		if (Buffer[i] == NULL) 
			PrintError("Error Memory Allocation at MergeSort!", 4);
	}
	for (int i = 0; i < Right - Left; ++i) {
		if ((IteratorSecond >= Right) || ((IteratorFirst < Middle) &&
			(strcmp(Strings[IteratorFirst], Strings[IteratorSecond]) < 0)))
			strcpy(Buffer[i], Strings[IteratorFirst++]);
		else
			strcpy(Buffer[i], Strings[IteratorSecond++]);
	}
	for (int i = 0; i < Right - Left; ++i)
		strcpy(Strings[i + Left], Buffer[i]);
	for (int i = 0; i < Right; ++i)
		free(Buffer[i]);
	free(Buffer);
}

int Partition(char** Strings, int Left, int Right) {
	char* Pivot = Strings[Left];
	int i = Left - 1, 
		j = Right + 1;
	while (true) {
		do {i++;} while (strcmp(Strings[i], Pivot) < 0);
		do {j--;} while (strcmp(Strings[j], Pivot) > 0);
		if (i >= j) return j;
		swap(&Strings[i], &Strings[j]);
	}
}

void QuickSort(char** Strings, int Left, int Right) {
	if (Left < Right) {
		int Middle = Partition(Strings, Left, Right);
		QuickSort(Strings, Left, Middle);
		QuickSort(Strings, Middle + 1, Right);
	}
}

void heapify(char** Strings, int NumberStrings, int Position) {
	int Largest = Position, 
		Left = (Position << 1) + 1, 
		Right = (Position << 1) + 2;
	if (Left < NumberStrings && 
		strcmp(Strings[Left], Strings[Largest]) > 0)
		Largest = Left;
	if (Right < NumberStrings && 
		strcmp(Strings[Right], Strings[Largest]) > 0)
		Largest = Right;
	if (Largest != Position) {
		swap(&Strings[Largest], &Strings[Position]);
		heapify(Strings, NumberStrings, Largest);
	}
}

void HeapSort(char** Strings, int NumberStrings) {
	for (int i = (NumberStrings >> 1) - 1; i >= 0; --i)
		heapify(Strings, NumberStrings, i);
	for (int i = NumberStrings - 1; i >= 0; --i) {
		if (strcmp(Strings[0], Strings[i]) != 0)
			swap(&Strings[0], &Strings[i]);
		heapify(Strings, i, 0);
	}
}

int compare(char* map, int* StrBegin, int* StrEnd, int FirstString, int SecondString) {
	int FirstLen = StrEnd[FirstString] - StrBegin[FirstString] + 1,
		SecondLen = StrEnd[SecondString] - StrBegin[SecondString] + 1;
	if (FirstLen < SecondLen) 
		return -1;
	if (FirstLen > SecondLen) 
		return 1;
	int Len = FirstLen;
	for (int i = 0; i < Len; ++i)
		if (map[StrBegin[FirstString] + i] < map[StrBegin[SecondString] + i])
			return -1;
		else if (map[StrBegin[FirstString] + i] > map[StrBegin[SecondString] + i])
			return 1;
	return 0;
}

int MmapPartition(char* map, int* StrBegin, int* StrEnd, int Left, int Right) {
	int Pivot = Left;
	int IteratorFirst = Left - 1, 
		IteratorSecond = Right + 1;
	while (1) {
		do {IteratorFirst++;} while (compare(map, StrBegin, StrEnd, IteratorFirst, Pivot) < 0);
		do {IteratorSecond--;} while (compare(map, StrBegin, StrEnd, IteratorSecond, Pivot) > 0);
		if (IteratorFirst >= IteratorSecond) 
			return IteratorSecond;
		int tmpbegin = StrBegin[IteratorFirst],
			tmpend = StrEnd[IteratorFirst];
		StrBegin[IteratorFirst] = StrBegin[IteratorSecond];
		StrEnd[IteratorFirst] = StrEnd[IteratorSecond];
		StrBegin[IteratorSecond] = tmpbegin;
		StrEnd[IteratorSecond] = tmpend;
	}
}

void MmapQuickSort (char* map, int* StrBegin, int* StrEnd, int Left, int Right) {
	if (Left < Right) {
		int Middle = MmapPartition(map, StrBegin, StrEnd, Left, Right);
		MmapQuickSort(map, StrBegin, StrEnd, Left, Middle);
		MmapQuickSort(map, StrBegin, StrEnd, Middle + 1, Right);
	}
}

void MmapSort(int NumberStrings, const char* FileName) {
	int FileDescriptor = open(FileName, O_RDWR);
	if (FileDescriptor < 0)
		PrintError("Can't open the file at MmapSort!", 2);
	struct stat SizeBinary;
	fstat(FileDescriptor, &SizeBinary);
	char* map = (char*)mmap(NULL, SizeBinary.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, FileDescriptor, 0);
	int* StrBegin = (int*)malloc(NumberStrings * sizeof(int));
	int* StrEnd = (int*)malloc(NumberStrings * sizeof(int));
	if (map == NULL || StrBegin == NULL || StrEnd == NULL) 
		PrintError("Error Memory Allocation at MmapSort!", 4);
	for (int i = 0, j = 0, begin = 0; (i < NumberStrings) && (j < SizeBinary.st_size); ++j) {
		if (map[j] == '\n') {
			StrBegin[i] = begin;
			StrEnd[i] = j;
			++i;
			begin = j + 1;
		}
	}
	MmapQuickSort(map, StrBegin, StrEnd, 0, NumberStrings - 1);
	for (int i = 0; i < NumberStrings; ++i)
		for (int j = StrBegin[i]; j <= StrEnd[i]; ++j)
			printf("%c", map[j]);
	free(StrBegin);
	free(StrEnd);
	munmap(map, SizeBinary.st_size);
	close(FileDescriptor);
	exit(0);
}

int Sanitize(const char* FileName, int NumberStrings) {
    FILE* Input;
    Input = fopen(FileName, "r");
	if (Input == NULL) 
		PrintError("Cannot open the file!", 2);
    int Count = 0;
    char c;
    while ((c = fgetc(Input)) != EOF) {
        if (c == '\n')
            ++Count;
        if (Count >= NumberStrings)
			break;
    }
    if (Count < NumberStrings) PrintError("Invalid Number of strings!", 1);
    if (Count < NumberStrings)
		NumberStrings = Count;
    fclose(Input);
    return NumberStrings;
}
		
int main(int argc, char** argv) {
	if (argc < 4) 
		PrintError("Invalid number of arguments!", 1);
	FILE* Input;
	int NumberStrings = atoi(argv[1]);
	const char* FileName = (const char*)argv[2];
	char* SortName = argv[3];
	NumberStrings = Sanitize(FileName, NumberStrings);
	if (strcmp(SortName, "mmap") == 0)
		MmapSort(NumberStrings, FileName);
	Input = fopen(FileName, "r");
	if (Input == NULL) 
		PrintError("Invalid argument #2 (File name)!", 2);
	char** Strings = (char**)malloc(NumberStrings * sizeof(char*));
	if (Strings == NULL) 
		PrintError("Error Memory Allocation at main!", 4);
	for (int i = 0; i < NumberStrings; ++i) {
		Strings[i] = (char*)malloc(256 * sizeof(char));
		if (fgets(Strings[i], 256, Input) == NULL)
			PrintError("Reading Error!", 4);
	}
	if (strcmp(SortName, "bubble") == 0)
		BubbleSort(Strings, NumberStrings);
	else if (strcmp(SortName, "insertion") == 0)
		InsertionSort(Strings, NumberStrings);
	else if (strcmp(SortName, "merge") == 0)
		MergeSort(Strings, 0, NumberStrings);
	else if (strcmp(SortName, "quick") == 0)
		QuickSort(Strings, 0, NumberStrings - 1);
	else if ((strcmp(SortName, "heap") == 0) || (strcmp(SortName, "radix") == 0))
		HeapSort(Strings, NumberStrings);
	else
		PrintError("Invalid argument #3 (Sorting algorithm name)!", 1);
	for(int i = 0; i < NumberStrings; ++i)
		printf("%s", Strings[i]);
	fclose(Input);
	for (int i = 0; i < NumberStrings; ++i)
		free(Strings[i]);
	free(Strings);
    return 0;
}
