#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


#define MAXSTR 32


void analyse_book( char *bookname )
{
  int file_descriptor;
  if( 0 == ( file_descriptor = open( (const char *)( bookname ), O_RDONLY ) ) )
  {
    printf( "Can`t open the file.\n" );
    exit(2);
  }
  long long int file_size;
  if( 0 >= ( file_size = lseek( file_descriptor, 0, SEEK_END ) ) )
    {
      printf( "Can`t read the file.\n" );
      exit(3);
    }
  char *book;
  if( MAP_FAILED == ( book = (char *)\
( mmap( NULL, file_size, PROT_READ, MAP_SHARED, file_descriptor, 0 ) ) ) )
  {
    printf( "Can`t map the file into memory.\n" );
    exit(4);
  }
  long long int i = 0;
  long long int length = 0;
  unsigned char str_buf[MAXSTR];

  while( i < file_size - 1 )
  {
    for( ; ( ( !isalnum( (int)( book[i] ) ) ) && ( i < file_size - 1 ) ); i++);
    while( ( ( isalnum( (int)( book[i] ) ) )\
 && (length < MAXSTR - 1) ) && ( i < file_size - 1 ) )
    {
      str_buf[length++] = (unsigned char)( book[i] );
      i++;
    }
    str_buf[length] = '\0';
    insert_key( str_buf, length );
    length = 0;
  }
  if( -1 == munmap( book, file_size ) )
  {
    printf( "Can`t delete the mapping.\n" );
    exit(4);
  }
}
