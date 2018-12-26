#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "sha256.h"

/* CONSTANTS */

#define MAX_WORD_SIZE 128
#define HASH_TABLE_SIZE 2048
#define SHA256_HASH_SIZE 32

enum algorithm {
	SHA256
};

typedef enum algorithm algorithm;


/* STRUCTURES */

/* Hash table chain element */
struct chainElement {
	char *word;
	unsigned count;
	struct chainElement *next;
};

typedef struct chainElement chainElement;

/* Hash table */
struct hashTable {
	chainElement **table;
	unsigned size;
	algorithm algo;
};

typedef struct hashTable hashTable;


/* FUNCTIONS */

/* Allocates memory with malloc(). Handles exceptions */
void *mallocate(size_t bytes) {
	void *pointer = malloc(bytes);
	if(pointer == 0) {
		printf("Failed to allocate memory\n");
		exit(4);
	}
	return pointer;
}

/* Allocates memory with calloc(). Handles exceptions */
void *callocate(unsigned count, size_t size) {
	void *pointer = calloc(count, size);
	if(pointer == 0) {
		printf("Failed to allocate memory\n");
		exit(4);
	}
	return pointer;
}

/* Calculates hash and returns first 4 bytes */
uint32_t hash(char *word, algorithm algo) {
	
	if(algo == SHA256) {
		static uint8_t output[SHA256_HASH_SIZE];
		
		sha256(word, strlen(word), output);
		
		uint32_t result = output[0];
		result <<= 8;
		result |= output[1];
		result <<= 8;
		result |= output[2];
		result <<= 8;
		result |= output[3];
		
		return result;
	}
	
	exit(5);
}

/* Creates hash table and returns pointer to it */
hashTable *ht_create(unsigned size, algorithm algo) {
	
	hashTable *ht = mallocate(sizeof(hashTable));
	chainElement **table = callocate(size, sizeof(chainElement *));
	
	if(table == 0) {
		printf("Error: failed to allocate memory for hash table pointers\n");
		exit(4);
	}
	
	ht -> table = table;
	ht -> size = size;
	ht -> algo = algo;
	
	return ht;
}

/* Puts word into hash table */
void ht_insert(hashTable *ht, char *word) {
	
	uint32_t key;
	
	switch(ht -> algo) {
		case SHA256: key = hash(word, SHA256); break;
		default: exit(5);
	}
	
	key %= ht -> size;
		
	chainElement *element = (ht -> table)[key];
	
	if(element != 0) {
		
		if(strcmp(element -> word, word) == 0) {
			++(element -> count);
			return;
		}
		
		while(element -> next != 0) {
			element = element -> next;
			if(strcmp(element -> word, word) == 0) {
				++(element -> count);
				return;
			}
		}
	}
	
	unsigned word_full_length = (strlen(word) + 1);
	
	char *word_copy = mallocate(word_full_length * sizeof(char));
	memcpy(word_copy, word, word_full_length * sizeof(char));
	
	chainElement *new_element = mallocate(sizeof(chainElement));
	new_element -> word = word_copy;
	new_element -> count = 1;
	new_element -> next = 0;
	
	if(element == 0) {
		(ht -> table)[key] = new_element;
	} else {
		element -> next = new_element;
	}
}

/* Iterates hash table with specified function */
void ht_iterate(hashTable *ht, void function(uint32_t key, chainElement *element)) {
	
	chainElement **table = ht -> table;
	
	unsigned size = ht -> size;
	
	for(unsigned i = 0; i < size; ++i) {
		
		chainElement *element = table[i];
		if(element != 0) {
			while(element -> next != 0) {
				function(i, element);
				element = element -> next;
			}
			function(i, element);
		}
	}
}

/* Cleans hash table */
void ht_clean(hashTable *ht) {
	
	chainElement **table = ht -> table;
	
	unsigned size = ht -> size;
	
	for(unsigned i = 0; i < size; ++i) {
		
		chainElement *element = table[i];
		if(element != 0) {
			while(element -> next != 0) {
				chainElement *next_element = element -> next;
				free(element -> word);
				free(element);
				element = next_element;
			}
			free(element -> word);
			free(element);
		}
	}
}

/* Removes hash table */
void ht_remove(hashTable *ht) {
	
	ht_clean(ht);
	free(ht -> table);
	free(ht);
}

/* Collects stats */

unsigned *chains_count;
char *most_common_word;
unsigned max_word_count;

void stats(uint32_t key, chainElement *element) {
	
	++chains_count[key];
	
	if(element -> count > max_word_count) {
		max_word_count = element -> count;
		most_common_word = element -> word;
	}
}

/* Prints word from chain element and number of repetitions */
void print_word_stats(__attribute__((unused)) uint32_t key, chainElement *element) {
	printf("%s %u\n", element -> word, element -> count);
}


int main(int argc, char **argv) {
	
	hashTable *ht = ht_create(HASH_TABLE_SIZE, SHA256);
	
	char *buffer = mallocate(MAX_WORD_SIZE * sizeof(char));
	char *pointer = buffer;
	
	char current_symbol = getchar();
	
	while(!feof(stdin)) {
		
		if(current_symbol >= 'a' && current_symbol <= 'z') {
			
			*pointer = current_symbol;
			++pointer;
			
		} else if(current_symbol >= 'A' && current_symbol <= 'Z') {
			
			*pointer = current_symbol + ('a' - 'A');
			++pointer;
			
		} else {
			
			if(pointer - buffer != 0) {
				*pointer = '\0';
				
				ht_insert(ht, buffer);
				
				pointer = buffer;
			}
		}
		
		current_symbol = getchar();
	}
	
	if(pointer - buffer != 0) {
		*pointer = '\0';
		ht_insert(ht, buffer);
	}
	
	free(buffer);
	
	if(argc == 2 && strcmp(argv[1], "stats") == 0) {
		
		/* Printing stats */
		
		chains_count = callocate(HASH_TABLE_SIZE, sizeof(unsigned));
		max_word_count = 0;
		ht_iterate(ht, stats);
		
		unsigned chain_elements_amount = 0;
		unsigned max_chain_length = 0;
		
		for(unsigned i = 0; i < HASH_TABLE_SIZE; ++i) {
			chain_elements_amount += chains_count[i];
			
			if(chains_count[i] > max_chain_length) {
				max_chain_length = chains_count[i];
			}
		}
		
		printf("There are %u different words in text.\n\n", chain_elements_amount);
		printf("The most common word is \"%s\", it occurs %u times.\n\n", most_common_word, max_word_count);
		printf("Middle chain length - %.3lf.\n\n", (double)chain_elements_amount / (double)HASH_TABLE_SIZE);
		printf("The longest chain consists of %u elements.\n\n", max_chain_length);
		
		free(chains_count);
		
	} else {
		
		/* Printing words and number of repetitions */
		
		ht_iterate(ht, print_word_stats);
		
	}
	
	ht_remove(ht);
	
	return 0;
}
