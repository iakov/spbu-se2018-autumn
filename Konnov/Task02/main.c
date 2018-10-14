#include <stdio.h>

int i, From, To, counter, cardo, Vector[100], NewVector[100];
char checker, Symbol;

extern Sort(int Limited[], int counter);

int main(int argc, char * argv[])
{
	From = -0x80000000;
	To = 0x7FFFFFFF;
	for(i = 0; i < argc; i++) //checking input parameters
	{
		if((argv[i][0] == '-') && (argv[i][1] == '-'))
		{
			if((argv[i][6] == '=') && (argv[i][2] == 'f') && (argv[i][3] == 'r') && (argv[i][4] == 'o') && (argv[i][5] == 'm'))
			{
				if(argv[i][7] == '-')
				{
					From = 0;
					counter = 8;
					while(argv[i][counter] != '\0')
					{
						From = From * 10 + argv[i][counter] - '0';
						counter++;
					}
					From = -From;
				}
				else
				{
					From = 0;
					counter = 7;
					while(argv[i][counter] != '\0')
					{
						From = From * 10 + argv[i][counter] - '0';
						counter++;
					}
				}
			}
			if((argv[i][4] == '=') && (argv[i][2] == 't') && (argv[i][3] == 'o'))
			{
				if(argv[i][5] == '-')
				{
					To = 0;
					counter = 6;
					while(argv[i][counter] != '\0')
					{
						To = To * 10 + argv[i][counter] - '0';
						counter++;
					}
					To = -To;
				}
				else
				{
					To = 0;
					counter = 5;
					while(argv[i][counter] != '\0')
					{
						To = To * 10 + argv[i][counter] - '0';
						counter++;
					}
				}
			}
			if((argv[i][6] != '=') && (argv[i][2] == 'f'))
			{
				checker = 'f';
			}
			if((argv[i][4] != '=') && (argv[i][2] == 't'))
			{
				checker = 't';
			}
		}
		if((argv[i][0] == '-') && (argv[i][1] != '-'))
		{
			if((argv[i][1] >= '0') && (argv[i][1] <= '9'))
			{
				if(checker == 'f')
				{
					From = 0;
					counter = 1;
					while(argv[i][counter] != '\0')
					{
						From = From * 10 + argv[i][counter] - '0';
						counter++;
					}
					From = -From;
					checker = 'i';
				}
				if(checker == 't')
				{
					To = 0;
					counter = 1;
					while(argv[i][counter] != '\0')
					{
						To = To * 10 + argv[i][counter] - '0';
						counter++;
					}
					To = -To;
					checker = 'i';
				}
			}
		}
		if((argv[i][0] >= '0') && (argv[i][0] <= '9'))
		{
			if(checker == 'f')
			{
				From = 0;
				counter = 0;
				while(argv[i][counter] != '\0')
				{
					From = From * 10 + argv[i][counter] - '0';
					counter++;
				}
				checker = 'i';
			}
			if(checker == 't')
			{
				To = 0;
				counter = 0;
				while(argv[i][counter] != '\0')
				{
					To = To * 10 + argv[i][counter] - '0';
					counter++;
				}
				checker = 'i';
			}
		}	
	}
	Symbol = getchar();
	cardo = 0;
	while(Symbol != '\n')
	{
		if(Symbol == ' ')
		{
			Symbol = getchar();
		}
		else 
		{
			if(Symbol == '-')
			{
				Symbol = getchar();
				while (Symbol >= '0' && Symbol <= '9')
				{
					Vector[cardo] = Vector[cardo] * 10 + Symbol - '0';
					Symbol = getchar();
				}
				Vector[cardo] = -Vector[cardo];
				cardo++;
			}
			else
			{
				while (Symbol >= '0' && Symbol <= '9')
				{
					Vector[cardo] = Vector[cardo] * 10 + Symbol - '0';
					Symbol = getchar();
				}
				cardo++;
			}
		}
	}
	counter = 0;
	for(i = 0; i < cardo; i++)
	{
		if(Vector[i] < From)
		{
			fprintf(stdout, "%d ", Vector[i]);
		}
		if(Vector[i] > To)
		{
			fprintf(stderr, "%d ", Vector[i]);
		}
		if((Vector[i] >= From) && (Vector[i] <= To))
		{
			NewVector[counter] = Vector[i];
			counter++;
		}
	}
	return Sort(&NewVector, counter);
}

