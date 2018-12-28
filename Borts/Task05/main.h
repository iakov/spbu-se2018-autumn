const char * allowed_options[] = {"bubble", "insertion", "merge", "quick", "radix"};
const unsigned int allowed_options_length = sizeof allowed_options / sizeof allowed_options[0];
void CheckOption(char * options[], unsigned int *number_of_lines);
void PrintError(char * string, int exit_code);

void Sort_Bubble(char * sort_strings[], unsigned int count_of_line);
void Sort_Insertion(char * sort_strings[], unsigned int count_of_line);
void Sort_Merge(char * sort_strings[], unsigned int count_of_line);
void Sort_Quick(char * sort_strings[], int first, int last);
void Sort_Radix(char * sort_strings[], unsigned int from, unsigned int to, unsigned int byte, unsigned int maxlength);

void SwapString(char * string1[], char * string2[]);
