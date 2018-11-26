#include <stdio.h>
#include <stdlib.h>

FILE *InputFile;
long int NumberOfStrings = 0;

char input(char **);
int choise_sort(char, char **);
int read_file(FILE *, char **);
int print_sorted(char **);
int memory_flush(char **);

int main(int argc, char *argv[])
{
	char SortName = input(argv);
	char **Strings = calloc(NumberOfStrings + 1, sizeof(char *));
	read_file(InputFile, Strings);
	choise_sort(SortName, Strings);
	print_sorted(Strings);
	memory_flush(Strings);
	return 0;
}


char input(char *argv[])
{
	short int Buf = 0;
	while (argv[1][Buf] != '\0')
		NumberOfStrings = 10 * NumberOfStrings + (long int) (argv[1][Buf++] - '0');
	if ((InputFile = fopen((argv[2]), "r")) == NULL)
	{
		printf("Can`t open \"%s\" file. Programm will be closed.\n", argv[2]);
		exit(0);
	}
	else
		return (char) (argv[3][0]);
}


int read_file(FILE *InputFile, char *Strings[])
{
	short int Length;
	int *Buf = calloc(100000, sizeof(int));
	for (long int Line = 0; Line < NumberOfStrings; Line++)
	{
		for (Length = 0; (Buf[Length] = getc(InputFile)) != 10 && Buf[Length] != -1; Length++);
		Strings[Line] = calloc(Length + 1, sizeof(char));
		Strings[Line][Length--] = '\0';
		for (; Length >= 0; Length--)
			Strings[Line][Length] = (char) Buf[Length];
	}
	free(Buf);
	fclose(InputFile);
	return 0;
}


int print_sorted(char **Strings)
{
	for (long int Line = 0; Line < NumberOfStrings; Line++)
		printf("%s\n", Strings[Line]);
	return 0;
}


int memory_flush(char *Strings[])
{
	for (long int Line = 0; Line < NumberOfStrings; Line++)
		free(Strings[Line]);
	free(Strings);
	return 0;
}


int bubble(char **);
int insertion(char **);
int merge(char **, long int, long int);
int quick(char **, long int, long int);
int radix(char **);

int choise_sort(char SortName, char **Strings)
{
	switch (SortName)
	{
		
		case 'b':
			bubble(Strings);
			break;
		case 'i':
			insertion(Strings);
			break;
		case 'm':
			merge(Strings, 0, NumberOfStrings - 1);
			break;
		case 'q':
			quick(Strings, 0, NumberOfStrings - 1);
			break;
		case 'r':
			radix(Strings);
			break;
		default:
			printf("Name of sorting algorithm is WRONG!\n");
			break;
	}
	return 0;
}


//It returns 1 if 1-st string is greater than 2-nd one.
int str_compare(long int Str1, long int Str2, char **Strings)
{
	int Buf;
	for (Buf = 0; Strings[Str1][Buf] == Strings[Str2][Buf] && Strings[Str1][Buf] != '\0' && Strings[Str2][Buf] != '\0'; Buf++);
	if (Strings[Str1][Buf] == '\0' || (Strings[Str1][Buf] < Strings[Str2][Buf] && Strings[Str2][Buf] != '\0'))
		return 0;
	else
		return 1;
}


int bubble(char **Strings)
{
	long int i, j;
	char *Buf;
	for (i = 0; i < NumberOfStrings - 1; i++)
		for (j = 1; j < NumberOfStrings - i; j++)
			if (str_compare(j - 1, j, Strings))
			{
				Buf = Strings[j-1];
				Strings[j-1] = Strings[j];
				Strings[j] = Buf;
			}
	return 0;
}


int insertion(char **Strings)
{
	long int i, j;
	for (i = 1; i < NumberOfStrings; i++)
	{
		Strings[NumberOfStrings] = Strings[i];
		for (j = i - 1; j >= 0 && str_compare(j, NumberOfStrings, Strings); j--)
			Strings[j+1] = Strings[j];
		Strings[j + 1] = Strings[NumberOfStrings];
	}	
	return 0;
}


