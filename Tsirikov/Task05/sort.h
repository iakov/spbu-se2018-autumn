int bubble(char **strings)
{
  long i, j;
  char *buf;
  for (i = 0; i < number_of_strings - 1; i++)
  {
    for (j = 1; j < number_of_strings - i; j++)
    {
      if (strcmp(strings[j - 1], strings[j]) >= 0)
      {
        buf = strings[j-1];
        strings[j-1] = strings[j];
        strings[j] = buf;
      }
    }
  }
  return 0;
}


int insertion(char **strings)
{
  long i, j;
  for (i = 1; i < number_of_strings; i++)
  {
    strings[number_of_strings] = strings[i];
    for (j = i - 1; (j >= 0) && (strcmp(strings[j], strings[number_of_strings]) >= 0); j--)
    {
      strings[j+1] = strings[j];
    }
    strings[j + 1] = strings[number_of_strings];
  }
  return 0;
}


int merge_union(char **strings, long left, long middle, long right)
{
  long left_length = middle - left + 1;
  long right_length = right - middle;
  char **buf_array = calloc(left_length + right_length, sizeof(char *));
  NULL_CHECK( buf_array );
  for (long buf = 0; buf < right_length; buf++)
  {
    buf_array[buf] = strings[left + buf];
    buf_array[left_length + buf] = strings[middle + 1 + buf];
  }
  if (left_length > right_length)
  {
    buf_array[left_length - 1] = strings[middle];
  }
  long i = 0, j = 0;
  for ( ; left <= right ; left++ )
  {
    if
    (
      (j >= right_length)   ||
      ((i < left_length)   &&
      (j < right_length)   &&
      (strcmp(buf_array[left_length + j], buf_array[i]) >= 0))
    )
    {
      strings[left] = buf_array[i++];
    }
    else
    {
      strings[left] = buf_array[left_length + j++];
    }
  }
  free(buf_array);
  return 0;
}


int merge(char **strings, long left, long right)
{
  if (left < right)
  {
    long middle = (left + right) / 2;
    merge(strings, left, middle);
    merge(strings, middle + 1, right);
    merge_union(strings, left, middle, right);
  }
  return 0;
}


int quick_partition(char **strings, long left, long right)
{
  char *buf;
  long support = left;
  for ( ; left < right ; left++ )
  {
    if ( strcmp(strings[right], strings[left]) >= 0 )
    {
      buf = strings[support];
      strings[support++] = strings[left];
      strings[left] = buf;
    }
  }
  buf = strings[support];
  strings[support] = strings[right];
  strings[right] = buf;
  return support;
}


int quick(char **strings, long left, long right)
{
  if ( left < right )
  {
    long support = quick_partition(strings, left, right);
    quick(strings, left, support - 1);
    quick(strings, support + 1, right);
  }
  return 0;
}


int radix_in_buckets(char **strings, char **copy, long left, long right, long depth)
{
  long *symbols = calloc( ALPHABET + 1, sizeof(long) );
  NULL_CHECK( symbols );
  long buf, different_symbols = 0;

  /* Counting number of different symbols in column 'depth'
   * from string with number 'left' to number 'right'.
   * It`s safe, because these strings have at least
   * one symbol ('\0') from this column to string`s end
   * by virtue of recursive condition below. */

  for (buf = left; buf <= right; buf++)
  {
    symbols[(int)( strings[buf][depth] )]++;
    if (symbols[(int)( strings[buf][depth] )] == 1)
    {
      different_symbols++;
    }
  }
  long diff = different_symbols;
  int *real_symbols = calloc( diff + 1, sizeof(int) );
  NULL_CHECK( real_symbols );
  long *order_symbols = calloc( ALPHABET + 1, sizeof(long) );
  NULL_CHECK( order_symbols );
  for ( buf = ALPHABET - 1; different_symbols != 0; buf--)
  {
    if (symbols[buf] != 0)
    {
      real_symbols[--different_symbols] = (int) buf;
    }
  }
  order_symbols[real_symbols[0]] = left;
  for ( buf = 1; buf < diff; buf++ )
  {
    order_symbols[real_symbols[buf]]  = order_symbols[real_symbols[buf - 1]];
    order_symbols[real_symbols[buf]] += symbols[real_symbols[buf - 1]];
  }
  for ( buf = left ; buf <= right; buf++ )
  {
    copy[order_symbols[(int)( strings[buf][depth] )]++] = strings[buf];
  }
  for ( buf = left ; buf <= right; buf++ )
  {
    strings[buf] = copy[buf];
  }

  /* Recursive condition puts 'left' and 'right' indexes
   * of strings, in which symbol '\0' haven`t met yet.*/

  long new_left, new_right;
  for ( buf = 0; buf < diff; buf++ )
  {
    if
    (
      symbols[real_symbols[buf]] > 1     &&
      (char)( real_symbols[buf] ) != '\0'  &&
      (char)( real_symbols[buf] ) != '\n'
    )
    {
      new_left  = buf > 0 ? order_symbols[real_symbols[buf - 1]] : left;
      new_right = order_symbols[real_symbols[buf]] - 1;
      radix_in_buckets( strings, copy, new_left, new_right, depth + 1 );
    }
  }
  free( real_symbols );
  free( symbols );
  free( order_symbols );
  return 0;
}


int radix( char **strings )
{
  char **copy = calloc( number_of_strings + 1, sizeof( char * ) );
  NULL_CHECK( copy );
  radix_in_buckets( strings, copy, 0, number_of_strings - 1, 0 );
  free( copy );
  return 0;
}
