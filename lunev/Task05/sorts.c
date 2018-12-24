#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_LENGTH 10000
void swapStrings (char **str, int first, int second)
{
    char *tmp = str[first];
    str[first] = str[second];
    str[second] = tmp;
}

void bubbleSort (char ** str, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (strcmp(str[j], str[j+1]) > 0)
                swapStrings(str, j, j+1);
}

void insertionSort (char ** str, int size)
{
    char *temp;
    for (int i = 1; i < size; i++)
    {
        temp = str[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (strcmp(temp, str[j]) > 0) break;
            str[j + 1] = str[j];
            str[j] = temp;
        }
    }
}


void mergeSort(char **str, int left, int right)
{
  if (left == right-1)
  {
      return;
  }
  int mid = (left + right) / 2;
  mergeSort(str, left, mid);
  mergeSort(str, mid, right);

  char **tmparray = (char **) malloc((right-left) * sizeof(char *));
  if (tmparray == NULL)
  {
      printf("Failed to allocate memory\n");
      exit(4);
  }
  int firstpath = left;
  int secondpath = mid;
  int i=0, end=0;
  while (firstpath<mid && secondpath<right)
  {
      if (strcmp(str[secondpath], str[firstpath]) > 0)
      {
        tmparray[i] = str[firstpath];
        i++;
        firstpath++;
        end = firstpath;
      }
      else
      {
        tmparray[i] = str[secondpath];
        i++;
        secondpath++;
        end = secondpath;
      }
  }

  if (end == firstpath)
  {
    while (secondpath<right)
    {
        tmparray[i] = str[secondpath];
        i++;
        secondpath++;
    }
  }
  else
  {
    while (firstpath<mid)
    {
        tmparray[i] = str[firstpath];
        i++;
        firstpath++;
    }
  }

  for (i = 0; i < right - left; i++)
  {
    str[left+i] = tmparray[i];
  }

  free (tmparray);
}

void quickSort(char **str, int left, int right)
{
    if (left < right)
    {
        int leftptr = left, rightptr = right;
        char *middle = str[(leftptr + rightptr) / 2];
        do
        {
            while (strcmp(middle, str[leftptr]) > 0) leftptr++;
            while (strcmp(str[rightptr], middle) > 0) rightptr--;
            if (leftptr <= rightptr)
            {
                swapStrings (str, leftptr, rightptr);
                leftptr++;
                rightptr--;
            }
        } while (leftptr <= rightptr);
        quickSort(str, left, rightptr);
        quickSort(str, leftptr, right);
    }
}

void formHeap(char **str, int root, int bottom)
{
  int maxChild;
  int done = 0;

  while ((root * 2 <= bottom) && (!done))
  {
    if (root * 2 == bottom)
      maxChild = root * 2;
    else if (strcmp(str[root*2], str[root*2+1]) > 0)
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
    if (strcmp(str[maxChild], str[root]) > 0)
    {
      swapStrings(str, root, maxChild);
      root = maxChild;
    }
    else
      done = 1;
  }
}

void heapSort(char **str, int size)
{
  int i;
  for (i = (size / 2) - 1; i >= 0; i--)
    formHeap(str, i, size - 1);
  for (i = size - 1; i >= 1; i--)
  {
    swapStrings(str, 0, i);
    formHeap(str, 0, i - 1);
  }
}

int main (int argc, char *argv[])
{
  if (argc != 4)
  {
      printf("wrong number of arguments!\n");
      exit(1);
  }
  FILE *file = fopen(argv[2], "r");
  if (file == NULL)
  {
      printf("Unable to open file\n");
      exit(2);
  }
  int number_str = atoi (argv[1]);
  char **str = (char **) malloc (number_str*sizeof(char *));
  if (str == NULL)
  {
      printf("Failed to allocate memory\n");
      exit(4);
  }

  char buffer[MAX_LENGTH];
  for (int i = 0; i < number_str; i++){
      if (fgets(buffer, MAX_LENGTH, file) == NULL)
      {
          number_str = i;
          break;
      }
      str[i] = malloc((strlen(buffer))*sizeof(char));
      if (str[i] == NULL)
      {
          printf("Failed to allocate memory\n");
          exit(4);
      }
      strcpy(str[i], buffer);
  }
  fclose(file);

  if (strcmp(argv[3], "bubble") == 0)
  {
      bubbleSort(str, number_str);
  }
  else if (strcmp(argv[3], "insertion") == 0)
  {
      insertionSort(str, number_str);
  }
  else if (strcmp(argv[3], "merge") == 0)
  {
      mergeSort(str, 0, number_str);
  }
  else if (strcmp(argv[3], "quick") == 0)
  {
      quickSort(str, 0, number_str-1);
  }
  else if (strcmp(argv[3], "radix") == 0)
  {
      heapSort(str, number_str);
  }
  else
  {
      for (int i = 0; i < number_str; ++i)
        free(str[i]);
      free(str);
      printf("wrong algorithm name\n");
      exit(1);
  }

  for (int i=0; i<number_str; i++)
  {
      printf("%s", str[i]);
      free(str[i]);
  }
  free(str);

  return 0;
}