int merge_union(char **Strings, long int Left, long int Middle, long int Right)
{
	long int LeftLength = Middle - Left + 1;
	long int RightLength = Right - Middle;
	char **BufArray = calloc(LeftLength + RightLength, sizeof(char *));
	for (long int Buf = 0; Buf < RightLength; Buf++)
	{
		BufArray[Buf] = Strings[Left + Buf];
		BufArray[LeftLength + Buf] = Strings[Middle + 1 + Buf];
	}
	if (LeftLength > RightLength)
		BufArray[LeftLength - 1] = Strings[Middle];
	long int i = 0, j = 0;
	for ( ; Left <= Right ; Left++ )
		if ( j >= RightLength || (i < LeftLength && j < RightLength && str_compare(LeftLength + j, i, BufArray)) )
			Strings[Left] = BufArray[i++];
		else 
			Strings[Left] = BufArray[LeftLength + j++];
	free(BufArray);
	return 0;
}


int merge(char **Strings, long int Left, long int Right)
{
	if (Left < Right)
	{
		long int Middle = (Left + Right) / 2;
		merge(Strings, Left, Middle);
		merge(Strings, Middle + 1, Right);
		merge_union(Strings, Left, Middle, Right);
	}
	return 0;
}


int quick_partition(char **Strings, long int Left, long int Right)
{
	char *Buf;
	long int Support = Left;
	for ( ; Left < Right ; Left++ )
		if (str_compare(Right, Left, Strings))
		{				
			Buf = Strings[Support];
			Strings[Support++] = Strings[Left];
			Strings[Left] = Buf;
		}
	
	Buf = Strings[Support];
	Strings[Support] = Strings[Right];
	Strings[Right] = Buf;
	return Support;
}


int quick(char **Strings, long int Left, long int Right)
{
	if ( Left < Right )
	{
		long int Support = quick_partition(Strings, Left, Right);
		quick(Strings, Left, Support - 1);
		quick(Strings, Support + 1, Right);
	}
	return 0;
}


int counting(char **Strings, char **Copy, long int Left, long int Right, long int Depth)
{
	long int *Symbols = calloc(256, sizeof(long int));
	long int Buf, DifferentSymbols = 0;
	for (Buf = Left; Buf <= Right; Buf++)
	{
		Symbols[Strings[Buf][Depth]]++;
		if (Symbols[Strings[Buf][Depth]] == 1)
			DifferentSymbols++;
	}
	long int Diff = DifferentSymbols;
	char *RealSymbols = calloc(Diff, sizeof(char));
	long int *OrderSymbols = calloc(256, sizeof(long int));
	for ( Buf = 255; DifferentSymbols != 0; Buf--)
		if (Symbols[Buf] != 0)
			RealSymbols[--DifferentSymbols] = (char) Buf;
	OrderSymbols[RealSymbols[0]] = Left;
	for ( Buf = 1; Buf < Diff; Buf++ )
			OrderSymbols[RealSymbols[Buf]] = OrderSymbols[RealSymbols[Buf - 1]] + Symbols[RealSymbols[Buf - 1]];
	for ( Buf = Left ; Buf <= Right; Buf++ )
		Copy[OrderSymbols[Strings[Buf][Depth]]++] = Strings[Buf];
	for ( Buf = Left ; Buf <= Right; Buf++ )
		Strings[Buf] = Copy[Buf];
	for ( Buf = 0; Buf < Diff; Buf++ )
		if ( Symbols[RealSymbols[Buf]] > 1 && RealSymbols[Buf] != '\0' && RealSymbols[Buf] != '\n')
			counting(Strings, Copy, Buf > 1 ? OrderSymbols[RealSymbols[Buf - 1]] : Left, OrderSymbols[RealSymbols[Buf]] - 1, Depth + 1);
	free(RealSymbols);
	free(Symbols);
	free(OrderSymbols);

	return 0;
}


int radix(char **Strings)
{
	char **Copy = calloc(NumberOfStrings + 1, sizeof(char *));
	counting(Strings, Copy, 0, NumberOfStrings - 1, 0);
	free(Copy);
	return 0;
}
