#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define LETTER( x ) (x) == 1 ? "." : "s."
#define UPTABLE 1000


typedef struct Table
{
  unsigned char *key;
  long long int value;
  struct Table *next;
} Item;


Item *Table;
long long int size = 0;
long long int load = 0;
long long int diff = 0;


Item *make_table()
{
  return (Item *)( calloc( size, sizeof( Item ) ) );
}


void clear_chain( Item *socket )
{
  if( 0 != socket->value )
  {
    free( socket->key );
    socket->key = NULL;
    socket->value = 0;
  }

  if( NULL != socket->next )
  {
    clear_chain( socket->next );
    free( socket->next );
    socket->next = NULL;
  }
}


void clear_table()
{
  for( int i = 0; i < size; i++ )
  {
    if( 0 != Table[i].value )
    {
      free( Table[i].key );
      Table[i].key = NULL;
      Table[i].value = 0;
    }

    if( NULL != Table[i].next )
    {
      clear_chain( Table[i].next );
      free( Table[i].next );
      Table[i].next = NULL;
    }
  }
  free( Table );
}


void insert_in_chain( Item *socket, unsigned char *key, long long int length )
{
  if( 0 == socket->value )
  {
    socket->value = 1;
    diff++;

    if( NULL == ( socket->key = (unsigned char *)\
 ( calloc( length + 1, sizeof( unsigned char ) ) ) ) )
    {
      printf( "Can`t allocate memory.\n" );
      exit(4);
    }

    if( NULL == ( strcpy( (char *)( socket->key ), (const char *)( key ) ) ) )
    {
      printf( "Can`t copy a key.\n" );
      exit(4);
    }
  }
  else if( 0 == strcmp( (const char *)( socket->key ), (const char *)( key ) ) )
  {
    socket->value++;
  }
  else
  {
    if( NULL == socket->next )
    {
      if( NULL == ( socket->next = (Item *) ( calloc( 1, sizeof( Item ) ) ) ) )
      {
        printf( "Can`t allocate memory.\n" );
        exit(4);
      }
    }
    insert_in_chain( socket->next, key, length );
  }
}


void remake_table();


void insert_key( unsigned char *key, long long int length )
{
  load++;
  insert_in_chain( Table + hash( key, length ), key, length );
  if( diff == size )
  {
    remake_table();
  }
}

/*	unused in final realisation

long long int key_search_in_chain( Item *socket, unsigned char *key, long long int length )
{
  if( ( 0 != strcmp( (const char *)( socket->key ),\
 (const char *)( key ) ) ) && ( NULL == socket->next ) )
  {
    return 0;
  }
  else if( 0 == strcmp\
( (const char *)( socket->key ), (const char *)( key ) ) )
  {
    return socket->value;
  }
  else
  {
      return key_search_in_chain( socket->next, key, length );
  }
}


void find_key( unsigned char *key, long long int length )
{
  long long int value = key_search_in_chain\
( Table + hash( key, length ), key, length );

  if( 0 == value )
  {
    printf( "There`s not such key.\n" );
  }
  else
  {
    printf( "Taken %lld key%s\n", value, LETTER( value ) );
  }
}

*/


void show_items_in_chain( Item *socket )
{
  if( 0 != socket->value )
  {
    fprintf( stdout, "%s %lld\n", socket->key, socket->value );
  }

  if( NULL != socket->next )
  {
    show_items_in_chain( socket->next );
  }
}


void iterate()
{
  for( int i = 0 ; i < size ; i++ )
  {
    show_items_in_chain( Table + i );
  }
}


long long int analyse_chain( Item *socket, int depth, long long int *count_word, unsigned char **max_word )
{
  if( NULL != socket->next )
  {
    depth = analyse_chain( socket->next, depth + 1, count_word, max_word);
  }

  if( socket->value > *count_word )
  {
    *count_word = socket->value;
    *max_word = socket->key;
  }

  return depth;
}


void statistics( unsigned char **max_word, long long int *count_word )
{
  long long int max_chain = 1;
  long long int buf;

  if( 1 <= diff )
  {
    for( int i = 0 ; i < size ; i++ )
    {
      buf = analyse_chain( Table + i, 1, count_word, max_word );

      if ( max_chain < buf )
      {
        max_chain = buf;
      }
    }
  }
  else
  {
    max_chain = diff;
  }

  /*if( 0 != size )
  {
    printf( "%lld keys are received.\n", load );
    printf( "%lld of them are different.\n", diff );
    printf( "Table`s load is %.0f%%.\n", (float)( diff * 100.0 / size ) );
    printf( "Largest chain is %lld pair%s\n", max_chain, LETTER( max_chain ) );
    printf( "Most popular word \"%s\" has met %lld time%s\n", max_word, *count_word, LETTER( *count_word ) );
  }*/
}


void copy_in_chain( Item *socket, Item *copy )
{
  if( 0 != socket->value )
  {
    if( 0 == copy->value )
    {
      copy->value = socket->value;
      if( NULL == ( copy->key = (unsigned char *) ( calloc\
( strlen( (const char *)( socket->key ) ) + 1, sizeof( unsigned char ) ) ) ) )
      {
        printf( "Can`t allocate memory.\n");
        exit(4);
      }
      strcpy( (char *)( copy->key ), (const char *)( socket->key ) );
    }
    else
    {
      if( NULL == copy->next )
      {
        if( NULL == ( copy->next = (Item *)( calloc( 1, sizeof( Item ) ) ) ) )
        {
          printf( "Can`t allocate memory.\n" );
          exit(4);
        }
      }
      copy_in_chain( socket, copy->next );
    }
  }
}


void remake_table()
{
  size += UPTABLE;

  Item *copy = make_table();
  Item *socket;
  long long int buf;

  for( int i = 0 ; i < size - UPTABLE ; i++ )
  {
    socket = Table + i;

    while( NULL != socket->next )
    {
      buf = hash( socket->key, strlen( (const char *)( socket->key ) ) );
      copy_in_chain( socket, copy + buf );
      socket = socket->next;
    }

    if( 0 != socket->value )
    {
      buf = hash( socket->key, strlen( (const char *)( socket->key ) ) );
      copy_in_chain( socket, copy + buf );
    }
  }

  size -= UPTABLE;
  clear_table();
  size += UPTABLE;
  Table = copy;
}
