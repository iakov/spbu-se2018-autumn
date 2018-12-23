#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH_BUFF 10000
char **str;

void swapLines(char* str[], int firstInd, int secondInd)
{
    char *temp = str[firstInd];
    str[firstInd] = str[secondInd];
    str[secondInd] = temp;
}

void bubbleSort(char* str[], int amountString)
{
for (int i = amountString-1; i >= 0; i--)
  {
    int verifSwap = 1;
    for (int j = 0; j<i; j++)
    {
        if (strcmp(str[j], str[j+1]) > 0)
        {
            swapLines(str, j, j+1);
            verifSwap = 0;
        }
    }
    if (verifSwap)
    {
        break;
    }
  }
}

void insertionSort(char* str[], int amountString)
{
   int i, j;
   char *key;
   for (i = 1; i < amountString; i++)
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
    int firstSub, secondSub, finalInd;
    int lenOfLeft = mid - left + 1;
    int lenOfRight = right - mid;

    char **Left = malloc(lenOfLeft*sizeof(char*));
    char **Right = malloc(lenOfRight*sizeof(char*));

    if (Left == NULL || Right == NULL)
    {
        printf("Cannot allocate extra memory for merge sort");
        exit(4);
    }

    for (firstSub = 0; firstSub < lenOfLeft; firstSub++)
    {
        Left[firstSub] = str[left + firstSub];
    }

    for (secondSub = 0; secondSub < lenOfRight; secondSub++)
    {
        Right[secondSub] = str[mid + 1+ secondSub];
    }

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
        int mid = left+(right-left)/2;

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

void heapify(char* str[], int amountString, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < amountString && strcmp(str[l], str[largest]) > 0)
    {
        largest = l;
    }

    if (r < amountString && strcmp(str[r], str[largest]) > 0)
    {
        largest = r;
    }

    if (largest != i)
    {
        swapLines(str, i, largest);
        heapify(str, amountString, largest);
    }
}
void heapSort(char *str[], int amountString)
{
    for (int i = amountString / 2 - 1; i >= 0; i--)
    {
        heapify(str, amountString, i);
    }

    for (int i = amountString - 1; i >= 0; i--)
    {
        swapLines(str, 0, i);
        heapify(str, i, 0);
    }
}

int main(int argc, char *argv[])
{
    int amountString = atoi(argv[1]);
    char *fileName = argv[2];
    char *algName = argv[3];
    if (argc < 4)
    {
        printf("Invalid number of parameters");
        exit(1);
    }

    FILE *myFile;
    if ((myFile = fopen(fileName, "r")) == NULL)
    {
        printf("Cannot open file");
        exit(2);
    }

    char **str = malloc(amountString*sizeof(char*));
    if (str == NULL)
    {
        printf("Cannot allocate memory for array of lines");
        exit(4);
    }
    char buffer[LENGTH_BUFF] ;

    for (int numStr = 0; numStr < amountString; numStr++){

        if (fgets(buffer, LENGTH_BUFF, myFile) == NULL)
        {
            amountString = numStr;
            break;
        }

        str[numStr] = malloc((strlen(buffer)+1)*sizeof(char));
        if (str[numStr] == NULL)
        {
            printf("Cannot allocate memory for line");
            exit(4);
        }
        strcpy(str[numStr], buffer);
    }
    fclose(myFile);

    if ( 0 == strcmp("bubble", algName) )
    {
        bubbleSort(str, amountString);
    }
    else if ( 0 == strcmp("insertion", algName) )
    {
        insertionSort(str, amountString);
    }
    else if ( 0 == strcmp("merge", algName) )
    {
        mergeSort(str, 0, amountString-1);
    }
    else if ( 0 == strcmp("quick", algName) )
    {
        quickSort(str, 0, amountString-1);
    }
    else if ( 0 == strcmp("radix", algName) )
    {
        heapSort(str, amountString);
    }
    else
    {
        for (int currLine = 0; currLine < amountString; currLine++)
        {
            free(str[currLine]);
        }
        free(str);
        printf("Invalid name of algorithm");
        exit(1);
    }

    for (int numStr=0; numStr<amountString; numStr++)
    {
        printf("%s", str[numStr]);
        free(str[numStr]);
    }
    free(str);
    return 0;
}
