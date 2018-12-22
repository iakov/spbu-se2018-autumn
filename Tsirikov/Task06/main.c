#include "hash.h"
#include "table.h"
#include "book.h"


#define MAXSTR 32


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
		exit(7);
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
