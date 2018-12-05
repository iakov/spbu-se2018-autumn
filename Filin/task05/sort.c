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
  int ptrleft = left, ptrright = right;
  char* mid = string[(left + right) / 2];
  while (ptrleft <= ptrright)
   {
    while (strcmp(mid, string[ptrleft]) == 1)
      ptrleft++;
    while (strcmp(mid, string[ptrright]) == -1)
      ptrright--;
    if (ptrleft <= ptrright)
     {
      char *buf = string[ptrleft];
      string[ptrleft] = string[ptrright];
      string[ptrright] = buf;
      ptrleft++;
      ptrright--;
     }
   }
  if (left < ptrright)
    quicksort (string, left, ptrright);
  if (ptrleft < right)
    quicksort (string, ptrleft, right);
}

void mergesort (char** string, int left, int right)
{
 if (left == right - 1) return;
 int mid = (left + right) / 2;
 int i;
 mergesort (string, left, mid);
 mergesort (string, mid, right);
 char** buf = malloc((right - left) * sizeof(char*));
 int ptrleft = left, ptrright = mid, newptr = 0;
 while (ptrleft < mid && ptrright < right)
   if (strcmp (string[ptrright], string[ptrleft]) == 1)
    {
     buf[newptr] = string [ptrleft];
     newptr++;
     ptrleft++;
    }
   else
    {
     buf[newptr] = string [ptrright];
     newptr++;
     ptrright++;
    }
 while (ptrleft < mid)
  {
   buf[newptr] = string [ptrleft];
   newptr++;
   ptrleft++;
  }
 while (ptrright < right)
  {
   buf[newptr] = string [ptrright];
   newptr++;
   ptrright++;
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
 int i, n;
 n = atoi(argv[1]);
 for (i = 0; i < n; ++i)
  {
   string[i] = (char*) malloc(1025 * sizeof(char));
   fgets(string[i], 1024, file);
  }
 switch (argv[3][0])
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
