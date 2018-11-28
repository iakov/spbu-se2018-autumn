#include <stdio.h>
#include <math.h> 

int main(){
double ans=0.0;
long long int i,n,z;
scanf("%lli", &n);
z=n*2+2;
n=round(n/2);
for(i=1;i<=n;i++){
	ans = (2./(z+1)) + (2./z) + ans;
	z += 4;
}
	printf("%.17f",-ans);
return(0);
}
