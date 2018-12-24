const char * allowedOptions[] = {"bubble", "insertion", "merge", "quick", "radix"};
const unsigned int allowedOptionsLength = sizeof allowedOptions / sizeof allowedOptions[0];
void CheckOption(char * options[], unsigned int *Numberoflines);
void PrintError(char * string, int ExitCode);

void Sort_Bubble(char * sortlines[], unsigned int Countofline);
void Sort_Insertion(char * sortlines[], unsigned int Countofline);
void Sort_Merge(char * sortlines[], unsigned int Countofline);
//void Sort_Quick(char * sortlines[], unsigned int first, unsigned int last);
void Sort_Radix(char * sortlines[], unsigned int from, unsigned int to, unsigned int byte, unsigned int maxlength);

void SwapString(char * string1[], char * string2[]);