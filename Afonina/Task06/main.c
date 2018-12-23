#include "md5.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void return_value_check(void *ptr, const char *name) {
    if ((char*)ptr == NULL) {
        printf("Not enough memory for %s!\n", name);
        exit(4);
    }
}

typedef struct table_item {
    char *key;
    int value;
} table_item_t;

typedef struct hashtable {
    int size;
    int capacity;
    table_item_t *data;
} hashtable_t;

hashtable_t init_table (int init_capacity) {
    hashtable_t table;
    table.data = (table_item_t*)calloc(init_capacity, sizeof(table_item_t));
    return_value_check(table.data, "table_data");
    table.capacity = init_capacity;
    table.size = 0;
    return table;
}

int find_position(table_item_t *data, int capacity, char *key) {
    uint8_t *hash = (uint8_t*)malloc(16 * sizeof(uint8_t));
    return_value_check(hash, "hash");
    int position = 0;
    md5((uint8_t*)key, strlen(key), hash);
    for (int i = 0; i < 16; ++i) {
        position += (int)hash[i] % capacity;
    }
    position %= capacity;
    free(hash);
    while (data[position].key != NULL && strcmp(key, data[position].key)) {
        ++position;
        position %= capacity;
    }
    return position;
}

void resize(hashtable_t *table) {
    int resized_capacity = 2 * table->capacity;
    table_item_t *resized_data = (table_item_t*)calloc(resized_capacity, sizeof(table_item_t));
    return_value_check(resized_data, "resized_data");
    for (int i = 0; i < table->capacity; ++i) {
        if (table->data[i].key != NULL) {
            int position = find_position(resized_data, resized_capacity, table->data[i].key);
            resized_data[position] = table->data[i];
        }
    }
    free(table->data);
    table->data = resized_data;
    table->capacity = resized_capacity;
}

void add(hashtable_t *table, char *key) {
    int position = find_position(table->data, table->capacity, key);
    if (table->data[position].key == NULL || strcmp(table->data[position].key, key)) {
        table->size++;
        if (table->size > table->capacity / 2) {
           resize(table);
        }
        position = find_position(table->data, table->capacity, key);
        table->data[position].key = key;
        table->data[position].value = 1;
    } else {
        ++table->data[position].value;
        free(key);
    }
}

void free_table(hashtable_t *table) {
    for(int i = 0; i < table->capacity; ++i) {
        if (table->data[i].key != NULL) {
            free(table->data[i].key);
        }
    }
    free(table->data);
    table->size = 0;
    table->capacity = 0;
}

int main() {
    hashtable_t table = init_table(128);
    const int MAX_WORD_LEN = 5000;
    int word_len = 0, words_cnt = 0;
    char ch = getchar();
    char buf[MAX_WORD_LEN];
    while (ch != EOF) {
        if ((ch >= 'a' && ch <='z') || (ch >= 'A' && ch <= 'Z')) {
            buf[word_len++] = ch;
        } else if (word_len > 0) {
            buf[word_len] = '\0';
            char *word = (char*)calloc(word_len + 1, sizeof(char));
            return_value_check(word, "next word");
            strncpy(word, buf, word_len);
            add(&table, word);
            word_len = 0;
        }
        ch = getchar();
    }
    int max_cnt = 0;
    for (int i = 0; i < table.capacity; ++i) {
        if (table.data[i].key != NULL) {
            printf("%s %d\n", table.data[i].key, table.data[i].value);
            ++words_cnt;
            if (table.data[i].value > max_cnt) {
                max_cnt = table.data[i].value;
            }
        }
    }
    for (int i = 0; i < table.capacity; ++i) {
        if (table.data[i].key != NULL && table.data[i].value == max_cnt) {
            fprintf(stderr, "%s %d\n", table.data[i].key, table.data[i].value);
        }
    }
    free_table(&table);
    return 0;
}
