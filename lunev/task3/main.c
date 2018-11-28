#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double sum_series (long long int n)
{
    long int i;
	long double s=0.0;
	long double con = 0.577215664901532860606512;
	s=con + log (2*n); // a sum ( 1 + 1/2 + 1/3 ... + 1/2n )
    // to get what we want we need minus ( 1/2 + 1/4 + 1/6 ... ) two times
    // 1/2 + 1/4 + 1/8 ...=1 (as the sum of an infinitely decreasing progression)
    // 1/3*( 1/2 + 1/4 + 1/8 ... )=1/6 + 1/12 + ... = 1/3
    // 1/5*( 1/2 + 1/4 + 1/8 ... )=1/10 + 1/20 + ... = 1/5
    // then 1/2 + 1/4 + 1/6 ... = 1/1 + 1/3 + 1/5 ...
	for (i=1; i<2*n; i=i+2)
        s=s - (long double) 2/i;
	return s;

}


int main (int argc, char *argv[])
{
    long long int n = atoi(argv[1]);
	printf("%.17f", sum_series (n));
}
//-0.69314718055994530941723212145817656807550013436025525412

