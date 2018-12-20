char input(char *argv[])
{
  short buf = 0;
  while (argv[1][buf] != '\0')
  {
    number_of_strings = 10 * number_of_strings + (long) (argv[1][buf++] - '0');
  }
  if ( NULL == (InputFile = fopen((argv[2]), "r")) )
  {
    printf("Can`t open \"%s\" file.\n", argv[2]);
    exit(2);
  }
  switch ((char) (argv[3][0]))
  {
    case 'b':
  if( 0 == strcmp( (const char *)( argv[3] ), "bubble" ) )
      {
        return 'b';
      }
  break;
    case 'i':
  if( 0 == strcmp( (const char *)( argv[3] ), "insertion" ) )
      {
        return 'i';
      }
  break;
  case 'm':
    if( 0 == strcmp( (const char *)( argv[3] ), "merge" ) )
        {
          return 'm';
        }
    break;
    case 'q':
  if( 0 == strcmp( (const char *)( argv[3] ), "quick" ) )
      {
        return 'q';
      }
  break;
    case 'r':
  if( 0 == strcmp( (const char *)( argv[3] ), "radix" ) )

      {
        return 'r';
      }
  break;

    default:
      printf( "Wrong name of sorting algorythm.\n" );
      exit( 1 );
      break;
  }
  printf( "Wrong name of sorting algorythm.\n" );
  exit( 1 );
}


int read_file(FILE *InputFile, char *strings[])
{
  short length;
  int *buf = calloc(MAX_STR_LENGTH, sizeof(int));
  NULL_CHECK( buf );
  for (long line_number = 0; line_number < number_of_strings; line_number++)
  {
    for (length = 0; (buf[length] = getc(InputFile)) != 10 && buf[length] != -1; length++);
    strings[line_number] = calloc(length + 1, sizeof(char));
    NULL_CHECK( strings[line_number] );
    if( ( -1 == buf[length] ) && ( line_number < number_of_strings ) )
    {
      printf("File is smaller then given length.\n");
      exit( 2 );
    }
    strings[line_number][length--] = '\0';
    for (; length >= 0; length--)
    {
      strings[line_number][length] = (char) buf[length];
    }
  }
  free(buf);
  if( 0 != fclose(InputFile) )
  {
    printf("Can`t close the file.\n");
    exit(4);
  }
  return 0;
}


int choise_sort(char sortname, char **strings)
{
  switch (sortname)
  {
    case 'b':
      bubble(strings);
      break;
    case 'i':
      insertion(strings);
      break;
    case 'm':
      merge(strings, 0, number_of_strings - 1);
      break;
    case 'q':
      quick(strings, 0, number_of_strings - 1);
      break;
    case 'r':
      radix(strings);
      break;
    default:
      printf("Name of sorting algorithm is wrong.\n");
      exit(1);
      break;
  }
  return 0;
}


int print_sorted(char **strings)
{
  for (long line_number = 0; line_number < number_of_strings; line_number++)
  {
    printf("%s\n", strings[line_number]);
  }
  return 0;
}


int memory_flush(char *strings[])
{
  for (long line_number = 0; line_number < number_of_strings; line_number++)
  {
    free(strings[line_number]);
  }
  free(strings);
  return 0;
}
