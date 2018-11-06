#include <stdio.h>

int main(){
double ans=0.0;
long long int i,n;
scanf("%lli", &n);
for(i=n+1;i<=n*2;i++){
	ans = ans + (1./i);
}
	printf("%.17f",-ans);
return(0);
}
