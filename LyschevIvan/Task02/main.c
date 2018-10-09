#include <stdio.h>
#include <string.h>
extern void sort(int *mas,int masMask[],int masLen);
int main(int argc, char *argv[]) {
    int i,k,minFlag=0,minV=0,maxFlag=0,maxV=0;
    int minZn=1,maxZn=1;
    char str[100];
    //zeroing string
    for(i=0;i<100;i++){
        str[i]='0';
    }
    //connecting strings
    if(argc>1){
        snprintf(str, sizeof(str),"%s",argv[1]);
    }
    for(i=2;i<argc;i++){
        snprintf(str, sizeof(str),"%s%s",str,argv[i]);
    }

    //parsing parameters
    for (int i = 0; i < sizeof(str); i++) {
        if(str[i]=='='){
            if(str[i-1]=='m'){
                minFlag=1;
                k=1;
                if(str[k+i]=='-') {
                    minZn=-1;
                    k++;}

                while((str[i+k]<='9')&&(str[i+k]>='0')){
                    minV=minV*10+((int)str[i+k]-'0');
                    k++;}
                minV*=minZn;
            }
            else{
                maxFlag=1;
                k=1;
                if(str[k+i]=='-') {
                    maxZn=-1;
                    k++;}
                while((str[i+k]<='9')&&(str[i+k]>='0')){
                    maxV=maxV*10+((int)str[i+k]-'0');
                    k++;}
                maxV*=maxZn;
            }
        }
    }
    //initializing array
    int numbers[100];
    //zeroing array
    for(i=0;i<100;i++){
        numbers[i]=0;
    }
    i=0;
    int masLen=0;
    //reading input values
    while(scanf("%i",&numbers[i])){
        i++;
        masLen++;
    }
    int numbersMask[masLen],numbCopy[masLen];
    //doing copy of unsorted array
    memcpy(numbCopy,numbers, sizeof(int)*masLen);
    //initializing array mask
    for(i=0;i<masLen;i++){
        numbersMask[i]=i;
    }
    //filling array mask
    for(i=0;i< masLen;i++){
        if ((numbers[i] <= minV)&&(minFlag)) {
            numbersMask[i] = -1;
            fprintf(stdout, "%d ", numbers[i]);
        }
        if ((numbers[i] >= maxV)&&(maxFlag)) {
            numbersMask[i] = -1;
            fprintf(stderr, "%d ", numbers[i]);
        }
    }
    //sorting "numbers" using mask
    sort(numbers,numbersMask,masLen);
    int changesCount=0;
    //counting changed positions
    for (i = 0; i <masLen ; i++) {
        if(numbCopy[i]!=numbers[i])
            changesCount++;
    }
    //show sorted numbers
    printf("Sorted: ");
    for (int i = 0; i < masLen; ++i) {
        if(numbersMask[i]!=-1){
            printf("%d ",numbers[i]);
        }
    }
    return changesCount;
}
