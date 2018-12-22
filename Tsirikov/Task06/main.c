#include "hash.h"
#include "table.h"


#define MAXSTR 64


int main()
{
	size = 100;
	set_hash_name('m');
	Table = make_table();

	char localbuf[MAXSTR];
	while( NULL != fgets( localbuf, MAXSTR, stdin ) )
	{
		insert_key( (unsigned char *)( localbuf ), strlen( localbuf ) );
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
