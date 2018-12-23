#include "header.h"


int main(int argc, char *argv[])
{
  char sortname;
  if ( argc == 4 )
  {
    sortname = input(argv);
  }
  else
  {
    printf("You should give to program 3 parameters.\n");
    printf("(Number of strings, name of file, name of sorting algorythm.)\n");
    exit(1);
  }

  char **strings = calloc(number_of_strings + 1, sizeof(char *));
  NULL_CHECK( strings );

  read_file(InputFile, strings);
  choise_sort(sortname, strings);
  print_sorted(strings);
  memory_flush(strings);
  return 0;
}
