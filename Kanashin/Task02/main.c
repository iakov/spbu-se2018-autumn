 #include <stdio.h>
 #include <stdlib.h>
 /*void bubblesort(int* a, int n)
 {
    for(int i = 0 ; i < n - 1; i++)
    {
       for(int j = 0 ; j < n - i - 1 ; j++)
       {
           if(a[j] > a[j+1])
           {
              int tmp = a[j];
              a[j] = a[j+1] ;
              a[j+1] = tmp;
           }
       }
    }
 }*/
 extern bubblesort(int* a, int n);

 int main (int argc, char * argv[])
 {
    int sign=1, i=1, from = -2147483648, to = 2147483647;
        while (i<argc)
        {
            if (argv[i][2] == 'f')
            {
                int count=7;
                from = 0;
                while(argv[i][count] != '\0')
                {
                    if (argv[i][count] == '-')
                        sign = -1;
                    else
                    {
                        from = 10*from + atoi(&argv[i][count]);
                    }
                    count++;
                }
                from *= sign;
                i++;
                sign = 1;
            }
            else if (argv[i][2] == 't')
            {
                int count=5;
                to = 0;
                while(argv[i][count] != '\0')
                {
                    if (argv[i][count] == '-')
                        sign = -1;
                    else
                    {
                        to = 10*to + atoi(&argv[i][count]);
                    }
                    count++;
                }
                to *= sign;
                i++;
                sign = 1;
            }
            else i++;
        }

    int  numbersbefore[100], signnumb[100], numbers[100];
    for (i=0; i<100; i++)
    {
        numbersbefore[i]=0; 
        numbers[i]=0; 
        signnumb[i]=1; 
    }
    i=0;
    char symb=getchar();
    while (symb != '\n')
    {
        if (symb == ' ')
        {
            symb = getchar();
            i++;
            sign=1;
            continue;
        }
        else if (symb == '-')
        {
            sign = -1;
            symb = getchar();
            continue;
        }
        else
        {
            numbers[i] = numbers[i]*10 + sign*atoi(&symb);
            symb = getchar();
            continue;
        }
    }
    int flaglessfrom = 0, countmoreto = 0, countnumb = i, countnumbsort = 0; 
    int morethanto[100]={0};
    //printf("Stdout: ");
    for (i=0; i<=countnumb; i++)
    {
        if (numbers[i]>from && numbers[i]<to)
        {
            numbers[countnumbsort]=numbers[i];
            numbersbefore[countnumbsort]=numbers[countnumbsort];
            countnumbsort++;
        }
        else if (numbers[i]<=from)
        {
            fprintf(stdout, "%d ", numbers[i]);
            flaglessfrom = 1;
        }
        else if (numbers[i]>=to)
        {
            morethanto[countmoreto]=numbers[i];
            countmoreto++;
        }
    }
    if (flaglessfrom == 0)
    printf("- ");
    //printf("Stderr: ");
    if (countmoreto == 0)
        fprintf(stderr, "%c", '-');
    else
        for (i=0; i<countmoreto; i++)
            fprintf(stderr, "%d ", morethanto[i]);

    bubblesort(numbers, countnumbsort);

    int countchanged=0; 
    //printf("\nSorted: ");
    for (i=0; i<countnumbsort; i++)
    {
        if (numbers[i]!=numbersbefore[i])
            countchanged++;
        //printf("%d ", numbers[i]);
    }
    return countchanged;
 }
