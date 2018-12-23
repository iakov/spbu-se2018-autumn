#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int strAmount;//
void string_swp(char **string1,char **string2)
{
    char *swp;
    swp = *string1;
    *string1 = *string2;
    *string2 = swp;

}
void bubble_sort(char **str)
{

    for(int i = 1; i < strAmount; i++)
    {
        for(int j = 1; j < strAmount; j++)
        {
            if((strcmp(str[j] , str[j-1])) < 0)
            {
                string_swp(&str[j] , &str[j-1]);
            }
        }
    }

}

void insertion_sort(char **str)
{
    char *tmp;
    for (int i = 1; i < strAmount; i++)
    {
        tmp = str[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if(strcmp(tmp , str[j]) <= 0)
            {
                str[j + 1] = str[j];
                str[j] = tmp;
            }
        }
    }
}


void merge_sort(char **str, int len)
{

    if (len <= 1)
        return;
    int middle = len / 2;
    merge_sort(str , middle);
    merge_sort(str + middle , len - middle);
    char ** tmp = malloc(len * sizeof(char *));
    if (tmp == NULL)
    {
        printf("Unable to allocate enough memory\n");
        exit(5);
    }
    int ptr_l = 0, ptr_r = middle, ptr = 0;
    while (ptr_l < middle)
    {
        if ((ptr_r >= len) || (strcmp(str[ptr_r], str[ptr_l]) > 0))
            tmp[ptr++] = str[ptr_l++];
        else
            tmp[ptr++] = str[ptr_r++];
    }
    while (ptr_r < len)
        tmp[ptr++] = str[ptr_r++];
    for (int i = 0; i < len; i++)
        str[i] = tmp[i];
    free(tmp);

}

void quick_sort(char **str,int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int left = l, right = r;//local iterators
    int middle = (r + l) / 2;
    char *tmp = str[middle];
    while (left <= right) {
        while (strcmp(str[left], tmp) < 0)
        {
            left++;
        }
        while (strcmp(str[right], tmp) > 0)
        {
            right--;
        }
        if (left <= right)
        {
            string_swp(&str[left++], &str[right--]);
        }
    }
    if(l < right) quick_sort(str, l, right);
    if(left < r) quick_sort(str, left, r);
}

void heap(char **str, int strCount, int i)
{
    int maxV = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < strCount && strcmp(str[left], str[maxV]) > 0)
    {
        maxV = left;
    }
    if (right < strCount && strcmp(str[right], str[maxV]) > 0)
    {
        maxV = right;
    }
    if (maxV != i) {
        string_swp(&str[i], &str[maxV]);
        heap(str, strCount, maxV);
    }
}
void heap_sort(char **str, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heap(str, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        string_swp(&str[i], &str[0]);
        heap(str, i, 0);
    }
}
int main(int argc,char* argv[])
{
    if(argc!=4)
    {
        printf("parameters amount error\n");
        exit(1);
    }
    FILE *file = NULL;
    file = fopen(argv[2],"r");
    if(file == NULL)
    {
        printf("Unable to open input file\n");
        exit(2);
    }

    int strLength = 100;
    strAmount = atoi(argv[1]);
    char **strings = (char **) malloc(strAmount * sizeof(char *));
    char *inpStr= (char *) malloc(strLength * sizeof(char));
    if((strings == NULL)||(inpStr == NULL))
    {
        printf("Unable to allocate memory for input\n");
        exit(4);
    }
    for(int i = 0; i < strAmount; i++)
    {
        if(fgets(inpStr, strLength, file) == NULL)
        {
            printf("Unable to read file\n");
            exit(4);
        }
        strings[i] = (char *) malloc((strlen(inpStr) + 1) * sizeof(char));
        if(strings[i] == NULL)
        {   printf("Unable to allocate memory for strings\n");
            exit(4);
        }
        strcpy(strings[i], inpStr);
    }
    free(inpStr);
    fclose(file);
    char *sort_type = argv[3];
    if (strcmp(sort_type, "bubble") == 0)
    {
        bubble_sort(strings);
    }
    else
        if (strcmp(sort_type, "insertion") == 0)
    {
        insertion_sort(strings);
    }
    else if (strcmp(sort_type, "merge") == 0)
    {
        merge_sort(strings, strAmount);
    }
    else if (strcmp(sort_type, "heap") == 0)
    {
        heap_sort(strings, strAmount);
    }
    else if (strcmp(sort_type, "radix") == 0)
    {
        heap_sort(strings, strAmount);
    }
    else if (strcmp(sort_type, "quick") == 0)
    {
        quick_sort(strings, 0, strAmount-1);
    }
    else
    {
        printf("Algorithm type error\n");
        exit(1);
    }

    for(int i = 0; i < strAmount; i++)
    {
        printf("%s",strings[i]);
        free(strings[i]);
    }

    free(strings);
    return 0;
}
