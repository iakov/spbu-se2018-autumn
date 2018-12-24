const char * allowedOptions[] = {"bubble", "insertion", "merge", "quick", "radix"};
const unsigned int allowedOptionsLength = sizeof allowedOptions / sizeof allowedOptions[0];
void CheckOption(char * options[], unsigned int *Numberoflines);

void Sort_Bubble(char * sortlines[], unsigned int Countofline);
void Sort_Insertion(char * sortlines[], unsigned int Countofline);

//void Sort_Merge(char * sortlines[], unsigned int Countofline);
void Sort_Merge(char** Strings, int Left, int Right);

//void Sort_Quick(char * sortlines[], unsigned int first, unsigned int last);
int Partition(char** Strings, int Left, int Right);
void Sort_Quick(char** Strings, int Left, int Right);

void Sort_Radix(char * sortlines[], unsigned int from, unsigned int to, unsigned int byte, unsigned int maxlength);

void SwapString(char * string1[], char * string2[]);
