#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Input file must contain N lines of 10 characters
 *
 * Data output is performed in the console and in
 * the output file (OUT_FILE_NAME)
 *
 * Application exit codes:
 *
 * 1 - invalid program argument
 * 2 - missing required file
 * 3 - incorrect input data
 * 4 - system function call error
 * 5 - reserved
 */

//Swap strings
void strSwap(char **x, char **y)
{
    char *temp = *x;
    *x = *y;
    *y = temp;
}

//Bubble sort
void bubbleSort(char **str_array, int strNum)
{
    for (int i = 0; i < strNum; i++)
    {
        for (int j = i + 1; j < strNum; j++)
        {
            if (strcmp(str_array[i], str_array[j]) > 0)
                strSwap(&str_array[i], &str_array[j]);
        }
    }
}

//Insertion sort
void insertionSort(char **str_array, int strNum)
{
    int j = 0;

    for (int i = 1; i < strNum; i++)
    {
        j = i;
        while ((j > 0) && (strcmp(str_array[j - 1], str_array[j]) > 0))
        {
            strSwap(&str_array[j - 1], &str_array[j]);
            j--;
        }
    }
}

//Merge sort
void merge(char **str_array, int middle, int strNum)
{
    char **tmp = malloc(strNum * sizeof(char *));
    if (tmp == NULL)
    {
        printf("Not enough memory\n");
        exit(4);    //4 - system function call error exit code
    }
    int left = 0, right = middle, cur_pos = 0;
    while (left < middle)
    {
        if (right >= strNum || strcmp(str_array[right], str_array[left]) > 0)
            tmp[cur_pos++] = str_array[left++];
        else
            tmp[cur_pos++] = str_array[right++];
    }
    while (right < strNum)
        tmp[cur_pos++] = str_array[right++];
    for (int i = 0; i < strNum; i++)
        str_array[i] = tmp[i];
    free(tmp);
}
void mergeSort(char **str_array, int strNum)
{
    if (strNum <= 1) return;
    int middle = strNum / 2;
    mergeSort(str_array, middle);
    mergeSort(str_array + middle, strNum - middle);

    merge(str_array, middle, strNum);
}

//Quick sort
void quickSort(char **str_array, int left, int right)
{
    int l_pointer = left;        //left pointer
    int r_pointer = right - 1;   //Right pointer
    char *pivot = str_array[(left + (right-left)/2)];  //Pivot element

    do
    {
        while((strcmp(str_array[l_pointer], pivot) < 0))
        {
            l_pointer++;
        }
        while((strcmp(str_array[r_pointer], pivot) > 0))
        {
            r_pointer--;
        }
        if(l_pointer <= r_pointer)
        {
            if((strcmp(str_array[l_pointer], str_array[r_pointer]) > 0))
            {
                strSwap(&str_array[l_pointer], &str_array[r_pointer]);
            }
            l_pointer++;
            if (r_pointer > 0)
            {
                r_pointer--;
            }
        }
    } while (l_pointer <= r_pointer);

    if(l_pointer < right)
    {
        quickSort(str_array, l_pointer, right);
    }
    if(r_pointer > left)
    {
        quickSort(str_array, left, r_pointer);
    }
}

//Heap sort
void heapify(char* str_array[], int strNum, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < strNum && strcmp(str_array[left], str_array[largest]) > 0)
    {
        largest = left;
    }

    if (right < strNum && strcmp(str_array[right], str_array[largest]) > 0)
    {
        largest = right;
    }

    if (largest != i)
    {
        strSwap(&str_array[i], &str_array[largest]);
        heapify(str_array, strNum, largest);
    }
}
void heapSort(char **str_array, int strNum)
{
    for (int i = strNum / 2 - 1; i >= 0; i--)
    {
        heapify(str_array, strNum, i);
    }

    for (int i = strNum - 1; i >= 0; i--)
    {
        strSwap(&str_array[0], &str_array[i]);
        heapify(str_array, i, 0);
    }
}

