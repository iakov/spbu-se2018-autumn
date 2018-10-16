#include <stdio.h>

extern int sort(int len, int mas[]);


int main (int argc, char* argv[])
{
   int i=1, from= -2147483647, to = 2147483647, j, s=0;
   for ( i = 1; i < argc ; i++)
   {

       if (argv [i] [0]== '-' && argv [i] [1]== '-' && argv [i] [2]== 'f' && argv [i] [3]== 'r' && argv [i] [4]== 'o' && argv [i] [5]== 'm' )
       {
           for (j=6; argv [i] [j] != '\0'; j++)
           {
               if (argv [i] [j] >= '0' && argv [i] [j] <= '9' )
               {
                   s= s*10 + argv [i] [j] - '0';
               }

           }
           from = s;
       }
   }


   s=0;

   for ( i = 1; i < argc ; i++)
   {

       if (argv [i] [0]== '-' && argv [i] [1]== '-' && argv [i] [2]== 't' && argv [i] [3]== 'o' )
       {
           for (j=4; argv [i] [j] != '\0'; j++)
           {
               if (argv [i] [j] >= '0' && argv [i] [j] <= '9' )
               {
                   s= s*10 + argv [i] [j] - '0';
               }

           }
           to = s;
       }
   }



   int mas [100];
   for (i=0; i <100; i++)
   mas [i] = 0;
   int size = 0;
   char c='x';
   while (c!='\n')
   {
       scanf ("%c", &c);
       if (c >= '0' && c <= '9')
       mas [size] = mas[size]*10 + c-'0';
       if (c== ' ')
       size++;
   }
int len=size+1;
   for (i=0; i<=size; i++)
       {
           if (mas[i]<= from)
           {
            printf ("%d ", mas[i]);
            len--;

           }
           if (mas[i] >= to)
           {
            fprintf (stderr, "%d ", mas[i]);
            len--;
           }
       }


    int realmas [len];
    int k=0;
    for (i=0; i<=size; i++)
       {
           if (mas[i]> from && mas[i]<to)
           {
               realmas [k] =mas[i];
               k++;

           }

       }

    int result = sort (len, realmas);


   return result;
}
