#include <stdio.h>
#include <limits.h>

int from, to, i, j, count, minus, k;
int symbol, vector[100], newvector[100];
char inpar[40];

extern Sort(int array[], int n);

void ChInPar(int argc, char * argv[])
{
	count = 0;
	for(i = 1; i < argc; i++)
	{
		j = 0;
		while(argv[i][j] != '\0')
		{
			inpar[count] = argv[i][j];
			count++;
			j++;
		}
	}
}

void SetToAndFrom(char mass[])
{
	for(i = 0; i < count; i++)
	{
		if(inpar[i] == 't')
		{
			to = 0;
			if(mass[i + 3] == '-')
			{
				minus = -1; j = i + 4;
			}
			else
			{
				minus = 1; j = i + 3;
			}
			while((mass[j] >= '0') && (mass[j] <= '9'))
			{
				to = 10 * to + mass[j] - '0';
				j++;
			}
			to *= minus;
		}
		if(inpar[i] == 'f')
		{
			from = 0;
			if(mass[i + 5] == '-')
			{
				minus = -1; j = i + 6;
			}
			else
			{
				minus = 1; j = i + 5;
			}
			while((mass[j] >= '0') && (mass[j] <= '9'))
			{
				from = 10 * from + mass[j] - '0';
				j++;
			}
			from *= minus;
		}
	}
}

void Scan()
{
	symbol = getchar();
	count = 0;
	while(symbol != '\n')
	{
		if(symbol == ' ')
		{
			symbol = getchar();
		}
		else 
		{
			if(symbol == '-')
			{
				symbol = getchar();
				while (symbol >= '0' && symbol <= '9')
				{
					vector[count] = vector[count] * 10 + symbol - '0';
					symbol = getchar();
				}
				vector[count] = -vector[count];
				count++;
			}
			else
			{
				while (symbol >= '0' && symbol <= '9')
				{
					vector[count] = vector[count] * 10 + symbol - '0';
					symbol = getchar();
				}
				count++;
			}
		}
	}
}

void Change()
{
	k = 0;
	for(i = 0; i < count; i++)
	{
		if(vector[i] < from)
		{
			fprintf(stdout, "%d ", vector[i]);
		}
		if(vector[i] > to)
		{
			fprintf(stderr, "%d ", vector[i]);
		}
		if((vector[i] >= from) && (vector[i] <= to))
		{
			newvector[k] = vector[i];
			k++;
		}
	}
}

int main(int argc, char * argv[])
{
	from = INT_MIN; to = INT_MAX;
	ChInPar(argc, argv); 
	SetToAndFrom(inpar); 
	Scan(); 
	Change(); 
	printf("%d \n", Sort(newvector, k));
	return Sort(newvector, k);
}
