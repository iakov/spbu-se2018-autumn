#include <stdio.h>

int main(){
double ans=0.0;
long long int i,n;
scanf("%lli", &n);
for(i=1;i<=n;i += 2){
	ans = ans + (1./i)-(1./(i+1));
}
	printf("%.17f",-ans);
return(0);
}
