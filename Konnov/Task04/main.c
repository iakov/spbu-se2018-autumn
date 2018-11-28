#include<stdio.h>

void other()
{
	printf("\n you HACKED me \n");
}

void input()
{
	char buf[20];
	printf("\n enter something: \n");
	scanf("%s", &buf);
	printf("\n carpe diem \n", buf);
}

int main()
{
	input();
	return 0;
}
