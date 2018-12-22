#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define startn 200
#define startlen 10

char **strings;
int *lengths;
//used to compare strings with different lengths
char get_ith_symbol(char* a,int len ,int i)
{
    if (i>=len)
    {
        return 0;
    }
    else return a[i];
}

//swapping strings and their lengths
void swap(int index1, int index2)
{
    char* temp = strings[index1];
    strings[index1] = strings[index2];
    strings[index2] = temp;
    int temp_len=lengths[index1];
    lengths[index1]=lengths[index2];
    lengths[index2]=temp_len;
}
// strlen is not viable,because unused memory is malloced, so it doesnt work properly
// hence cmp is used
char cmp(char* a, char* b,int len_a,int len_b)
{
    for (int i = 0; i < max(len_a,len_b); i++)
    {
        if (get_ith_symbol(a,len_a,i) > get_ith_symbol(b,len_b,i))
        {
        return 1;
        }
        if (get_ith_symbol(b,len_b,i) > get_ith_symbol(a,len_a,i))
        {
        return 0;
        }
    }
    return 1;
}

void bubbleSort(int n)
{
    int n1 = n - 1;
    bool swapped;
    do
    {
        swapped = 0;
        for (int i = 0; i < n1; i++)
        {
            if (cmp(strings[i],strings[i+1],lengths[i],lengths[ i + 1]))
            {
                swap(i, i + 1);
                swapped = 1;
            }
        }
        n1--;
    }
    while (swapped);
}

void insertionSort(int n)
{
    int i = 1;
    while (i < n)
    {
        int j = i;
        while ((j > 0) &&
              (cmp(strings[j],strings[j-1],lengths[j],lengths[ j - 1])))
        {
            swap(j, j - 1);
            j = j - 1;
        }
        i += 1;
    }

}

int partition(int low, int high)
{
    int pivot = high;    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (cmp(strings[pivot],strings[j],lengths[pivot],lengths[j]))
        {
            i++;
            swap(i, j);
            // increment index of smaller element
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

void startQuickSort(int low, int high)
{
    if (low < high)
    {

        int pi = partition(low, high);

        // Separately sort elements before
        // partition and after partition
        startQuickSort(low, pi - 1);
        startQuickSort(pi + 1, high);
    }
}

void quickSort(int low, int high)
{
    startQuickSort(low, high);
}

void merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;


    char** L=malloc(n1*sizeof(char*));
    if (L==NULL)
    {
        printf("Memory allocation error!");
        exit(4);
    }
    char** R=malloc(n2*sizeof(char*));
    if (R==NULL)
    {
        printf("Memory allocation error!");
        exit(4);
    }
    int* len1=malloc(n1*sizeof(int));
    int* len2=malloc(n2*sizeof(int));
    if (len1==NULL || len2==NULL)
    {
        printf("Memory allocation error!");
        exit(4);
    }

    for (i = 0; i < n1; i++)
    {
        L[i] = strings[l + i];
        len1[i]=lengths[l+i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = strings[m + 1 + j];
        len2[j]=lengths[m+1+j];
    }


    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (cmp(R[j],L[i],len2[j],len1[i]))
        {
            strings[k] = L[i];
            lengths[k]=len1[i];
            i++;
        }
        else
        {
            strings[k] = R[j];
            lengths[k]=len2[j];
            j++;
        }
        k++;
    }


    while (i < n1)
    {
        strings[k] = L[i];
        lengths[k]=len1[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        strings[k] = R[j];
        lengths[k]=len2[j];
        j++;
        k++;
    }
    free(L);
    free(R);
    free(len1);
    free(len2);
}

void startMergeSort( int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
       int m = l + (r - l) / 2;

        // Sort first and second halves
        startMergeSort(l, m);
        startMergeSort(m + 1, r);

        merge(l, m, r);
    }
}


void mergeSort(int l, int r)
{
    startMergeSort(l, r);
}

// A function to do counting sort of strings[] according to
// the digit represented by exp.
void countSort(int n, int num)
{
    char** output; // output stringsay
    output=malloc(sizeof(char*)*n);
    if (output==NULL)
    {
        printf("Memory allocation error!");
        exit(4);
    }
    int i, count[256] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
    {
        count[get_ith_symbol(strings[i],lengths[i],num)]++;
    }
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 256; i++)
    {
        count[i] += count[i - 1];
    }
    int* lens=malloc(n*sizeof(int));
    if (lens==NULL)
    {
        printf("Memory allocation error!");
        exit(4);
    }
    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        int index=get_ith_symbol(strings[i],lengths[i],num);
        output[count[index] - 1] = strings[i];
        (lens[count[index]-1])=lengths[i];
        count[get_ith_symbol(strings[i],lengths[i],num)]--;
    }

    // Copy the output array to strings[], so that strings[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
    {
        strings[i] = output[i];
        lengths[i]=lens[i];
    }
    free(output);
    free(lens);
}

