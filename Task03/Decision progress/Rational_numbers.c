#include <stdio.h>
#include <math.h> 

int main(){
double ans=0,bufchis=0,bufzna=1;
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
	bufchis = (bufchis*z*(z+1)) + (2*z*bufzna)+(2*(z+1)*bufzna);
	bufzna = bufzna * z * (z+1);
	
	z += 4;
	if((bufzna * z * (z+2)>9223372036854775000)||(bufzna * z * (z+2)<1)){
		ans = ans + (bufchis/bufzna);
		bufzna=1;
		bufchis=0;
	}
}
ans = ans + (bufchis/bufzna);
if(r==1){
	ans = ans + (1./(z-1));
}
	printf("%.17f",-ans);
return(0);
}
