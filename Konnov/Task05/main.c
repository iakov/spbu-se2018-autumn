#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int sizeFile;
enum sorts {bubble, insertion, merge, quick, radix, other};


enum sorts sortSelection(char *name)
{
	enum sorts res = other;

	if(strcmp("bubble", name) == 0)
	{
		res = bubble;
	}
	if(strcmp("insertion",name) == 0)
	{
		res = insertion;
	}
	if(strcmp("merge",name) == 0)
	{
		res = merge;
	}
	if(strcmp("quick",name) == 0)
	{
		res = quick;
	}
	if(strcmp("radix",name) == 0)
	{
		res = radix;
	}

	return res;
}

void errorMessage(char *message)
{
	printf("//\n%s\n//\n", message);
}

void bubbleSort(char **bubbleText,int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for(j = 0; j < n - i - 1; j++)
		{
			if (strcmp(bubbleText[j], bubbleText[j + 1]) > 0)
			{
				char *tmp = bubbleText[j];
				bubbleText[j] = bubbleText[j + 1];
				bubbleText[j + 1] = tmp;
			}
		}
	}
}

void insertionSort(char **insertionText, int n)
{
	int i, j;
	for(i = 1; i < n; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
        	if(strcmp(insertionText[j], insertionText[j + 1]) > 0)
			{
				char *tmp = insertionText[j];
				insertionText[j] = insertionText[j + 1];
				insertionText[j + 1] = tmp;
			}
		}
	}
}

void mergeSort(char **mergeText, int n)
{
	if(n <= 1)
	{
		return;
	}

	int mid = n / 2;

	mergeSort(mergeText, mid);
	mergeSort(mergeText + mid, n - mid);

	char **tmp = (char **) malloc(n * sizeof(char *));
	if(tmp == NULL)
	{
		errorMessage("cant allocate memory for tmp in mergesort procedure");
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
	
	int i;
	for(i = 0; i < n; i++)
	{
		mergeText[i] = tmp[i];
	}
	free(tmp);
}

void quickSort(char **quickText, int left, int right)
{
	if(left >= right)
	{
		return;
	}

	int ptrL = left, ptrR = right;
	char *mid = quickText[(left + right) / 2];

	while(ptrL <= ptrR)
	{
		while(strcmp(mid, quickText[ptrL]) > 0)
		{
			ptrL++;
		}
		while(strcmp(quickText[ptrR], mid) > 0)
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
	
	quickSort(quickText, left, ptrR);
	quickSort(quickText, ptrL, right);
}

void heap(char **textInHeap, int amount, int i)
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
		heap(textInHeap, amount, largest);
	}
}

void heapSort(char **heapText, int n)
{
	int i;
	for(i = n / 2 - 1; i >= 0; i--)
	{
		heap(heapText, n, i);
	}

	for(i = n - 1; i >= 0; i--)
	{
		char *tmp = heapText[0];
		heapText[0] = heapText[i];
		heapText[i] = tmp;
		heap(heapText, i, 0);
	}
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		errorMessage("wrong number of arguments");
		exit(1);
	}
	FILE *file = fopen(argv[2], "r");
	if(file == NULL)
	{
		errorMessage("cant open file");
		exit(2);
	}
	sizeFile = atoi(argv[1]);
	int strLength = 20;

	char **text = (char **) malloc(sizeFile * sizeof(char *));
	char *buf = (char *) malloc(strLength * sizeof(char));
	if(text == NULL)
	{
		errorMessage("cant allocate memory for text in main function");
		exit(4);
	}
	if(buf == NULL)
	{
		errorMessage("cant allocate memory for buf in main function");
		exit(4);
	}
	
	int i;
	int realSize = 0; //real size of text
	for(i = 0; i < sizeFile; i++)
	{
		if(fgets(buf, strLength, file) == NULL)
		{
			break;
		}
		realSize++;
		text[i] =(char *) malloc((strlen(buf) + 1) * sizeof(char));
		if(text[i] == NULL)
		{
			errorMessage("cant allocate memory for a string of text in main function");
			exit(4);
		}
		strcpy(text[i], buf);
	} 
	free(buf);
	
	argv[3][0] = tolower(argv[3][0]);
	switch(sortSelection(argv[3]))
	{
		case bubble:
				bubbleSort(text, realSize);
				break;
		case insertion:
				insertionSort(text, realSize);
				break;
		case merge:
				mergeSort(text, realSize);
				break;
		case quick:
				quickSort(text, 0, realSize - 1);
				break;
		case radix:
				heapSort(text, realSize);
				break;
		default:
				errorMessage("Unknown algorithm");
				exit(1);
				break;
	}

	for(i = 0; i < realSize; i++)
	{
		printf("%s", text[i]);
	}

	for(i = 0; i < realSize; i++)
	{
		free(text[i]);
	}	
	free(text);
	fclose(file);

	return 0;
}
