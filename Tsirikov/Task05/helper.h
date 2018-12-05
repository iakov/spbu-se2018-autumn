char input(char *argv[])
{
	short buf = 0;
	while (argv[1][buf] != '\0')
		number_of_strings = 10 * number_of_strings + (long) (argv[1][buf++] - '0');
	if ((InputFile = fopen((argv[2]), "r")) == NULL)
	{
		printf("Can`t open \"%s\" file.\n", argv[2]);
		exit(0);
	}
	switch ((char) (argv[3][0]))
    {
        case 'b': case 'i': case 'm': case 'q': case 'r':
		  return (char) (argv[3][0]);
            break;
        default:
            return 0;
            break;
    }
}


int read_file(FILE *InputFile, char *strings[])
{
	short length;
	int *buf = calloc(MAX_STR_LENGTH, sizeof(int));
	for (long line_number = 0; line_number < number_of_strings; line_number++)
	{
		for (length = 0; (buf[length] = getc(InputFile)) != 10 && buf[length] != -1; length++);
		strings[line_number] = calloc(length + 1, sizeof(char));
		strings[line_number][length--] = '\0';
		for (; length >= 0; length--)
			strings[line_number][length] = (char) buf[length];
	}
	free(buf);
	fclose(InputFile);
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
			break;
	}
	return 0;
}


int print_sorted(char **strings)
{
	for (long line_number = 0; line_number < number_of_strings; line_number++)
		printf("%s\n", strings[line_number]);
	return 0;
}


int memory_flush(char *strings[])
{
	for (long line_number = 0; line_number < number_of_strings; line_number++)
		free(strings[line_number]);
	free(strings);
	return 0;
}
