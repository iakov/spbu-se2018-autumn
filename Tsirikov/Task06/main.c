#include "hash.h"
#include "table.h"
#include "book.h"


#define MAXSTR 32


int main(int argc, char *argv[])
{
	size = 100;
	set_hash_name('m');
	Table = make_table();
	char filename[MAXSTR];

	if( 1 < argc )
	{
		analyse_book( ( argv[1] ) );
	}
	else
	{
		if( EOF == scanf( "%s", filename ) )
		{
			printf("Reading error\n");
			exit(4);
		}
		if( NULL != filename )
		{
			analyse_book( filename );
		}
		else
		{
			printf("Book name wasn`t given.\n");
			exit(1);
		}
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
