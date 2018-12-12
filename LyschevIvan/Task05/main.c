#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;
void message(char *m)
{
    printf("!%s\n", m);
}
void string_swp(char **string1,char **string2){
    char *swp;
    swp=*string1;
    *string1=*string2;
    *string2=swp;

}
void bubble_sort(char **str){

    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            if((strcmp(str[j],str[j-1]))<0){
                string_swp(&str[j],&str[j-1]);
            }
        }
    }

}

void insertion_sort(char **str){
    char *tmp;
    for (int i = 1; i < n; i++){
    tmp = str[i];
    for (int j = i - 1; j >= 0; j--){
        if(strcmp(tmp, str[j]) <= 0){
        str[j + 1] = str[j];
        str[j] = tmp;}
        }
    }
}


void merge_sort(char **str, int len)
{

    if (len <= 1)
        return;
    int middle = len / 2;
    merge_sort(str, middle);
    merge_sort(str + middle, len - middle);
    char ** tmp = malloc(len * sizeof(char *));
    if (tmp == NULL) {
        message("memory err");
        exit(0);
    }
    int ptr_l = 0, ptr_r = middle, ptr = 0;
    while (ptr_l < middle) {
        if ((ptr_r >= len) || (strcmp(str[ptr_r], str[ptr_l]) > 0))
            tmp[ptr++] = str[ptr_l++];
        else
            tmp[ptr++] = str[ptr_r++];
    }
    while (ptr_r < len)
        tmp[ptr++] = str[ptr_r++];
    for (int i = 0; i < len; i++)
        str[i] = tmp[i];
    free(tmp);

}

void quick_sort(char **str,int l, int r) {
    if (l >= r) {
        return;
    }
    int left2 = l, right2 = r;
    int middle = (r + l) / 2;
    char *tmp = str[middle];
    while (left2 <= right2) {
        while (strcmp(str[left2], tmp) < 0) {
            left2++;
        }
        while (strcmp(str[right2], tmp) > 0) {
            right2--;
        }
        if (left2 <= right2) {
            string_swp(&str[left2++], &str[right2--]);
        }
    }
    if(l<right2) quick_sort(str,l, right2);
    if(left2<r) quick_sort(str,left2, r);
}

void heap(char **str, int strCount, int i)
{
    int maxV = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if (left < strCount && strcmp(str[left], str[maxV]) > 0) {
        maxV = left;
    }
    if (right < strCount && strcmp(str[right], str[maxV]) > 0) {
        maxV = right;
    }
    if (maxV != i) {
        string_swp(&str[i], &str[maxV]);
        heap(str, strCount, maxV);
    }
}
void heap_sort(char **str, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heap(str, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        string_swp(&str[i], &str[0]);
        heap(str, i, 0);
    }
}
int main(int argc,char* argv[]) {
    FILE *file=NULL;
    file=fopen(argv[2],"r");
    if(file == NULL) {
        message("open err");
        exit(0);}

    int strLength = 100;
    n=atoi(argv[1]);
    char **strings = (char **) malloc(n * sizeof(char *));
    char *inpStr = (char *) malloc(strLength * sizeof(char));
    if((NULL == strings)||(NULL == inpStr))
    {
        message("strings allocate err");
        exit(0);
    }
    for(int i = 0; i < n; i++)
    {
        if(NULL == fgets(inpStr, strLength, file))
        {
            message("read err");
            exit(0);
        }
        strings[i] =(char *) malloc((strlen(inpStr) + 1) * sizeof(char));
        if(NULL == strings[i])
        {
            message("array of strings allocate err");
            exit(0);
        }
        strcpy(strings[i], inpStr);
    }
    free(inpStr);
    fclose(file);
    char sort_type=argv[3][0];
    switch(sort_type){
        case 'b':
            bubble_sort(strings);
            break;
        case 'i':
            insertion_sort(strings);
            break;
        case 'm':
            merge_sort(strings, n);
            break;
        case 'q':

            quick_sort(strings,0,n-1);
            break;
        case 'h':
            heap_sort(strings, n);
            break;
        default:
            message("algorithm type err");
            break;
    }


    FILE *out_file;
    out_file=fopen("out.txt","w");
    for(int i=0;i<n;i++){
        fputs(strings[i],out_file);
    }
    fclose(out_file);
    return 0;
}