#include "./hashes/sha1c.h"
#include "./hashes/md5c.h"


#define HEXMULTIPLE 256


extern long long int size;
long long int ( *hash )( unsigned char *, long long int );


long long int md5( unsigned char *string, long long int length )
{
  MD5_CTX mdContext;
  MD5Init( &mdContext );
  MD5Update( &mdContext, string, length );
  MD5Final( &mdContext );

  unsigned long long int buf = 0;

  for( int i = 0; i < 8; i++ )
  {
    buf *= HEXMULTIPLE;
    buf += (unsigned long long int)( mdContext.digest[i] );
  }
  buf = (long long int)( buf % size );
  return buf;
}


long long int sha1( unsigned char *string, long long int length )
{
  /*Buffer array for sha-1 hash code.*/

  unsigned char hash[21];

  SHA1( (char *)( hash ), (const char *)( string ), length );


  unsigned long long int buf = 0;

  for( int i = 0; i < 8; i ++ )
  {
    buf *= HEXMULTIPLE;
    buf += (unsigned long long int)( hash[i] );
  }
  buf = (long long int)( buf % size );
  return buf;
}


void set_hash_name( unsigned char hash_name )
{
  hash = hash_name == 'm' ? &md5 : &sha1;
}
