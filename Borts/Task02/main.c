/*

Предполагается, что параметры будут вводиться всегда в стандартном виде, как в условии, без дополнительных пробелов. (--from=1547).

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>

extern void QuickSort(int s_arr[], int first, int last);

const char * allowedOptions[] = {"--from=", "--to="}; // Массив разрешённых параметров.
const unsigned int allowedOptionsLength = sizeof allowedOptions / sizeof allowedOptions[0]; // Вычисление кол-ва параметров в массиве выше.

void checkOptions(int length, char * options[], int *fromAddress, int *toAddress);

int main(int argc, char * inputstring[])
{
	int from = INT_MIN, to = INT_MAX;

	if(argc > 1)
		checkOptions(argc, inputstring, &from, &to);

	int *numbers = NULL;
	numbers = (int*)calloc(1, sizeof(int));
	unsigned int numberCounter = 0;
	bool numberSign = true;

	printf("\n\t\t\t\t\t============[ !ATTENTION! ]============\n");
	printf("Correct reading occurs only if you follow a number of rules:\n1) The string with numbers does not begin and does not end with a space character.\n2) Numbers are entered in a row, without extraneous characters (only 0..9, ' ', '-'), and are separated from each other by a space character.");
	printf("\n\t\t\t\t\t=======================================\n");

	printf("Enter a set of numbers to sort:\n");

	while(true)
	{
		char tempchar = getchar();

		if(tempchar == '\n')
		{
			if(!numberSign)
				numbers[numberCounter] *= -1;
			break;
		}
		if((tempchar >= '0') && (tempchar <= '9'))
			numbers[numberCounter] = numbers[numberCounter] * 10 + (tempchar - '0');
		else if(tempchar == '-')
			if(numbers[numberCounter] != 0)
			{
				printf("\n[!] Error: Detected extraneous characters. The sign \"-\" is in the middle of the number.\n");
				exit(EXIT_FAILURE);			
			}
			else
				numberSign = false;
		else if((tempchar == ' '))
		{			
			if(!numberSign)
				numbers[numberCounter] *= -1;
			numberSign = true;
			numberCounter++;
			numbers = (int*)realloc(numbers, (numberCounter+1)*sizeof(int));
			numbers[numberCounter] = 0;
		}
		else
		{
			printf("\n[!] Error: Detected extraneous characters. Violated the rules for entering numbers.\n");
			exit(EXIT_FAILURE);
		}

	}

	int *numbersclone = NULL;
	unsigned int counter = 0;
	numbersclone = (int*)calloc(1, sizeof(int));
	for(int i=0; i <= numberCounter; ++i)
	{
		if((numbers[i] > from) && (numbers[i] < to))
		{

			numbersclone[counter] = numbers[i];
			++counter;
			numbersclone = (int*)realloc(numbersclone, (counter + 1) * sizeof(int));
		}
		else if(numbers[i] < from)
			fprintf(stdout, "%d ", numbers[i]);
		else if(numbers[i] > to)
			fprintf(stderr, "%d ", numbers[i]);
	}

	free(numbers);
	numbers = (int*)calloc(counter + 1, sizeof(int));
	memcpy(numbers, numbersclone, (counter + 1) * sizeof(int));
	
	QuickSort(numbersclone, 0, counter);

	unsigned int changedposition = 0;
	for(int i=0; i < counter; ++i)
	{
		if(numbers[i] != numbersclone[i+1])
			++changedposition;
	}

	free(numbers);
	free(numbersclone);

	return changedposition;
}

void checkOptions(int length, char * options[], int *fromAddress, int *toAddress) // Проверка переданных параметров и запись их значений.
{
	int UnknownOptionIndex = -1;

	for(int i = 1; i < length; i++) // Цикл перебора введённых параметров.
	{
		for(int j = 0; j < allowedOptionsLength; j++) // Подцикл сравнения введённых параметров с разрешёнными.
		{
			if((strstr(options[i], allowedOptions[j])-options[i]+1) == 1) // Проверка, что найдена подстрока(параметр) и она начинаетс с 1 символа.
			{
				UnknownOptionIndex = -1;
				int FoundArg = 0;			
				for (int m = (strstr(options[i], "=")-options[i]+1); m < strlen(options[i]); m++) // Посимвольный перебор параметра начиная со знака, следующего за "=".
				{
					if((options[i][m] >= '0') && (options[i][m] <= '9')) // Проверка, что текущий символ является цифрой.
					{
						if(FoundArg == 0)
							FoundArg = options[i][m] - '0';
						else 
							FoundArg = FoundArg * 10 + options[i][m] - '0';
					}
					else if(options[i][m] == '=') // Проверка на ошибку ввода (двойной =).
					{
						printf("\n[!] Error: Wrong options format (two characters equals)\n");
						exit(EXIT_FAILURE);
					}
					else // Иные ошибки, допущенные при вводе.
					{
						printf("\n[!] Error: Detected extraneous characters. Characters other than 0..9 are not allowed after the options.\n");
						exit(EXIT_FAILURE);
					}
				}

				if(j == 0)
					*fromAddress = FoundArg;
				else if(j == 1)
					*toAddress = FoundArg;

				break;
			}
			else
				UnknownOptionIndex = i;
		}
		if(UnknownOptionIndex > -1) // Если введённый параметр не найден в списке разрешённых.
		{
			printf("\n[!] Error: Unknown option was given! (%s)\n", options[UnknownOptionIndex]);
			exit(EXIT_FAILURE);
		}
	}
}