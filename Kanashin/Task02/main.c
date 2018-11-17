 #include <stdio.h>
 #include <stdlib.h>
  extern void bubblesort(int* a, int n);
  int convertParams(char *param, int numb)
 {
    int sign=1;
    int paramNum = 0;
    while(param[numb] != '\0')
    {
        if (param[numb] == '-')
            sign = -1;
        else
        {
            paramNum = 10*paramNum + atoi(&param[numb]);
        }
        numb++;
    }
    paramNum *= sign;
    return paramNum;
 }
 int convertToFrom(char* argv[], int it, int secondIt)
 {
        if (argv[it][secondIt]>='0' && argv[it][secondIt]<='9' || argv[it][secondIt]=='-')
            return convertParams(argv[it], secondIt);

        else if (argv[it+1][0]>='0' && argv[it+1][0]<='9' || argv[it+1][0]=='-')
            return convertParams(argv[it+1], 0);

        else
            return convertParams(argv[it+2], 0);
 }
  int main (int argc, char * argv[])
 {
    int sign=1, i=1, from = -2147483648, to = 2147483647;
    for (i; i<argc; i++)
    {
        if (argv[i][2] == 'f')
        {
            from = convertToFrom(argv, i, 7);
        }
        else if (argv[i][2] == 't')
        {
            to = convertToFrom(argv, i, 5);
        }
    }
    int  numbersBefore[100]={0}, numbers[100]={0};
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
    int flagLessFrom=0, countMoreTo = 0, countNumb = i, countNumbSort = 0;
    int moreThanTo[100]={0};
    for (i=0; i<=countNumb; i++)
    {
        if (numbers[i]>from && numbers[i]<to)
        {
            numbers[countNumbSort]=numbers[i];
            numbersBefore[countNumbSort]=numbers[countNumbSort];
            countNumbSort++;
        }
        else if (numbers[i]<=from)
        {
            fprintf(stdout, "%d ", numbers[i]);
            flagLessFrom=1;
        }
        else if (numbers[i]>=to)
        {
            moreThanTo[countMoreTo]=numbers[i];
            countMoreTo++;
        }
    }
    if (!flagLessFrom)
    printf("- ");;
    if (countMoreTo == 0)
        fprintf(stderr, "%c", '-');
    else
        for (i=0; i<countMoreTo; i++)
            fprintf(stderr, "%d ", moreThanTo[i]);
     bubblesort(numbers, countNumbSort);
     int countChanged=0;
    for (i=0; i<countNumbSort; i++)
    {
        if (numbers[i]!=numbersBefore[i])
            countChanged++;
    }
    return countChanged;
 }
