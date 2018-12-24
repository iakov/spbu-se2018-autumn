#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <time.h>

#include "header.h"

clock_t timecounter_start = 0;
clock_t timecounter_end = 0;

void Sort_Quick(char **base, int left, int right) {
    if (left >= right) {
        return;
    }
    int i = left, j = right;
    int middle = (right + left) / 2;
    char *pivot = base[middle];
    while (i <= j) {
        while (strcmp(base[i], pivot) < 0) {
            ++i;
        }
        while (strcmp(base[j], pivot) > 0) {
            --j;
        }
        if (i <= j) {
            SwapString(&base[i++], &base[j--]);
        }
    }
    if(left<j) Sort_Quick(base, left, j);
    if(i<right) Sort_Quick(base, i, right);
}

int main(int argc, char * inputstring[])
{
	unsigned int Numberoflines;
	if(argc == 4)
		CheckOption(inputstring, &Numberoflines);
	else
	{
		PrintError("Three parameters must be entered.", 1);
	}

	FILE *inputfile = fopen(inputstring[2],"r");
	if(!inputfile)
	{
		PrintError("Failed to read a file.", 2);
	}

	char **strings;
	strings = (char**)malloc(Numberoflines * sizeof(char*));
	unsigned int counter = 0;
	unsigned int pass_counter = 0;
	while(counter < Numberoflines)
	{
		int tmplen = 1000;
		char tmpstring[tmplen];
		if(fgets(tmpstring, tmplen, inputfile) == NULL)
		{
			break;
		}

		pass_counter++;
		if(pass_counter == 1)
		{
			strings[counter] = (char*)calloc((strlen(tmpstring) + 1), sizeof(char));
			if(strings == NULL)
			{
				PrintError("I can not allocate memory in Main for a \"strings[counter]\" array.", 4);
			}
		}
		else
		{
			strings[counter] = (char*)realloc(strings[counter], (strlen(strings[counter]) + strlen(tmpstring) + 1) * sizeof(char));
			if(strings[counter] == NULL)
		    {
				PrintError("I can not change the size of the allocated memory in Main for a \"strings[counter]\" array.", 4);
		    }
		}
		sprintf(strings[counter], "%s%s", strings[counter], tmpstring);
		char tempchar = tmpstring[strlen(tmpstring)-1];
		if(tempchar == '\n' || tempchar == EOF)
		{
			counter++;
			pass_counter = 0;
		}
	}
	Numberoflines = counter;


	if(!strcmp(inputstring[3], "bubble"))
	{
		Sort_Bubble(strings, Numberoflines);
	}
	else if(!strcmp(inputstring[3], "insertion"))
	{
		Sort_Insertion(strings, Numberoflines);
	}
	else if(!strcmp(inputstring[3], "merge"))
	{
		Sort_Merge(strings, Numberoflines);
	}
	else if(!strcmp(inputstring[3], "quick"))
	{
		Sort_Quick(strings, 0, Numberoflines-1);
	}
	else if(!strcmp(inputstring[3], "radix"))
	{
		unsigned int maxlength = strlen(strings[0]);
		for(unsigned int i = 1; i < Numberoflines; ++i)
		{
			if(strlen(strings[i]) > maxlength)
			{
				maxlength = strlen(strings[i]);
			}
		}
		Sort_Radix(strings, 0, Numberoflines-1, 0, maxlength-2);
	}
	else
	{
		PrintError("Unknown error, program failed.", 1);
	}

	for(unsigned int i = 0; i < Numberoflines; ++i)
	{
		printf("%s", strings[i]);
		free(strings[i]);
	}
	free(strings);


	//printf("Time: %ld\n", timecounter_end - timecounter_start);

	fclose(inputfile);

	return 0;
}

void Sort_Bubble(char * sortlines[], unsigned int Countofline)
{
	if(timecounter_start == 0)
	{
		timecounter_start = clock();
	}
	for(unsigned int i = 0; i < Countofline-1; ++i)
	{
		for(unsigned int j = 0; j < Countofline - i - 1; ++j)
		{
			if(strcmp(sortlines[j], sortlines[j+1]) > 0)
			{
				SwapString(&sortlines[j], &sortlines[j+1]);
			}
		}
	}

	timecounter_end = clock();
}

