#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string[100000000];

void bubblesort(char **string, int n)
{
 int i, j;
 for (i = 0; i < n; i++)
   for (j = 0; j < n - i - 1; j++)
     if (strcmp(string[j], string[j + 1]) == 1)
      {
       char *buf = string[j];
       string[j] = string[j + 1];
       string[j + 1] = buf;
      }
}

void insertionsort(char **string, int n)
{
 int i, j;
 for (i = 1; i < n; i++)
   for (j = i - 1; j >= 0; j--)
     if (strcmp(string[j], string[j + 1]) == 1)
      {
       char *buf = string[j];
       string[j] = string[j + 1];
       string[j + 1] = buf;
      }
}

void quicksort(char **string, int left, int right)
{
  if (left >= right) return;
  int left_ptr = left, right_ptr = right;
  char* mid = string[(left + right) / 2];
  while (left_ptr <= right_ptr)
   {
    while (strcmp(mid, string[left_ptr]) == 1)
      left_ptr++;
    while (strcmp(mid, string[right_ptr]) == -1)
      right_ptr--;
    if (left_ptr <= right_ptr)
     {
      char *buf = string[left_ptr];
      string[left_ptr] = string[right_ptr];
      string[right_ptr] = buf;
      left_ptr++;
      right_ptr--;
     }
   }
  if (left < right_ptr)
    quicksort (string, left, right_ptr);
  if (left_ptr < right)
    quicksort (string, left_ptr, right);
}

void mergesort (char** string, int left, int right)
{
 if (left >= right - 1) return;
 int mid = (left + right) / 2;
 int i;
 mergesort (string, left, mid);
 mergesort (string, mid, right);
 char** buf = malloc((right - left) * sizeof(char*));
 int left_ptr = left, right_ptr = mid, new_ptr = 0;
 while (left_ptr < mid && right_ptr < right)
   if (strcmp (string[right_ptr], string[left_ptr]) == 1)
    {
     buf[new_ptr] = string [left_ptr];
     new_ptr++;
     left_ptr++;
    }
   else
    {
     buf[new_ptr] = string [right_ptr];
     new_ptr++;
     right_ptr++;
    }
 while (left_ptr < mid)
  {
   buf[new_ptr] = string [left_ptr];
   new_ptr++;
   left_ptr++;
  }
 while (right_ptr < right)
  {
   buf[new_ptr] = string [right_ptr];
   new_ptr++;
   right_ptr++;
  }
 for (i = left; i < right; i++)
   string[i] = buf[i - left];
 free(buf);
}

void heap (char** string, int i, int n)
{
 int max = i;
 while (1)
  {
   int child = 2 * i + 1;
   if (child < n && strcmp(string[child], string[max]) == 1)
     max = child;
   child++;
   if (child < n && strcmp(string[child], string[max]) == 1)
     max = child;
   if(max == i) break;
   else
    {
     char *buf = string[max];
     string[max] = string[i];
     string[i] = buf;
     i = max;
    }
  }
}

void heapsort (char** string, int n)
{
 int i;
 for (i = n / 2; i >= 0; i--)
   heap(string, i, n);
 for (i = n - 1; i >= 1; i--)
  {
   char *buf = string[0];
   string[0] = string[i];
   string[i] = buf;
   heap(string, 0, i);
  }
}


int main (int argc, char* argv[])
{
 FILE *file = fopen(argv[2], "r");
 if (file == NULL)
  {
   fprintf(stderr, "Error! Can not open file.");
   return 0;
  }
 int i, n;
 n = atoi(argv[1]);
 for (i = 0; i < n; ++i)
  {
   string[i] = (char*) malloc(1025 * sizeof(char));
   fgets(string[i], 1024, file);
  }
 char* namesort = argv[3];
 switch (namesort[0])
  {
        case 'b': {
            bubblesort(string, n);
            break;
        }
        case 'i': {
            insertionsort(string, n);
            break;
        }
        case 'q': {
            quicksort(string, 0, n - 1);
            break;
        }
        case 'm': {
            mergesort(string, 0, n);
            break;
        }
        case 'h': {
            heapsort(string, n);
            break;
        }
        default: break;
  }
 for (i = 0; i < n; i++)
   printf("%s\n", string[i]);
 for (i = 0; i < n; i++)
   free (string[i]);
 fclose (file);
 return 0;
}
