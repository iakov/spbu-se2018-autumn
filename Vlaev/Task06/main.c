#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

#define init_size 3
#define STRING_MAX_LEN 1000
uint64_t md5(uint8_t *initial_msg, size_t initial_len) {

    // Message (to prepare)
    uint8_t *msg = NULL;

    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating

    // r specifies the per-round shift amounts

    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    uint32_t h[4];

    h[0] = 0x67452301;
    h[1] = 0xefcdab89;
    h[2] = 0x98badcfe;
    h[3] = 0x10325476;

    // Pre-processing: adding a single 1 bit
    //append "1" bit to message
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */

    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message

    size_t new_len;
    for(new_len = initial_len*8 + 1; new_len%512!=448; new_len++);
    new_len /= 8;

    msg = calloc(new_len + 64, 1); // also appends "0" bits
                                   // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit

    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer

    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    size_t offset;
    for(offset=0; offset<new_len; offset += (512/8)) {

        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);

#ifdef DEBUG
        printf("offset: %d %x\n", offset, offset);

        int j;
        for(j =0; j < 64; j++) printf("%x ", ((uint8_t *) w)[j]);
        puts("");
#endif

        // Initialize hash value for this chunk:
        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];

        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {

#ifdef ROUNDS
            uint8_t *p;
            printf("%i: ", i);
            p=(uint8_t *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);

            p=(uint8_t *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);

            p=(uint8_t *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);

            p=(uint8_t *)&d;
            printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], d);
            puts("");
#endif


            uint32_t f, g;

             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

#ifdef ROUNDS
            printf("f=%x g=%d w[g]=%x\n", f, g, w[g]);
#endif
            uint32_t temp = d;
            d = c;
            c = b;
           // printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;



        }

        // Add this chunk's hash to result so far:

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;

    }
    uint64_t modulo = (1<<30)-1;
    uint64_t delta = 1<<30;
    uint64_t multiplier = delta;
    uint64_t result=0;
    for (int i=0;i<4;i++)
    {
        result=(result +(multiplier*h[i]) % modulo)%modulo;
        multiplier=(multiplier*delta) % modulo;
    }
    // cleanup
    free(msg);
    return result;

}

struct Node
{
    uint64_t hsh;
    char * key;
    int  value;
    struct Node * next;
};
struct HashTable
{
    struct Node ** data;
    int size;
};
struct HashTable* createHashTable(int size)
{
    struct HashTable * newTable=malloc(sizeof(struct HashTable));
    if (newTable==NULL)
    {
        printf("Memory error");
        exit(1);

    }
    newTable->data=malloc(size*sizeof(struct Node*));
    if (newTable->data==NULL)
    {
        free(newTable);
        printf("Memory error");
        exit(1);
    }
    for (int i=0;i<size;i++)
    {
        newTable->data[i]=NULL;
    }
    newTable->size=size;
    return newTable;
}
void clearChainNotStrings(struct Node* node)
{
    if (node==NULL)
    {
        return;
    }
    else
    {
        clearChainNotStrings(node->next);
        free(node);
    }
}
void clearTableButNotStrings(struct HashTable * table)
{

    for (int i=0;i<table->size;i++)
    {
        clearChainNotStrings(table->data[i]);
        table->data[i]=NULL;
    }
    free(table->data);
    free(table);
}
struct HashTable * insertInTable(struct HashTable * table, char * key, int value);
struct HashTable * resize(struct HashTable * table,int size)
{
    struct HashTable * newTable=createHashTable(size);
    for (int i=0;i<table->size;i++)
    {
        struct Node * current=table->data[i];
        while (current!=NULL)
        {
            newTable=insertInTable(newTable,current->key,current->value);
            current=current->next;
        }
    }
    clearTableButNotStrings(table);
    return newTable;
}
struct HashTable * insertInTable(struct HashTable * table, char * key, int value)
{