void Sort_Insertion(char * sortlines[], unsigned int Countofline)
{
	if(timecounter_start == 0)
	{
		timecounter_start = clock();
	}

	for(unsigned int i = 1; i < Countofline; ++i)
	{
		char *temp = sortlines[i];
		int j = i-1;
		while((j >= 0) && (strcmp(sortlines[j], temp) > 0))
		{
			SwapString(&sortlines[j], &sortlines[j+1]);
			j--;
		}
	}

	timecounter_end = clock();
}

void Sort_Merge(char * sortlines[], unsigned int Countofline)
{
	if(timecounter_start == 0)
	{
		timecounter_start = clock();
	}

	if(Countofline <= 1)
	{
		return;
	}

	unsigned int mid = Countofline / 2;
	Sort_Merge(sortlines, mid);
    Sort_Merge(sortlines + mid, Countofline - mid);

    char **tmp = (char **) malloc(Countofline * sizeof(char *));
    if(tmp == NULL)
    {
		PrintError("I can not allocate memory in Merge sorting for a \"tmp\" array.", 4);
    }

    unsigned int left_pointer = 0, right_pointer = mid, pointer = 0;
    while(left_pointer < mid)
    {
        if((right_pointer >= Countofline) || (strcmp(sortlines[right_pointer], sortlines[left_pointer]) > 0))
        {
            tmp[pointer++] = sortlines[left_pointer++];
    	}
        else
        {
    		tmp[pointer++] = sortlines[right_pointer++];
        }
    }
    while(right_pointer < Countofline)
    {
        tmp[pointer++] = sortlines[right_pointer++];
    }
    for(unsigned int i = 0; i < Countofline; i++)
    {
        sortlines[i] = tmp[i];
    }
    
    free(tmp);

	timecounter_end = clock();
}

/*void Sort_Quick(char * sortlines[], unsigned int first, unsigned int last)
{
	if(timecounter_start == 0)
	{
		timecounter_start = clock();
	}

	if(first >= last)
	{
		return;
	}

    unsigned int i = first, j = last;
    unsigned int middle = (first + last)/2;
    char *pivot = sortlines[middle];

    while (i <= j)
    {
        while((strcmp(sortlines[i], pivot) < 0))
        {
            ++i;
        }
        while((strcmp(sortlines[j], pivot) > 0))
        {
            --j;
        }

		if (i <= j)
		{
            SwapString(&sortlines[i++], &sortlines[j--]);
        }
    }
 
    if(i < last)
    {
        Sort_Quick(sortlines, i, last);
    }
    if(j > first)
    {
        Sort_Quick(sortlines, first, j);
    }

	timecounter_end = clock();
}*/

