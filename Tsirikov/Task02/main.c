#include <stdio.h>
#include <stdlib.h>

char IsDown = 0, IsHigh = 0;
int Down, High;

int read_parametrs(int, char **);
int read_massive(int *);
extern int __sort(int, int*);

int main(int argc, char *argv[])
{
	read_parametrs(argc, argv);
	int *massive = calloc(100, sizeof(int));
	int AmountOfElements = read_massive(massive);
	int Transpositions = __sort(AmountOfElements, massive);
	free(massive);
	return Transpositions;
}


int read_parametrs(int argc, char *argv[])
{
	char CharBuf;
	int NumberBuf = 0;
	for (int i = 1, j = 0; i < argc; i++, j = 0)
		while ( (CharBuf = argv[i][j++]) != '\0' )
			if ( (IsDown == 1 || IsHigh == 1) && (CharBuf == '-' || (CharBuf >= '0' && CharBuf <= '9')) )
			{
				NumberBuf = CharBuf == '-' ? (int) (argv[i][j++] - '0') : (int) (CharBuf - '0');
				while (argv[i][j] != '\0')
					
					NumberBuf = NumberBuf * 10 + (int) (argv[i][j++] - '0');
				
				if ( CharBuf =='-' )

					NumberBuf *= -1;
				
				if (IsDown == 1)
				{
					Down = NumberBuf;
					IsDown++;
				}
				else
				{
					High = NumberBuf;
					IsHigh++;
				}
			}
			else switch (CharBuf)
			{
				case 'f':
					IsDown++;
					break;
				case 't':
					IsHigh++;
					break;
				default:
					break;
			}
	return 0;
}


int read_massive(int *massive)
{
	int Buf1 = getchar(), Buf0 = '\0';
	int Counter = 0, Sign = 1;
	while ( Buf0 != EOF )
	{
		if ( Buf1 == '-' )
			
			Sign = -1;

		else if ( Buf1 >= '0' && Buf1 <= '9' )
		
			massive[Counter] = massive[Counter] * 10 + (int) (Buf1 - '0');
		
		else if ( Buf0 >= '0' && Buf0 <= '9' )
		{
			massive[Counter] *= Sign;
			if (IsDown != 0 && massive[Counter] <= Down)
			
				fprintf(stdout, "%d ", massive[Counter]);
			
			if (IsHigh != 0 && massive[Counter] >= High)
			
				fprintf(stderr, "%d ", massive[Counter]);
			
			if ( !(IsDown != 0 && massive[Counter] <= Down) && !(IsHigh != 0 && massive[Counter] >= High) )
			
				Counter++;

			else

				massive[Counter] = 0;

			Sign = 1;
		}
		Buf0 = Buf1;
		Buf1 = getchar();
	}
	return Counter;
}
