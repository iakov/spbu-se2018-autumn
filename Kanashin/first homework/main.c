 #include <stdio.h>
 #include <stdlib.h>

 extern bubblesort(int* a, int n);

 int convertparams(char *param, int numb)
 {
    int sign=1;
    int paramnum = 0;
    while(param[numb] != '\0')
    {
        if (param[numb] == '-')
            sign = -1;
        else
        {
            paramnum = 10*paramnum + atoi(&param[numb]);
        }
        numb++;
    }
    paramnum *= sign;
    return paramnum;
 }

 int main (int argc, char * argv[])
 {
    int sign=1, i=1, from = -2147483648, to = 2147483647;
    while (i<argc)
    {
        if (argv[i][2] == 'f')
        {
            if (argv[i][7]>='0' && argv[i][7]<='9' || argv[i][7]=='-')
            {
                from = convertparams(argv[i], 7);
                i++;
            }
            else if (argv[i+1][1]>='0' && argv[i+1][1]<='9' || argv[i+1][1]=='-')
            {
                from = convertparams(argv[i+1], 1);
                i += 2;
            }
            else
            {
                from = convertparams(argv[i+2], 0);
                i += 3;
            }
        }
        else if (argv[i][2] == 't')
        {
            if (argv[i][5]>='0' && argv[i][5]<='9' || argv[i][5]=='-')
            {
                to = convertparams(argv[i], 5);
                i++;
            }
            else if (argv[i+1][1]>='0' && argv[i+1][1]<='9' || argv[i+1][1]=='-')
            {
                to = convertparams(argv[i+1], 1);
                i += 2;
            }
            else
            {
                to = convertparams(argv[i+2], 0);
                i += 3;
            }
        }
        else i++;
    }
    int  numbersbefore[100]={0}, numbers[100]={0};
    sign=1;
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
    int flaglessfrom=0, countmoreto = 0, countnumb = i, countnumbsort = 0;
    int morethanto[100]={0};
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
            flaglessfrom=1;
        }
        else if (numbers[i]>=to)
        {
            morethanto[countmoreto]=numbers[i];
            countmoreto++;
        }
    }
    if (!flaglessfrom)
    printf("- ");;
    if (countmoreto == 0)
        fprintf(stderr, "%c", '-');
    else
        for (i=0; i<countmoreto; i++)
            fprintf(stderr, "%d ", morethanto[i]);

    bubblesort(numbers, countnumbsort);

    int countchanged=0;
    for (i=0; i<countnumbsort; i++)
    {
        if (numbers[i]!=numbersbefore[i])
            countchanged++;
    }
    return countchanged;
 }