void Sort_Radix(char * sortlines[], unsigned int from, unsigned int to, unsigned int byte, unsigned int maxlength)
{
	if(timecounter_start == 0)
	{
		timecounter_start = clock();
	}

	if(byte >= maxlength)
	{
		return;
	}

	char *basecharacters = " !\"'(),-.0123456789:;?ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnoprqrstuvwxyz";
	unsigned int length = strlen(basecharacters)+1;
	unsigned int datacounter[length];
	unsigned int strcounter[length];
	char ***data = (char***)malloc((length + 1) * sizeof(char**));
	if(data == NULL)
    {
		PrintError("I can not allocate memory in Radix sorting for a \"data\" array.", 4);
    }

    for(unsigned int i = 0; i < length; ++i)
	{
		datacounter[i] = 0;
		strcounter[i] = 0;
	}

	for(unsigned int i = from; i <= to; ++i)
	{
		int tempchar;
		if(byte >= strlen(sortlines[i])-2)
		{
			tempchar = 0;
		}
		else
		{
			char *tempchar_temp = strchr(basecharacters, sortlines[i][byte]);
			if(tempchar_temp == NULL)
			{
		        printf("\n[!] String: %d Byte: %d / [ %c ]\n", i+1, byte, sortlines[i][byte]);
				PrintError("Found a character that is not part of the allowed.", 5);
			}
			tempchar = tempchar_temp - basecharacters + 1;
		}
		if(datacounter[tempchar] == 0)
		{
			data[tempchar] = (char**)calloc(1, sizeof(char*));
			if(data[tempchar] == NULL)
		    {
				PrintError("I can not allocate memory in Radix sorting for a \"data[tempchar]\" array.", 4);
		    }
		}
		else if(datacounter[tempchar] > 0)
		{
			data[tempchar] = (char**)realloc(data[tempchar], (datacounter[tempchar] + 1) * sizeof(char*));			
			if(data[tempchar] == NULL)
		    {
				PrintError("I can not change the size of the allocated memory in Radix sorting for a \"data[tempchar]\" array.", 4);
		    }
		}

		data[tempchar][datacounter[tempchar]] = (char*)malloc((strlen(sortlines[i]) + 1) * sizeof(char));
		if(data[tempchar][datacounter[tempchar]] == NULL)
	    {
			PrintError("I can not allocate memory in Radix sorting for a \"data[tempchar][datacounter[tempchar]]\" array.", 4);
	    }
		sprintf(data[tempchar][datacounter[tempchar]], "%s", sortlines[i]);

		datacounter[tempchar]++;
		strcounter[tempchar]++;
	}

	unsigned int counter = 0;
	while(counter <= (to-from))
	{
		for(unsigned int i = 0; i < length; ++i)
		{
			if(datacounter[i] > 0)
			{
				for(unsigned int j = 0; j < datacounter[i]; ++j)
				{
					free(sortlines[from+counter]);
					sortlines[from+counter] = (char*)calloc((strlen(data[i][j]) + 1), sizeof(char));
					sprintf(sortlines[from+counter], "%s", data[i][j]);
					counter++;
				}
			}
		}
	}

	counter = 0; int fromposition = -1;
	for(unsigned int i = from; i < to; ++i)
	{
		if(sortlines[i][byte] == sortlines[i+1][byte])
		{
			if(fromposition == -1)
			{
				fromposition = i;
			}
			counter++;
		}
		else if(( sortlines[i][byte] != sortlines[i+1][byte]) && (fromposition != -1))
		{
			Sort_Radix(sortlines, fromposition, fromposition+counter, byte+1, maxlength);
			counter = 0;
			fromposition = -1;
		}
	}

	for(unsigned int i = 0; i < length; ++i)
	{
		if(datacounter[i] > 0)
		{
			for(int j = strcounter[i]; j > 0; --j)
			{
				free(data[i][j-1]);
			}
			free(data[i]);
		}
	}

	free(data);

	timecounter_end = clock();
}

void CheckOption(char * options[], unsigned int *Numberoflines)
{
	int UnknownOptionIndex = -1;

	*Numberoflines = atoi(options[1]);
	if(*Numberoflines == 0)
	{
		char errorstr[75 + strlen(options[1])];
		sprintf(errorstr, "The parameter is responsible for the number of lines NaN, or it is zero.(%s)", options[1]);
		PrintError(errorstr, 1);
	}
	for(unsigned int j = 0; j < allowedOptionsLength; j++)
	{
		if(strcmp(options[3], allowedOptions[j]) == 0)
		{
			UnknownOptionIndex = -1;
			break;
		}
		else
		{		
			UnknownOptionIndex = 3;
		}
	}
	if(UnknownOptionIndex > -1)
	{
		char errorstr[30 + strlen(options[UnknownOptionIndex])];
		sprintf(errorstr, "Unknown option was given! (%s)", options[UnknownOptionIndex]);
		PrintError(errorstr, 1);
	}
}

void SwapString(char * string1[], char * string2[])
{
	char *temp = *string1;
	*string1 = *string2;
	*string2 = temp;
}

void PrintError(char * string, int ExitCode)
{
	printf("\n[!] Error: %s.\n\n", string);
	fflush(stdin);
	exit(ExitCode);
}