// The main function to that sorts strings[] of size n using
// Radix Sort
int getMax(int n)
{
    int mx = lengths[0];
    for (int i = 1; i < n; i++)
    {
        if (lengths[i] > mx)
        {
            mx = lengths[i];
        }
    }
    return mx;
}
void radixsort(int n)
{

    // Find the maximum number to know number of symbols
    int maxlen = getMax(n);
    // Do counting sort for every symbol.
    for (int num = maxlen - 1; num >= 0; num--)
    {
        countSort(n, num);
    }

}
// A utility function to print an array
void print(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < lengths[i]; j++)
        {
            printf("%c", strings[i][j]);
        }
        printf("\n");
    }
}

// Driver program to test above functions
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Error! Incorrect number of parameters");
        return 1;
    }
    int true_n=atoi(argv[1]);
    int n = 0;
    FILE *fptr;
    fptr = fopen(argv[2], "r");
    if (fptr == NULL)
    {
        printf("Error! Incorrect file name %s",argv[2]);
        return 2;
    }
    char c;
    unsigned long long int current_n_for_malloc = startn;
    unsigned long long int current_string_len = startlen;
    strings = malloc(current_n_for_malloc * sizeof(char *));
    if (strings==NULL)
    {
        printf("Memory allocation error!");
        return 4;
    }
    char *current_string = malloc(startlen* sizeof(char));
    if (current_string==NULL)
    {
        printf("Memory allocation error!");
        return 4;
    }
    lengths = malloc(current_n_for_malloc * sizeof(int));
    if (lengths==NULL)
    {
        printf("Memory allocation error!");
        return 4;
    }
    int current_string_list_len = 0;
    while(n<true_n)
    {
        c = getc(fptr);
        if (c==EOF)
        {
            printf("Error! Unexpected EOF");
            return 3;
        }
        if (c == '\n')
        {
            strings[n] = current_string;
            lengths[n] = (current_string_list_len);
            n++;
            current_string_list_len = 0;
            current_string = malloc(startlen* sizeof(char));
            current_string_len = startlen;
            if (n + 1 > current_n_for_malloc)
            {
                current_n_for_malloc *= 2;
                strings = realloc(strings, current_n_for_malloc * sizeof(char *));
                if (strings==NULL)
                {
                    printf("Memory allocation error!");
                    return 4;
                }
                lengths = realloc(lengths, current_n_for_malloc * sizeof(int));
                if (lengths==NULL)
                {
                    printf("Memory allocation error!");
                    return 4;
                }
            }
        }
        else
        {
            current_string[current_string_list_len] = c;
            (current_string_list_len)++;
            if ((current_string_list_len) + 1 > current_string_len)
            {
                current_string_len *= 2;
                current_string = realloc(current_string, current_string_len);
                if (current_string==NULL)
                {
                    printf("Memory allocation error!");
                    return 4;
                }
            }
        }
    }
    if (current_string_list_len > 0)
    {
        strings[n] = current_string;
        lengths[n] = (current_string_list_len);
        n++;
    }
    char sort_name_first_symbol=argv[3][0];
    switch (sort_name_first_symbol)
    {
        case 'b':
        {
            if (strcmp(argv[3], "bubble") == 0)
            {
                bubbleSort(n);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                return 1;
            }
            break;
        }
        case 'i':
        {
            if (strcmp(argv[3], "insertion") == 0)
            {
                insertionSort(n);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                return 1;
            }
            break;
        }
        case 'm':
        {
            if (strcmp(argv[3], "merge") == 0)
            {
                mergeSort(0, n - 1);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                return 1;
            }
            break;
        }
        case 'q':
        {
            if (strcmp(argv[3], "quick") == 0)
            {
                quickSort(0, n - 1);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                return 1;
            }
            break;
        }
        case 'r':
        {
            if (strcmp(argv[3], "radix") == 0)
            {
                radixsort(n);
            }
            else
            {
                printf("Error: Sort %s was not found.", argv[3]);
                return 1;
            }
            break;
        }
        default:
        {
            printf("Error: Sort %s was not found.", argv[3]);
            return 1;
        }
    }
    print(n);
    fclose(fptr);
    free(lengths);
    for (int i=0;i<n;i++)
    {
        free(strings[i]);
    }
    free(strings);
    free(current_string);
    return 0;
}
