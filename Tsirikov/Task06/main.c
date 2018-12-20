#include "hash.h"
#include "table.h"
#include "book.h"

#define MAXSTR 32


void manage_table();
long long int get_key( unsigned char * );


int main(int argc, char *argv[])
{
	size = 100;
	set_hash_name('m');
	Table = make_table();
	if( 1 < argc )
	{
		analyse_book( ( argv[1] ) );
	}
	else
	{
		printf("Book name wasn`t given.\n");
		exit(1);
	}
	iterate();
	unsigned char *popular_word = NULL;
	unsigned char **pt_word = &popular_word;
	long long int popular_number = 0;
	statistics( pt_word, &popular_number );
	fprintf( stderr, "%s %lld\n", popular_word, popular_number );
	clear_table();
	return 0;
}

/* Procedure 'manage_table' is an interface
 * for manual inputting data to hash-table.*/

void manage_table()
{
  unsigned char str_buf[MAXSTR];
  long long int num_buf;
  int err_log = 0;
  unsigned char *wordbuf = NULL;
  unsigned char **ptbuf = &wordbuf;
  long long int digitbuf = 0;
	

  err_log = scanf( "%s", str_buf );
  if( 0 >= err_log )
  {
    exit(4);
  }

  /*Exit from program.*/

  while( 'e' != str_buf[0] )
  {
    switch( str_buf[0] )
    {

      /*Make table with given 'size' and 'hash'.*/

      case 'm':
        err_log = scanf( "%lld %s", &size, str_buf );
        if( 0 >= err_log )
        {
          exit(4);
        }
        set_hash_name( *str_buf );
        Table = make_table();
        break;

      /*Clear table and statistics.*/

      case 'c':
        clear_table();
        size = 0;
        diff = 0;
        load = 0;
        break;

      /*Insert 'key' in hash_table.*/

      case 'i':
        num_buf = get_key( str_buf );
        insert_key( str_buf, num_buf );
        break;

      /*Get information about 'key' in the table.*/

      case 'g':
        num_buf = get_key( str_buf );
        find_key( str_buf, num_buf );
        break;

      /*Print all key-value pairs.*/

      case 'p':
        iterate();
        break;

      /*Statistic information`s output.*/

      case 's':
	statistics( ptbuf, &digitbuf );
        break;

      /*'File' read until its end with mmap.*/

      case 'f':
        err_log = scanf( "%s", str_buf );
        if( 0 >= err_log )
        {
          exit(4);
        }
        analyse_book( (char *)( str_buf ) );
        break;

      /*Help-brief for manage the table.*/

      case 'h':
        printf( "Use one of these keywords:\n" );
        printf( "make (size) (hash)\n" );
        printf( "clear\ninsert (key)\n" );
        printf( "get (key)\npairs\n" );
        printf( "file (filename)\n" );
        printf( "statistics\nexit\n" );
        break;

      /*Incorrect input exception.*/

      default:
        printf( "Use 'help' for more information.\n" );
        break;
    }
    err_log = scanf( "%s", str_buf );
    if( 0 >= err_log )
    {
      exit(4);
    }
  }

  /*Clear table at the exit if the user didn`t.*/

  if( 0 != size )
  {
    clear_table();
  }
}


long long int get_key( unsigned char *key )
{
  long long int length = 0;
  int char_buf;

  while( !isalnum( char_buf = getchar() ) );

  while( ( isalnum( char_buf ) ) && ( MAXSTR - 1 > length ) )
  {
    key[length++] = (unsigned char)( char_buf );
    char_buf = getchar();
  }

  key[length] = '\0';
  return length;
}
