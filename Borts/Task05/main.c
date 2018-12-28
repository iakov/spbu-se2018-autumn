#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

int main(int argc, char * input_string[])
{	
	unsigned int number_of_lines = 0;
	if(argc != 4)
	{
		printf("Required: [number of lines] [input file] [algorithm name]\n");
		printf("Valid algorithm names: bubble / merge / insertion / quick / radix\n");
		printf("Example: 10 text.txt radix\n");
		PrintError("Three parameters must be entered.", 1);
	}
	else
	{
		CheckOption(input_string, &number_of_lines);
	}

	FILE *input_file = fopen(input_string[2],"r");
	if(!input_file)
	{
		PrintError("Failed to read a file.", 2);
	}

	char **strings;
	strings = (char**)malloc(number_of_lines * sizeof(char*));
	if(strings == NULL)
	{
		PrintError("I can not allocate memory in Main for a \"strings\".", 4);
	}
	unsigned int counter = 0;
	unsigned int pass_counter = 0;
	while(counter < number_of_lines)
	{
		int temp_length = 1000;
		char temp_string[temp_length];
		if(fgets(temp_string, temp_length, input_file) == NULL)
		{
			break;
		}

		pass_counter++;
		if(pass_counter == 1)
		{
			strings[counter] = (char*)calloc((strlen(temp_string) + 1), sizeof(char));
			if(strings[counter] == NULL)
			{
				PrintError("I can not allocate memory in Main for a \"strings[counter]\".", 4);
			}
		}
		else
		{
			strings[counter] = (char*)realloc(strings[counter],(strlen(strings[counter])+strlen(temp_string)+1)*sizeof(char));
			if(strings[counter] == NULL)
			{
				PrintError("I can not change the size of the allocated memory in Main for a \"strings[counter]\".", 4);
			}
		}
		strcat(strings[counter], temp_string);
		char line_end_pointer = temp_string[strlen(temp_string)-1];
		if(line_end_pointer == '\n' || line_end_pointer == EOF)
		{
			counter++;
			pass_counter = 0;
		}
	}
	number_of_lines = counter;

	char *algorithm_name = input_string[3];

	if(!strcmp(algorithm_name, "bubble"))
	{
		Sort_Bubble(strings, number_of_lines);
	}
	else if(!strcmp(algorithm_name, "insertion"))
	{
		Sort_Insertion(strings, number_of_lines);
	}
	else if(!strcmp(algorithm_name, "merge"))
	{
		Sort_Merge(strings, number_of_lines);
	}
	else if(!strcmp(algorithm_name, "quick"))
	{
		Sort_Quick(strings, 0, number_of_lines-1);
	}
	else if(!strcmp(algorithm_name, "radix"))
	{
		unsigned int maximum_length = strlen(strings[0]);
		for(unsigned int i = 1; i < number_of_lines; ++i)
		{
			if(strlen(strings[i]) > maximum_length)
			{
				maximum_length = strlen(strings[i]);
			}
		}
		Sort_Radix(strings, 0, number_of_lines-1, 0, maximum_length-2);
	}
	else
	{
		PrintError("Unknown error while selecting sorting algorithm, program failed.", 1);
	}

	for(unsigned int i = 0; i < number_of_lines; ++i)
	{
		printf("%s", strings[i]);
		free(strings[i]);
	}
	free(strings);

	fclose(input_file);

	return 0;
}

void Sort_Bubble(char * sort_strings[], unsigned int count_of_line)
{
	for(unsigned int i = 0; i < count_of_line-1; ++i)
	{
		for(unsigned int j = 0; j < count_of_line - i - 1; ++j)
		{
			if(strcmp(sort_strings[j], sort_strings[j+1]) > 0)
			{
				SwapString(&sort_strings[j], &sort_strings[j+1]);
			}
		}
	}
}

void Sort_Insertion(char * sort_strings[], unsigned int count_of_line)
{
	for(unsigned int i = 1; i < count_of_line; ++i)
	{
		char *temp = sort_strings[i];
		int j = i-1;
		while((j >= 0) && (strcmp(sort_strings[j], temp) > 0))
		{
			SwapString(&sort_strings[j], &sort_strings[j+1]);
			j--;
		}
	}
}

void Sort_Merge(char * sort_strings[], unsigned int count_of_line)
{
	if(count_of_line <= 1)
	{
		return;
	}

	unsigned int middle = count_of_line / 2;
	Sort_Merge(sort_strings, middle);
	Sort_Merge(sort_strings + middle, count_of_line - middle);

    char **temp_array = (char **)malloc(count_of_line * sizeof(char *));
    if(temp_array == NULL)
    {
		PrintError("I can not allocate memory in Merge sorting for a \"temp_array\".", 4);
    }

    unsigned int left_pointer = 0, right_pointer = middle, pointer = 0;
    while(left_pointer < middle)
    {
        if((right_pointer >= count_of_line) || (strcmp(sort_strings[right_pointer], sort_strings[left_pointer]) > 0))
        {
            temp_array[pointer++] = sort_strings[left_pointer++];
    	}
        else
        {
    		temp_array[pointer++] = sort_strings[right_pointer++];
        }
    }
    while(right_pointer < count_of_line)
    {
        temp_array[pointer++] = sort_strings[right_pointer++];
    }
    for(unsigned int i = 0; i < count_of_line; i++)
    {
        sort_strings[i] = temp_array[i];
    }
    
    free(temp_array);
}

