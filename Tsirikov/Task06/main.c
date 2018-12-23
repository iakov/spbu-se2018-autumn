#include "hash.h"
#include "table.h"


#define MAXSTR 64


int main()
{
	size = 100;		//size of table at the beginning
	set_hash_name('m'); 	//md5 hash-function as default
	Table = make_table();	//initializing table for start

	/* reading input from stdin by word,
	 * inserting key in table if not EOF*/

	char localbuf[MAXSTR];
	while( EOF != scanf( "%s", localbuf ) )
	{
		insert_key( (unsigned char *)( localbuf ), strlen( localbuf ) );
	}

	iterate();	//show pairs (key & value)
	
	/* searching for the most popular word in table */

	unsigned char *popular_word = NULL;
	unsigned char **pt_word = &popular_word;
	long long int popular_number = 0;
	statistics( pt_word, &popular_number );
	fprintf( stderr, "%s %lld\n", popular_word, popular_number );

	clear_table();	//deletes all keys & values, frees allocated memory
	return 0;
}