//Sort by defined algorithm
void sort(char **str_array, int linesNumber, const char *alg)
{
    if (strcmp(alg,"bubble") == 0)
    {
        bubbleSort(str_array, linesNumber);     //Bubble sort
    }
    else if (strcmp(alg,"insertion") == 0)
    {
        insertionSort(str_array, linesNumber);  //Insertion sort
    }
    else if (strcmp(alg,"merge") == 0)
    {
        mergeSort(str_array, linesNumber);      //Merge sort
    }
    else if (strcmp(alg,"quick") == 0)
    {
        quickSort(str_array, 0, linesNumber);   //Quick sort
    }
    else if (strcmp(alg,"heap") == 0)
    {
        heapSort(str_array, linesNumber);       //Heap sort
    }
    else if (strcmp(alg,"radix") == 0)
    {
        heapSort(str_array, linesNumber);       //Still heap sort
    }
    else
    {
        fprintf(stderr, "Unknown sorting algorithm! (%s)\n", alg);
        exit(1);    //1 - invalid program argument exit code
    }
}

int main(int argc, char *argv[])
{
    //Number of program arguments validity check
    if (argc != 4)
    {
        fprintf(stderr, "Invalid number of arguments! (%d) 4 expected\n", argc);
        exit(1);    //1 - invalid program argument exit code
    }

    //Output to file
    //char *OUT_FILE_NAME = "/home/avalacnhe/CLionProjects/FileSort/output.txt";

    const int LINE_LENGTH = 1337228;
    int LINES_NUMBER = (int)strtol(argv[1], NULL, 10);  //String to int conversion
    char *IN_FILE_NAME = argv[2];                       //
    char *ALG_NAME = argv[3];                           //

    FILE *i_file = fopen(IN_FILE_NAME, "r");
    if (i_file == NULL)
    {
        fprintf(stderr, "Invalid path to file! (%s)\n", IN_FILE_NAME);
        exit(2);    //2 - missing file exit code
    }

    char **str_array = malloc(LINES_NUMBER * sizeof(char *));   //File content
    if (str_array == NULL)
    {
        fprintf(stderr, "Not enough memory!\n");
        exit(4);    //4 - system function call error exit code
    }

    char *temp = malloc(LINE_LENGTH);  //Temporary string buffer
    if (temp == NULL)
    {
        fprintf(stderr, "Not enough memory! (and money...)\n");
        exit(4);    //4 - system function call error exit code
    }

    int current_line_number = 0;
    for (current_line_number = 0; current_line_number < LINES_NUMBER; current_line_number++)
    {
        if (fgets(temp, LINE_LENGTH, i_file) == NULL)
        {
            if (current_line_number < LINE_LENGTH)      //if input file contains less lines than expected
            {
                fprintf(stderr, "Wrong input data! (%s)\n", IN_FILE_NAME);
                exit(3);
            }
            break;
        }

        str_array[current_line_number] = malloc((strlen(temp) + 1) * sizeof(char));
        if (str_array[current_line_number] == NULL)
        {
            for (int i = 0; i < current_line_number; i++)
                free(str_array[i]);

            free(str_array);
            free(temp);

            fprintf(stderr, "Not enough memory!");
            exit(4);    //4 - system function call error exit code
        }
        strcpy(str_array[current_line_number], temp);
    }

    /*
    FILE *o_file = fopen(OUT_FILE_NAME, "w");
    if (o_file == NULL)
    {
        fprintf(stderr, "File open/creation error (%s)\n", OUT_FILE_NAME);
        exit(5);    //5 - use-it-in-any-incomprehensible-situation exit code
    }
     */

    if (current_line_number > 0)
        sort(str_array, current_line_number, ALG_NAME);

    /*
    //Output to file
    for (int i = 0; i < LINES_NUMBER; i++)
    {
        fprintf(o_file, "%s", str_array[i]);
    }
     */

    for (int i = 0; i < current_line_number; i++)
    {
        printf("%s", str_array[i]);
    }

    //Memory release
    for (int i = 0; i < current_line_number; i++)
    {
        free(str_array[i]);
    }
    free(str_array);
    free(temp);         //Temporary buffer memory release
    fclose(i_file);     //Input file close
    //fclose(o_file);     //Output file close

    return 0;
}
