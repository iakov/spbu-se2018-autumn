#include <stdio.h>
#include <math.h> 

int main(){
double ans=0.0;
long long int i,n,z,r=0;
scanf("%lli", &n);
if(n % 2==1){
	n=n-1;
	r=1;
}
z=n*2+2;
if(r==1){
	z += 1;
}
n=round(n/2);
for(i=1;i<=n;i++){
	ans = ans + (2./z)+(2./(z+1));
	z += 4;
}
if(r==1){
	ans = ans + (1./(z-1));
}
	printf("%.17f",-ans);
return(0);
}
