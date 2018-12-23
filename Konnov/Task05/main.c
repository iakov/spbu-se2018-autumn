#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int sizeFile, i, j;

int sortSelection(char *name)
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

void errorMessage(char *message)
{
	printf("//\n%s\n//\n", message);
}

void bubbleSort(char **bubbleText,int n)
{
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
	if(NULL == tmp)
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
		quickSort(quickText, left, ptrR);
	}

	if(ptrL < right)
	{
		quickSort(quickText, ptrL, right);
	}
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
	if(NULL == file)
	{
		errorMessage("cant open file");
		exit(2);
	}
	sizeFile = atoi(argv[1]);
	int strLength = 20;

	char **text = (char **) malloc(sizeFile * sizeof(char *));
	char *buf = (char *) malloc(strLength * sizeof(char));
	if(NULL == text)
	{
		errorMessage("cant allocate memory for text in main function");
		exit(4);
	}
	if(NULL == buf)
	{
		errorMessage("cant allocate memory for buf in main function");
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
			errorMessage("cant allocate memory for a string of text in main function");
			exit(4);
		}
		strcpy(text[i], buf);
	} 
	free(buf);
	
	switch(sortSelection(argv[3]))
	{
		case 1:
				bubbleSort(text, realSize);
				break;
		case 2:
				insertionSort(text, realSize);
				break;
		case 3:
				mergeSort(text, realSize);
				break;
		case 4:
				quickSort(text, 0, realSize - 1);
				break;
		case 5:
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

	for(i = 0; i < sizeFile; i++)
	{
		free(text[i]);
	}	
	free(text);
	fclose(file);

	return 0;
}