    uint64_t hsh=md5((uint8_t*)key,strlen(key));
    uint64_t pos=hsh%(table->size);
    if (table->data[pos]==NULL)
    {
        table->data[pos]=malloc(sizeof(struct Node));
        table->data[pos]->hsh=hsh;
        table->data[pos]->key=key;
        table->data[pos]->value=value;
        table->data[pos]->next=NULL;
    }
    else
    {
        int chain_len=0;
        char placed = 0;
        struct Node* currentNode=table->data[pos];
        struct Node* lastNode=table->data[pos];
        while (placed ==0)
        {
            if (currentNode==NULL)
            {
                currentNode=malloc(sizeof(struct Node));
                currentNode->hsh=hsh;
                currentNode->key=key;
                currentNode->value=value;
                currentNode->next=NULL;
                lastNode->next=currentNode;
                placed=1;
            }
            else if (strcmp(key,currentNode->key)==0)
            {
                (currentNode->value)++;
                free(key);
                placed=1;
            }
            lastNode=currentNode;
            currentNode=currentNode->next;
            chain_len++;
        }
        if (chain_len>=table->size-1)
        {
            return resize(table,table->size*2);
        }
    }
    return table;

}
int getValue(struct HashTable * table, char * key)
{
    uint64_t hsh=md5((uint8_t*) key,strlen(key));
    uint64_t pos=hsh%(table->size);
    bool found =false;
    struct Node* currentNode=table->data[pos];
    int result=-1;
    while (found==false)
    {
        if (currentNode==NULL)
        {
            printf("Not found!");
            found=true;
            result=-1;
        }
        else
        {
            if (strcmp(key, currentNode->key) == 0)
            {
                found = true;
                result = currentNode->value;
            }
            currentNode = currentNode->next;
        }
    }
    return result;
}
void clearTable (struct HashTable * table);
char * delete_punctuation(struct HashTable *table, char * st)
{
    int sign_counter=0;
    for (unsigned long i=0;i<strlen(st);i++)
    {
        if (!(isalpha(st[i])))
        {
            sign_counter++;
        }
    }
    int cur_pos=0;
    for (unsigned int i=0;i<strlen(st);i++)
    {
        if (isalpha(st[i]))
        {
            st[cur_pos]=st[i];
            cur_pos++;
        }
    }
    size_t len=max((strlen(st)-sign_counter),0)*sizeof(char);
    st=realloc(st,len+1);
    if (st==NULL)
    {
        clearTable(table);
        printf("Memory error");
        exit(5);
    }
    st[len]='\0';
    return st;
}
void clearChain(struct Node* node)
{
    if (node==NULL)
    {
        return;
    }
    else
    {
        clearChain(node->next);
        free(node->key);
        free(node);
    }
}
void clearTable(struct HashTable * table)
{

    for (int i=0;i<table->size;i++)
    {
        clearChain(table->data[i]);
        table->data[i]=NULL;
    }
    free(table->data);
    free(table);
}
void iterate_inc(struct HashTable * table)
{
    for (int i=0;i<table->size;i++)
    {
        struct Node * current=table->data[i];
        while (current!=NULL)
        {
            current->value++;
            current=current->next;
        }
    }
}
void printTable(struct HashTable * table)
{
    for (int i=0;i<table->size;i++)
    {
        if (table->data[i] != NULL)
        {
            struct Node * current = table->data[i];
            while (current!=NULL)
            {
                printf("%s %d\n",current->key, getValue(table,current->key));
                current=current->next;
            }
        }
    }
}
char * readword(struct HashTable * table)
{
    char gotChar =(char) fgetc(stdin);
    char *word = malloc(STRING_MAX_LEN * sizeof(char));
    if (word==NULL)
    {
        clearTable(table);
        printf("memory error");
        exit(4);
    }
    int size = 0;
    while ((gotChar != EOF) && (isalpha(gotChar)==0)) // skip everything until the first word
    {
        gotChar =(char) fgetc(stdin);
    }
    while ((gotChar !=EOF) && (isalpha(gotChar)!=0))
    {
        word[size] = gotChar;
        size++;
        gotChar = (char) fgetc(stdin);
    }
    word[size] = '\0';
    if (size == 0)
    {
        free(word);
        return NULL;
    }
    return word;
}
int find_max(struct HashTable * table)
{
    int cur_max=0;
    for (int i=0;i<table->size;i++)
    {
        if (table->data[i] != NULL)
        {
            struct Node * current = table->data[i];
            while (current!=NULL)
            {
               // printf("%s %d\n",current->key, getValue(table,current->key));
                cur_max=max(cur_max,current->value);
                current=current->next;
            }
        }
    }
    return cur_max;
}
void display_elems_with_value(struct HashTable * table, int value)
{
    for (int i=0;i<table->size;i++)
    {
        if (table->data[i] != NULL)
        {
            struct Node * current = table->data[i];
            while (current!=NULL)
            {
                if (current->value==value)
                {
                    fprintf(stderr,"%s %d\n",current->key, current->value);
                }
                current=current->next;
            }
        }
    }
}
int average_chain_length(struct HashTable * table)
{
    int sum=0;
    for (int i=0;i<table->size;i++)
    {
        if (table->data[i] != NULL)
        {
            struct Node * current = table->data[i];
            int counter=0;
            while (current!=NULL)
            {
                counter++;
                current=current->next;
            }
            sum+=counter;
        }
    }
    return sum/table->size;
}
int main(/*int argc, char **argv*/)
{

   /* if (argc < 2)
    {
        printf("Error: incorrect number of parameters\n", argv[0]);
        exit(1);
    }
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Error! file not found");
        exit(1);
    }*/
    struct HashTable *table = createHashTable(init_size);
    char * word=readword(table);
    while (word!=NULL)
    {

        word=delete_punctuation(table,word);
        if (word!=NULL)
        {
            int value = 1;
            table = insertInTable(table, word, value);
        }
        word=readword(table);
    }
    printTable(table);
   // printf("%d\n",table->size);
    display_elems_with_value(table,find_max(table));
   // printf("%d",average_chain_length(table));
    clearTable(table);
    return 0;
}
