#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int a[100];

const long long int INTMAX=4294967296;
/*void hoarasort(int a[], int first, int last)
{

int i = first, j = last;
int tmp, x = a[(first + last) / 2];

do {
   while (a[i] < x)
     i++;
   while (a[j] > x)
     j--;

   if (i <= j)
   {
     if (i < j)
     {
       tmp=a[i];
       a[i]=a[j];
       a[j]=tmp;
     }
     i++;
     j--;
   }
} while (i <= j);

if (i < last)
   hoarasort(a, i, last);
if (first < j)
   hoarasort(a, first,j);
}
*/
const int wrong_com=666;
char parse_command(char * com,int comlen,long long int * from, long long int * to)
{
    int sost=0;
    int i=0;
    long long int num=0;
    int type=0;
    while (sost<100)
    {

        switch (sost)
        {
            case 0:
                {
                    if (com[i]=='-')
                    {
                        i++;
                        sost=1;
                    }
                    else sost=wrong_com;
                    break;
                }
            case 1:
                {
                    if (com[i]=='-')
                    {
                        i++;
                        sost=2;
                    }
                    else sost=wrong_com;
                    break;
                }
            case 2:
                {
                    if (com[i]=='f')
                    {
                        i+=5;
                        type=0;
                        sost=3;
                    }
                    else if (com[i]=='t')
                    {
                        i+=3;
                        type=1;
                        sost=3;
                    }
                    else sost=wrong_com;
                    break;

                }
            case 3:
                {
                    if (com[i]=='\0')
                    {
                        if (type==0)
                        {
                            *from=num;
                        }
                        else
                        {
                            *to=num;
                        }
                        return '1';
                    }
                    else if (com[i]=='-')
                    {
                        if (type==0)
                        {
                            *from=num;
                        }
                        else
                        {
                            *to=num;
                        }
                        sost=1;
                        num=0;
                        i++;
                    }
                    else  if ((com[i]>='0')&&(com[i]<='9'))
                            {
                                num = num * 10 + com[i] - '0';
                                i++;
                            }
                            else sost=wrong_com;
                    break;
                }
            case 666:
                {
                    return 0;
                }
        }
    }
    return 0;
}
int main(int argc, char* argv[])
{

	long long int from=-INTMAX;
	long long int to=INTMAX+1;
	char commass [100];
	char * command=commass;
	int charlen=0;
    for (int i=1;i<argc;i++)
    {
        int j=0;
        int doplen=0;

        while (argv[i][j]!='\0')
        {
            if (argv[i][j]!=' ')
            {
                command[j+charlen]=argv[i][j];
                doplen++;
            }
            j++;
        }
        charlen+=doplen;
    }
    char b=parse_command(command,charlen,&from,&to);

    if (b=='1')
    {


        int len=0;
        int x=0;
        char c;
            c=getchar();
        char got_number=0;
        while (c!='\n')
        {


            if (c==' ')
            {
                got_number=1;
                if (x<=from)
                {
                    printf("%d ",x);
                }
                else
                if (x>=to)
                {
                   fprintf(stderr,"%d ",x);
                }
                else
                {
                    a[len]=x;
                    len++;
                }
                x=0;
            }
            else
            if ((c>='0')&&(c<='9'))
            {
                x=x*10+c-'0';
                got_number=0;
            }
            c=getchar();
        }


        if (got_number==0)
        {
            if (x<=from)
            {
                printf("%d ",x);
            }
            else
            if (x>=to)
            {
                fprintf(stderr,"%d ",x);
            }
            else
            {
                a[len]=x;
                len++;
            }
        }


        int buf_mass[100];
        for (int i=0;i<len;i++)
        {
            buf_mass[i]=a[i];
        }
        extern hoarasort(int a[], int first, int last);
        hoarasort(a,0,len-1);
        int res=0;
        for (int i=0;i<len;i++)
        {
            res+=(a[i]!=buf_mass[i]);
        }
        return res;
    }
}
