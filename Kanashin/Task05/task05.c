#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swapLines(char* str[], int n, int m){
    char *temp = str[n];
    str[n] = str[m];
    str[m] = temp;
}

void bubbleSort(char* str[], int size){
for (int i = size-1; i >= 0; i--)
  {
    int flagSwap = 1;
    for (int j = 0; j<i; j++)
    {
      if (strcmp(str[j], str[j+1]) > 0){
        swapLines(str, j, j+1);
        flagSwap = 0;
      }
    }
    if (flagSwap)
        break;
  }
}

void insertionSort(char* str[], int n)
{
   int i, j;
   char *key;
   for (i = 1; i < n; i++)
   {
       key = str[i];
       j = i-1;
       while (j >= 0 && strcmp(str[j] ,key) >0)
       {
           str[j+1] = str[j];
           j = j-1;
       }
       str[j+1] = key;
   }
}

void merge(char *str[], int left, int mid, int right)
{
    long int firstSub, secondSub, finalInd;
    long int lenOfLeft = mid - left + 1;
    long int lenOfRight = right - mid;

    char **Left = malloc(lenOfLeft*sizeof(char*));
    char **Right = malloc(lenOfRight*sizeof(char*));

    for (firstSub = 0; firstSub < lenOfLeft; firstSub++)
        Left[firstSub] = str[left + firstSub];
    for (secondSub = 0; secondSub < lenOfRight; secondSub++)
        Right[secondSub] = str[mid + 1+ secondSub];

    firstSub = 0;
    secondSub = 0;
    finalInd = left;
    while (firstSub < lenOfLeft && secondSub < lenOfRight)
    {
        if (strcmp(Left[firstSub], Right[secondSub]) < 0)
        {
            str[finalInd] = Left[firstSub];
            firstSub++;
        }
        else
        {
            str[finalInd] = Right[secondSub];
            secondSub++;
        }
        finalInd++;
    }


    while (firstSub < lenOfLeft)
    {
        str[finalInd] = Left[firstSub];
        firstSub++;
        finalInd++;
    }


    while (secondSub < lenOfRight)
    {
        str[finalInd] = Right[secondSub];
        secondSub++;
        finalInd++;
    }
    free(Right);
    free(Left);
}

void mergeSort(char *str[], int left, int right)
{
    if (left < right)
    {
        long int mid = left+(right-left)/2;

        mergeSort(str, left, mid);
        mergeSort(str, mid+1, right);

        merge(str, left, mid, right);
    }
}
int partition(char *str[], int low, int high)
{
    char *pivot = str[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (strcmp(str[j],pivot) < 0)
        {
            i++;
            swapLines(str, i, j);
        }
    }
    swapLines(str, i+1, high);
    return (i + 1);
}
void quickSort(char* str[], int low, int high)
{
    if (low < high)
    {
        int parInd = partition(str, low, high);

        quickSort(str, low, parInd - 1);
        quickSort(str, parInd + 1, high);
    }
}

void heapify(char* str[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && strcmp(str[l], str[largest]) > 0)
        largest = l;

    if (r < n && strcmp(str[r], str[largest]) > 0)
        largest = r;

    if (largest != i)
    {
        swapLines(str, i, largest);
        heapify(str, n, largest);
    }
}

void heapSort(char *str[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(str, n, i);

    for (int i=n-1; i>=0; i--)
    {
        swapLines(str, 0, i);
        heapify(str, i, 0);
    }
}

int main(int argc, char *argv[])
{
    int amountString = atoi(argv[1]);
    char *fileName = argv[2];
    char algName = argv[3][0];

    FILE *myFile = fopen(fileName, "r");
    if (myFile == NULL){
        printf("Cannot open file");
        return 1;
    }

    int lenOfStr = 1;
    char **str = (char**) malloc(amountString*sizeof(char*));
    for (int numStr=0; numStr<amountString; numStr++){
        str[numStr] = malloc(lenOfStr*sizeof(char));
        for (int currLenOfCurrStr=0; (str[numStr][currLenOfCurrStr] = fgetc(myFile)) != '\n'; currLenOfCurrStr++){
            if (currLenOfCurrStr+1>lenOfStr){
                lenOfStr *=2;
                str[numStr] = (char*) realloc(str[numStr], lenOfStr*sizeof(char));
            }
        }
    }
    fclose(myFile);

    switch (algName){
        case 'b':
            bubbleSort(str, amountString);
            break;
        case 'i':
            insertionSort(str, amountString);
            break;
        case 'm':
            mergeSort(str, 0, amountString-1);
            break;
        case 'q':
            quickSort(str, 0, amountString-1);
            break;
        case 'h':
            heapSort(str, amountString);
            break;
        default:
            break;
    }

    for (int numStr=0; numStr<amountString; numStr++){
        printf("%s", str[numStr]);
        free(str[numStr]);
    }
    free(str);
    return 0;
}