void Sort_Quick(char * sort_strings[], int first, int last)
{
    if(first >= last)
    {
        return;
    }

    int i = first, j = last;
    int middle = (last + first) / 2;
    char *pivot = sort_strings[middle];

    while(i <= j)
    {
        while (strcmp(sort_strings[i], pivot) < 0)
        {
            i++;
        }
        while (strcmp(sort_strings[j], pivot) > 0)
        {
            j--;
        }
        if(i <= j)
        {
            SwapString(&sort_strings[i++], &sort_strings[j--]);
        }
    }

    if(first < j)
    {
    	Sort_Quick(sort_strings, first, j);
    }
    if(last > i)
    {
    	Sort_Quick(sort_strings, i, last);
    }
}

void Sort_Radix(char * sort_strings[], unsigned int from, unsigned int to, unsigned int byte, unsigned int maximum_length)
{
	if(byte >= maximum_length)
	{
		return;
	}

	char *basecharacters = "!\"'(),-.0123456789:;?ABCDEFGHIJKLMNOPQRSTUVWXYZ`abcdefghijklmnoprqrstuvwxyz";
	unsigned int length = strlen(basecharacters)+1;
	unsigned int counter_data[length];
	unsigned int counter_string[length];
	char ***data = (char***)malloc((length + 1) * sizeof(char**));
	if(data == NULL)
    {
		PrintError("I can not allocate memory in Radix sorting for a \"data\".", 4);
    }

    for(unsigned int i = 0; i < length; ++i)
	{
		counter_data[i] = 0;
		counter_string[i] = 0;
	}

	for(unsigned int i = from; i <= to; ++i)
	{
		int current_char;
		if(byte >= strlen(sort_strings[i])-2)
		{
			current_char = 0;
		}
		else
		{
			char *tempchar_temp = strchr(basecharacters, sort_strings[i][byte]);
			if(tempchar_temp == NULL)
			{
		        printf("\n[!] String: %d Byte: %d / [ %c ]\n", i+1, byte, sort_strings[i][byte]);
				PrintError("Found a character that is not part of the allowed.", 5);
			}
			current_char = tempchar_temp - basecharacters + 1;
		}
		if(counter_data[current_char] == 0)
		{
			data[current_char] = (char**)calloc(1, sizeof(char*));
			if(data[current_char] == NULL)
		    {
				PrintError("I can not allocate memory in Radix sorting for a \"data[current_char]\".", 4);
		    }
		}
		else if(counter_data[current_char] > 0)
		{
			data[current_char] = (char**)realloc(data[current_char], (counter_data[current_char] + 1) * sizeof(char*));			
			if(data[current_char] == NULL)
		    {
				PrintError("I can not change the size of the allocated memory in Radix sorting for a \"data[current_char]\".", 4);
		    }
		}

		data[current_char][counter_data[current_char]] = (char*)malloc((strlen(sort_strings[i]) + 1) * sizeof(char));
		if(data[current_char][counter_data[current_char]] == NULL)
	    {
			PrintError("I can not allocate memory in Radix sorting for a \"data[current_char][counter_data[current_char]]\".", 4);
	    }
		strcpy(data[current_char][counter_data[current_char]], sort_strings[i]);

		counter_data[current_char]++;
		counter_string[current_char]++;
	}

	unsigned int counter = 0;
	while(counter <= (to - from))
	{
		for(unsigned int i = 0; i < length; ++i)
		{
			if(counter_data[i] > 0)
			{
				for(unsigned int j = 0; j < counter_data[i]; ++j)
				{
					free(sort_strings[from+counter]);
					sort_strings[from+counter] = (char*)calloc((strlen(data[i][j]) + 1), sizeof(char));
					strcpy(sort_strings[from+counter], data[i][j]);
					counter++;
				}
			}
		}
	}

	counter = 0; int from_position = -1;
	for(unsigned int i = from; i < to; ++i)
	{
		if(sort_strings[i][byte] == sort_strings[i+1][byte])
		{
			if(from_position == -1)
			{
				from_position = i;
			}
			counter++;
		}
		if((i+1 == to) && (from_position != -1))
		{
			Sort_Radix(sort_strings, from_position, from_position + counter, byte+1, maximum_length);
			counter = 0;
			from_position = -1;
		}
		else if((sort_strings[i][byte] != sort_strings[i+1][byte]) && (from_position != -1))
		{
			Sort_Radix(sort_strings, from_position, from_position + counter, byte+1, maximum_length);
			counter = 0;
			from_position = -1;
		}
	}

	for(unsigned int i = 0; i < length; ++i)
	{
		if(counter_data[i] > 0)
		{
			for(int j = counter_string[i]; j > 0; --j)
			{
				free(data[i][j-1]);
			}
			free(data[i]);
		}
	}

	free(data);
}

void CheckOption(char * options[], unsigned int *number_of_lines)
{
	int unknown_option_index = -1;

	*number_of_lines = atoi(options[1]);
	/*if(*number_of_lines == 0)
	{
		char errorstr[75 + strlen(options[1])];
		sprintf(errorstr, "The parameter is responsible for the number of lines NaN, or it is zero.(%s)", options[1]);
		PrintError(errorstr, 1);
	}*/
	for(unsigned int j = 0; j < allowed_options_length; j++)
	{
		if(strcmp(options[3], allowed_options[j]) == 0)
		{
			unknown_option_index = -1;
			break;
		}
		else
		{		
			unknown_option_index = 3;
		}
	}
	if(unknown_option_index > -1)
	{
		char errorstr[30 + strlen(options[unknown_option_index])];
		sprintf(errorstr, "Unknown option was given! (%s)", options[unknown_option_index]);
		PrintError(errorstr, 1);
	}
}

void SwapString(char * string1[], char * string2[])
{
	char *temp = *string1;
	*string1 = *string2;
	*string2 = temp;
}

void PrintError(char * string, int exit_code)
{
	fprintf(stderr, "\n[!] Error: %s.\n\n", string);
	exit(exit_code);
}
