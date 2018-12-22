#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//array of links to strings
int Strings[100000000][2];

void SwapStrings(int i, int j){
	int buf = Strings[i][0];
	Strings[i][0] = Strings[j][0];
	Strings[j][0] = buf;
	buf = Strings[i][1];
	Strings[i][1] = Strings[j][1];
	Strings[j][1] = buf;
}

void bubbleSort(char *text, int N){
	int i, j;
	for(i=0; i<N; i++){
		for(j=i+1; j<N; j++){
			if(strcmp(&text[Strings[i][0]],&text[Strings[j][0]])==1){
				SwapStrings(i,j);
			}
		}
	}
}

void insertionSort(char *text, int N){
	int i, j;
    for (i=0; i<N; i++){
        j=0;
        for (; j<i && strcmp(&text[Strings[i][0]],&text[Strings[j][0]])>0; j++){
        }
        for (; j<i; j++){
            SwapStrings(i,j);
        }
    }
}

void mergeSort(char *text, int N, int start){
	int len = N - start;
    if(len<1){
    	return;
    }
	int m = start + len/2;
    mergeSort(text, m, start);
    mergeSort(text, N, m+1);
    int Buffer[len][2];
    int PosLeft=start, PosRight=m+1, Pos=0, i, j=0;
    while(PosLeft<=m && PosRight<=N){
        if(strcmp(&text[Strings[PosRight][0]], &text[Strings[PosLeft][0]])>0){
            Buffer[Pos][0] = Strings[PosLeft][0];
            Buffer[Pos++][1] = Strings[PosLeft++][1];
        }
        else{
            Buffer[Pos][0] = Strings[PosRight][0];
            Buffer[Pos++][1] = Strings[PosRight++][1];
        }
    }
    while(PosRight<=N){
    	Buffer[Pos][0] = Strings[PosRight][0];
    	Buffer[Pos++][1] = Strings[PosRight++][1];
  	}
	while(PosLeft<=m){
		Buffer[Pos][0] = Strings[PosLeft][0];
		Buffer[Pos++][1] = Strings[PosLeft++][1];
  	}
    for(i=start; i<=start+len; i++){
        Strings[i][0]=Buffer[j][0];
        Strings[i][1]=Buffer[j][1];
        j++;
	}
}

void quickSort(char *text, int start, int N){
    if (N-start<=1){
        return;
    }
    int L = start, R = N;
    int M=(N+start)/2;
    while (L <= R){
        while(M!=L && strcmp(&text[Strings[M][0]],&text[Strings[L][0]])>0){
            L++;
        }
        while(M!=R && strcmp(&text[Strings[R][0]],&text[Strings[M][0]])>0){
            R--;
        }
        if (L <= R){
            SwapStrings(L,R);
            if(M==L){
            	M=R;
            	L++;
            }
            else{
            	if(M==R){
            		M=L;
            		R--;
            	}
            	else{
            		L++;
            		R--;
            	}
            }
        }
    }
	if (start < R){
        quickSort(text, start, R);
    }
    if (L < N){
        quickSort(text, L, N);
	}
}

void sink(char *text, int i, int max){
	int big_index, childl, childr;
	while(i < max){
   		big_index = i;
    	childl = 2 * i + 1;
    	childr = childl + 1;
    	if(childl < max && strcmp(&text[Strings[childl][0]],&text[Strings[big_index][0]])>0){
    		big_index = childl;
    	}
    	if (childr < max && strcmp(&text[Strings[childr][0]],&text[Strings[big_index][0]])>0){
    		big_index = childr;
    	}
    	if (big_index == i){
    		return;
    	}
    	SwapStrings(i, big_index);
    	i = big_index;
    }
}

void heapSort(char *text, int N){
	int index = (N / 2) - 1 ;
	while ( index >= 0 ){
    	sink(text, index, N);
    	index--;
	}
	int end = N - 1;
	while(end >= 0) {
		SwapStrings(0, end);
    	sink(text, 0, end);
    	end -= 1;
   }
}

void FunctionDef(char *text, int N, char Name){
	switch (Name)
    {
    case 'h':
        bubbleSort(text, N);
        break;
    case 'i':
        insertionSort(text, N);
        break;
    case 'm':
        mergeSort(text, N-1, 0);
        break;
    case 'q':
        quickSort(text, 0, N);
        break;
    case 'b':
        heapSort(text, N);
        break;
    case 'r':
        heapSort(text, N);
        break;
    default:
        printf("Invalid name of algorythm\n");
        exit(1);
        break;
    }
}

int main(int argc, char **argv)
{
	int i=0, N, j=0, z=0;
    if (argc != 4){
        printf("Invalid number of arguments!\n");
        exit(1);
    }
    N = atoi(argv[1]);
  if(N==0){
  	return(0);
  } 
	FILE *f=fopen(argv[2], "r");
	if(f==0){
	printf("Failed to open file\n");
	exit(2);
	}
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *text = (char*) malloc(size*sizeof(char)+1);
	if(text==0){
	printf("Failed to malloc memory\n");
	}
	Strings[0][0]=0;
	while ((text[i] = fgetc(f)) != EOF) {
		z++;
		if(text[i]=='\n'){
			Strings[j+1][0]=i+1;
			Strings[j][1]=z;
			z=0;
			j++;
		}
		i++;
	}
	text[i]='\n';
	if(j<N){
		N=j;
	}
	Strings[j][1]=z+1;
	fclose(f);
	if(strcmp(argv[3],"bubble")==0 || strcmp(argv[3],"insertion")==0 || strcmp(argv[3],"heap")==0 || strcmp(argv[3],"merge")==0 || strcmp(argv[3],"radix")==0 || strcmp(argv[3],"quick")==0){
	 FunctionDef(text, N, argv[3][0]);
	}
	else{
		printf("Invalid name of algorythm");
		exit(1);
	}
	for(i=0;i<N;i++){
		for(j=0;j<Strings[i][1];j++){
			printf("%c",text[Strings[i][0]+j]);
		}
	}
	free(text);
	return(0);
}
