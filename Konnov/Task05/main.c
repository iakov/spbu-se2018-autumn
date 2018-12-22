#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int sizeFile, i, j;

int SortSelection(char *name)
{
	int res = 0;

	if((strcmp("bubble",name) == 0) || (strcmp("Bubble",name) == 0))
	{
		res = 1;
	}
	if((strcmp("insertion",name) == 0) || (strcmp("Insertion",name) == 0))
	{
		res = 2;
	}
	if((strcmp("merge",name) == 0) || (strcmp("Merge",name) == 0))
	{
		res = 3;
	}
	if((strcmp("quick",name) == 0) || (strcmp("Quick",name) == 0))
	{
		res = 4;
	}
	if((strcmp("radix",name) == 0) || (strcmp("Radix",name) == 0))
	{
		res = 5;
	}

	return res;
}

void ErrorMessage(char *message)
{
	printf("//\n%s\n//", message);
}

void BubbleSort(char **bubbleText)
{
	for (i = 0; i < sizeFile; i++)
	{
		for(j = 0; j < sizeFile - i - 1; j++)
		{
			if (strcmp(bubbleText[j], bubbleText[j + 1]) == 1)
			{
				char *tmp = bubbleText[j];
				bubbleText[j] = bubbleText[j + 1];
				bubbleText[j + 1] = tmp;
			}
		}
	}
}

void InsertionSort(char **insertionText)
{
	for(i = 1; i < sizeFile; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
	        	if(strcmp(insertionText[j], insertionText[j + 1]) == 1)
			{
				char *tmp = insertionText[j];
				insertionText[j] = insertionText[j + 1];
				insertionText[j + 1] = tmp;
			}
		}
	}
}

void MergeSort(char **mergeText, int n)
{
	if(n <= 1)
	{
		return;
	}

	int mid = n / 2;

	MergeSort(mergeText, mid);
	MergeSort(mergeText + mid, n - mid);

	char **tmp = (char **) malloc(n * sizeof(char *));
	if(NULL == tmp)
	{
		ErrorMessage("cant allocate memory for tmp in mergesort procedure");
		exit(4);
	}

	int ptrL = 0, ptrR = mid;
	int ptr = 0;

	while(ptrL < mid)
	{
		if((ptrR >= n) || (strcmp(mergeText[ptrR], mergeText[ptrL]) > 0))
		{
			tmp[ptr++] = mergeText[ptrL++];
		}
		else
		{
			tmp[ptr++] = mergeText[ptrR++];
		}
	}

	while(ptrR < n)
	{
		tmp[ptr++] = mergeText[ptrR++];
	}

	for(i = 0; i < n; i++)
	{
		mergeText[i] = tmp[i];
	}
	free(tmp);
}

void QuickSort(char **quickText, int left, int right)
{
	if(left >= right)
	{
		return;
	}

	int ptrL = left, ptrR = right;
	char *mid = quickText[(left + right) / 2];

	while(ptrL <= ptrR)
	{
		while(strcmp(mid, quickText[ptrL]) == 1)
		{
			ptrL++;
		}
		while(strcmp(quickText[ptrR], mid) == 1)
		{
			ptrR--;
		}
		if(ptrL <= ptrR)
		{
			char *tmp = quickText[ptrL];
			quickText[ptrL] = quickText[ptrR];
			quickText[ptrR] = tmp;
			ptrL++;
			ptrR--;
		}
	}

	if(left < ptrR)
	{
		QuickSort(quickText, left, ptrR);
	}

	if(ptrL < right)
	{
		QuickSort(quickText, ptrL, right);
	}
}

void Heap(char **textInHeap, int amount, int i)
{
	int largest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if(left < amount && strcmp(textInHeap[left], textInHeap[largest]) > 0)
	{
		largest = left;
	}

	if(right < amount && strcmp(textInHeap[right], textInHeap[largest]) > 0)
	{
		largest = right;
	}

	if(largest != i)
	{
		char *tmp = textInHeap[i];
		textInHeap[i] = textInHeap[largest];
		textInHeap[largest] = tmp;
		Heap(textInHeap, amount, largest);
	}
}

void HeapSort(char **heapText, int n)
{
	for(i = n / 2 - 1; i >= 0; i--)
	{
		Heap(heapText, n, i);
	}

	for(i = n - 1; i >= 0; i--)
	{
		char *tmp = heapText[0];
		heapText[0] = heapText[i];
		heapText[i] = tmp;
		Heap(heapText, i, 0);
	}
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		ErrorMessage("wrong number of arguments");
		exit(1);
	}
	FILE *file = fopen(argv[2], "r");
	if(NULL == file)
	{
		ErrorMessage("cant open file");
		exit(2);
	}
	sizeFile = atoi(argv[1]);
	int strLength = 10000;

	char **text = (char **) malloc(sizeFile * sizeof(char *));
	char *buf = (char *) malloc(strLength * sizeof(char));
	if(NULL == text)
	{
		ErrorMessage("cant allocate memory for text in main function");
		exit(4);
	}
	if(NULL == buf)
	{
		ErrorMessage("cant allocate memory for buf in main function");
		exit(4);
	}
	
	int realSize = 0; //real size of text
	for(i = 0; i < sizeFile; i++)
	{
		if(NULL == fgets(buf, strLength, file))
		{
			break;
		}
		realSize++;
		text[i] =(char *) malloc((strlen(buf) + 1) * sizeof(char));
		if(NULL == text[i])
		{
			ErrorMessage("cant allocate memory for a string of text in main function");
			exit(4);
		}
		strcpy(text[i], buf);
	} 
	free(buf);
	sizeFile = realSize;
	if(NULL == realloc(text, sizeFile * sizeof(char *)))
	{
		ErrorMessage("Cant reallocate memory for text in main function");
		exit(4);
	}

	switch(SortSelection(argv[3]))
	{
		case 1:
				BubbleSort(text);
				break;
		case 2:
				InsertionSort(text);
				break;
		case 3:
				MergeSort(text, sizeFile);
				break;
		case 4:
				QuickSort(text, 0, sizeFile - 1);
				break;
		case 5:
				HeapSort(text, sizeFile);
				break;
		default:
				ErrorMessage("Unknown algorithm");
				exit(1);
				break;
	}

	for(i = 0; i < sizeFile; i++)
	{
		printf("%s", text[i]);
	}

	free(text);
	fclose(file);

	return 0;
}
