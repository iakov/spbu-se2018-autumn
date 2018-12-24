void PrintError(char * string, int ExitCode);

struct HashTableSlot
{
    char *key;
    uint32_t *hash;
    uint32_t value;
};

struct HashTable
{
    struct HashTableSlot *data;
    uint32_t size;
    uint32_t numberOfElements;
};

struct HashTable CreateHashTable(uint32_t size)
{
    struct HashTable hashTable;
    hashTable.data = (struct HashTableSlot *)calloc(size, sizeof(struct HashTableSlot));
    if(hashTable.data == NULL)
    {
        PrintError("I can not allocate memory in Main for \"hashTable.data\"", 4);
    }

    hashTable.size = size;
    hashTable.numberOfElements = 0;
    return hashTable;
}

void Add(struct HashTable *hashTable, char *key, uint32_t value);
void Resize(struct HashTable *hashTable, uint32_t size);
uint32_t Get(struct HashTable *hashTable, char *key);
uint32_t GetIndex(struct HashTable *hashTable, char *key);
void Clear(struct HashTable *hashTable);
