#include <stdio.h>
#include <math.h> 

int main(){
double ans=0.0;
long long int i,n,z;
scanf("%lli", &n);
while(n % 3>0){
	n = n-1;
}
z=n/3*4+2;
n = n/3;
for(i=1;i<=n;i++){
	ans = ans + (2./z)+(2./(z+1));
	z += 4;
}
	printf("%.17f",-ans);
return(0);
}
