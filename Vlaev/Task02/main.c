#include <stdio.h>
#include <stdlib.h>
int a[100];
int res=0;
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
       res++;
     }
     i++;
     j--;
   }
} while (i <= j);

if (i < last)
   hoarasort(a, i, last);
if (first < j)
   hoarasort(a, first,j);
}*/

const int wrong_com=666;
char parse_command(char* com, char *comtype,long long int *num)
{
    int sost=0;
    int i=0;
   /*  while (com[i]!='\0')
    {
        printf("%c\n",com[i]);
        i++;
    }
    i=0;*/
    *num=0;
    while (sost<100)
    {
       // printf("%d\n",sost);
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
                        *comtype=0;
                        sost=3;
                    }
                    else if (com[i]=='t')
                    {
                        i+=3;
                        *comtype=1;
                        sost=3;
                    }
                    else sost=wrong_com;
                    break;

                }
            case 3:
                {
                    if (com[i]=='\0')
                    {
                        sost=wrong_com;
                    }
                    else sost=4;
                    break;
                }
            case 4:
                {
                    if (com[i]=='\0')
                    {
                        return 1;
                    }
                    else
                        if ((com[i]>='0')&&(com[i]<='9'))
                        {
                            *num = (*num) * 10 + com[i] - '0';
                            i++;
                        }
                        else sost=666;
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

    /*for (int i=0;i<argc-1;i++)
    {
            printf("%s\n",argv[i+1]);
    }*/
	long long int from=-INTMAX;
	long long int to=INTMAX+1;

    for (int i=1;i<argc;i++)
    {

        char type=3;
        char * ptype=&type;

        long long int value=-1;
        long long int *pvalue=&value;
        //printf("%d\n",argc);

        char b=parse_command(argv[i],ptype,pvalue);
       // printf("%lld\n",*pvalue);
        if (b==1)
        {
            if (*ptype==0)
            {
                from=(*pvalue);
            }
            if (*ptype==1)
            {
                to=(*pvalue);
            }
        }
    }
    //printf("%d",666);
    int len=0;

   // while (!());
    char c='A';
    int x=0;
    while (c!='\n')
    {
        if (c==' ')
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
            x=0;
        }
        else
        if ((c>='0')&&(c<='9'))
        {
            x=x*10+c-'0';
        }
        c=getchar();
    }
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
    /*int temp=scanf("%d",&x);
    while (!(temp>3))
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
        temp=scanf("%d",&x);
        printf("%d",temp);
    }*/
   // printf("%d",666);
    //int r=0;
    extern hoarasort(int a[], int first, int last);
    hoarasort(a,0,len-1);
    return res;
}
