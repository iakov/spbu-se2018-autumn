typedef struct table_item
{
    char *key;
    int value;
} table_item_var;

typedef struct hash_table
{
    int size;
    int capacity;
    table_item_var *data;
} hash_table_var;

hash_table_var InitTable(int init_capacity);
void Resize(hash_table_var *table);
void Add(hash_table_var *table, char *key);
void FreeTable(hash_table_var *table);
//int FindPosition(table_item_var *data, int capacity, char *key);
int find_position(table_item_var *data, int capacity, char *key);

void PrintError(char * string, int ExitCode);