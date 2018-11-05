#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern int __sort(int counter, int massive[]);

//optional "from" and "to"
int down = NULL;
int high = NULL;

void params(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    params(argc, argv);
    //read and filter massive
    int *massive = calloc(100, sizeof(int));
    int counter = 0;
    while (scanf("%d", massive + counter) == 1)
    {
        if ((down != '\0') && (massive[counter] <= down))
        {
            fprintf(stdout, "%d ", massive[counter]);
            massive[counter] = 0;
            counter--;
        }
        else if ((high != '\0') && (massive[counter] >= high))
        {
            fprintf(stderr, "%d ", massive[counter]);
            massive[counter] = 0;
            counter--;
        }
        counter++;
    }
    //sort massive
    int counterOfTranspositions = __sort(counter, massive);
    free(massive);
    return counterOfTranspositions;
}

//read parametrs
void params(int argc, char *argv[])
    {
        char *parametrs = calloc(40, sizeof(char));
        int counter = 0;
        for (int i = 1, j = 0; i <= argc - 1; i++, j = 0)
    	    while ((argv[i])[j] != '\0')
    		    parametrs[counter++] = (argv[i])[j++];
        parametrs[counter] = '\0';
        counter = 0;
        while (parametrs[counter++] != '\0')
    	    if (parametrs[counter] == 'f')
    	    {
    		    counter += 5;
    		    int sign = parametrs[counter] == '-' ? -1 : 1;
    		    if (sign == -1) ++counter;
    		    down = 0;
    		    while(isdigit(parametrs[counter]))
    			    down = down * 10 + parametrs[counter++] - '0';
    		    down *= sign;
    	    }
            else if (parametrs[counter] == 't')
    	    {
    		    counter += 3;
    		    int sign = parametrs[counter] == '-' ? -1 : 1;
    		    if (sign == -1) ++counter;
    		    high = 0;
    		    while (isdigit(parametrs[counter]))
    			    high = high * 10 + parametrs[counter++] - '0';
    		    high *= sign;
    	    }
        free(parametrs);
    }
