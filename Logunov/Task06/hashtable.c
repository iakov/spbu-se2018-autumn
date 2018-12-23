#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "md5.h"

#define MD5_BLOCK_SIZE 16
#define MAX_WORD_SIZE 100

void ForcedExit(char *message, int errcode) {
    printf("%s\n", message);
    exit(errcode);
}

#define CHECK_NULL(value) if(value == NULL) ForcedExit("no memory", 4)

int getHashIndex(char *key, int size) {
    uint8_t *md5hash = malloc(MD5_BLOCK_SIZE * sizeof(uint8_t));
    CHECK_NULL(md5hash);
    md5((uint8_t*)key, strlen(key), md5hash);
    int index = 0;
    for (int i = 0; i < MD5_BLOCK_SIZE; i++) {
        index = (index * 16 + (int)md5hash[i]) % size;
    }
    free(md5hash);
    return index;
}

struct HashTableElement {
    char *key;
    int value;
};

struct HashTable {
    struct HashTableElement *table;
    int size, capacity;
    int iter; // for iterative function
}; 

struct HashTable newHashTable(int capacity) {
    struct HashTable new;
    new.table = calloc(capacity, sizeof(struct HashTableElement));
    CHECK_NULL(new.table);
    new.capacity = capacity;
    new.size = 0;
    return new;
}  

void delHashTable(struct HashTable *hashTable) {
    for (int i = 0; i < hashTable->capacity; i++) {
        if (hashTable->table[i].key != NULL)
            free(hashTable->table[i].key);
    }
    free(hashTable->table);
} 

void resize(struct HashTable*, int);                               

void add(struct HashTable *hashTable, char *key, int num) {
    int pos = getHashIndex(key, hashTable->capacity);
    while (hashTable->table[pos].key != NULL && strcmp(key, hashTable->table[pos].key) != 0) {
        // searching for free pos in table
        pos++;
        pos %= hashTable->capacity; // in case we made it too far
    }
    if (hashTable->table[pos].key == NULL) {
        hashTable->table[pos].key = key;
        hashTable->table[pos].value = num;
        hashTable->size++;
    }
    else { // if (strcmp(key, hashTable->table[pos].key) == 0) {
        hashTable->table[pos].value += num;
        free(key);
        /* we will never use this string after exiting this function
         * so we should free it's memory
         */ 
    }
    if (hashTable->size > hashTable->capacity / 2)   // more than 50% of HashTable is full, let's double it
        resize(hashTable, hashTable->capacity * 2);
}

void resize(struct HashTable *hashTable, int newCapacity) {
    struct HashTableElement *oldTable = calloc(hashTable->size, sizeof(struct HashTableElement)); 
    CHECK_NULL(oldTable);  
    int oldTableIndex = 0;
    for (int i = 0; i < hashTable->capacity; i++) {
        if (hashTable->table[i].key != NULL) {
            oldTable[oldTableIndex].key = hashTable->table[i].key;
            oldTable[oldTableIndex].value = hashTable->table[i].value;
            oldTableIndex++;
        }
    }
    free(hashTable->table);
    hashTable->table = calloc(newCapacity, sizeof(struct HashTableElement));
    CHECK_NULL(hashTable->table);
    hashTable->capacity = newCapacity;
    hashTable->size = 0;
    for (int i = 0; i < oldTableIndex; i++) {  
        add(hashTable, oldTable[i].key, oldTable[i].value);
    }
    free(oldTable);
}

struct HashTableElement *nextHashTableElement(struct HashTable *hashTable) {
    while (hashTable->iter < hashTable->capacity && hashTable->table[hashTable->iter].key == NULL) {
        hashTable->iter++;
    } 
    if (hashTable->iter >= hashTable->capacity) { // found end of HashTable
        hashTable->iter = 0;
        return NULL;
    }
    return &hashTable->table[hashTable->iter++]; // increasing iter after returning current one
}

void printCurrentState(struct HashTable *hashTable) {
    for (int i = 0; i < hashTable->capacity; i++) {
        if (hashTable->table[i].key != NULL) {
            printf("%s: %d\n", hashTable->table[i].key, hashTable->table[i].value);
        }
    }
    printf("\n");
}

bool isLetter(char c, bool extra) { // "extra" is for special symbols which can be in middle of a word
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (extra && (c == '-' || c == '\''));
}

char *nextWord() {
    char nextChar = fgetc(stdin);
    char *word = malloc(MAX_WORD_SIZE * sizeof(char));
    CHECK_NULL(word);
    int wordSize = 0;
    while (nextChar != EOF && !isLetter(nextChar, false)) {
        nextChar = fgetc(stdin);
        // searching fot the first letter of the word in the file
    }
    while (nextChar != EOF && isLetter(nextChar, true)) {
        /*if (nextChar >= 'A' && nextChar <= 'Z') {
            nextChar = nextChar - 'A' + 'a'; // lowering upper-case char
        } */
        word[wordSize] = nextChar;
        wordSize++;
        nextChar = fgetc(stdin);
    }
    word[wordSize] = '\0';
    if (wordSize == 0) { // found end of file
        free(word);
        return NULL;
    }
    return word;
}

int main() {
    struct HashTable hashTable = newHashTable(32);
    char *word = nextWord();
    while (word != NULL) {
        add(&hashTable, word, 1);
        word = nextWord();
    }
    int maxCount = -1;
    struct HashTableElement *currentElement = nextHashTableElement(&hashTable);
    while (currentElement != NULL) {
        if (currentElement->value > maxCount) {
            maxCount = currentElement->value;
        }
        fprintf(stdout, "%s %d\n", currentElement->key, currentElement->value);
        currentElement = nextHashTableElement(&hashTable);
    }
    //fprintf(stdout, "\n");
    currentElement = nextHashTableElement(&hashTable);
    while (currentElement != NULL) {
        if (currentElement->value == maxCount) {
            fprintf(stderr, "%s %d\n", currentElement->key, currentElement->value);
        }
        currentElement = nextHashTableElement(&hashTable);
    }
    //fprintf(stderr, "\n");
    delHashTable(&hashTable);
}
