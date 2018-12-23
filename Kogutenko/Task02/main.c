#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void read_parameter(int *argc, char **argv);

bool from_specified = false, to_specified = false;
int from, to;
int i = 1; // Parameter number
int numbers[100], p = 0; // Numbers array for sorting and pointer
bool changed[100]; // To check if the element has been moved

extern char sort();

int main(int argc, char **argv) {
	// Reading parameters
	read_parameter(&argc, argv);
	read_parameter(&argc, argv);
	
	// Reading numbers
	int current;
	while(scanf("%d", &current) != EOF) {
		if(from_specified == true && current <= from) {
			printf("%d ", current);
			if(to_specified == true && current >= to) {
				fprintf(stderr, "%d ", current);
			}
			continue;
		}
		if(to_specified == true && current >= to) {
			fprintf(stderr, "%d ", current);
			continue;
		}
		numbers[p] = current;
		changed[p] = false;
		++p;
	}
	return sort();
}


// Reads parameter. Works with "--<param>=<num>", "--<param><>=<num>", "--<param>= <num>" and "--<param> = <num>"
void read_parameter(int *argc, char **argv) {
	if(i < *argc) {
		if(argv[i][2] == 'f') {
			// "--from" specified
			from_specified = true;
			if(argv[i][6] == '=') {
				// No space after "--from"
				if(argv[i][7] == '\0') {
					// Space after "equal"
					++i;
					from = atoi(&argv[i][0]);
					++i;
				} else {
					// No space after "equal"
					from = atoi(&argv[i][7]);
					++i;
				}
			} else {
				// Space after "--from"
				++i;
				if(argv[i][1] == '\0') {
					// Space after "equal"
					++i;
					from = atoi(&argv[i][0]);
					++i;
				} else {
					// No space after "equal"
					from = atoi(&argv[i][1]);
					++i;
				}
			}
		} else {
			// "--to" specified
			to_specified = true;
			if(argv[i][4] == '=') {
				// No space after "--to"
				if(argv[i][5] == '\0') {
					// Space after "equal"
					++i;
					to = atoi(&argv[i][0]);
					++i;
				} else {
					// No space after "equal"
					to = atoi(&argv[i][5]);
					++i;
				}
			} else {
				// Space after "--to"
				++i;
				if(argv[i][1] == '\0') {
					// Space after "equal"
					++i;
					to = atoi(&argv[i][0]);
					++i;
				} else {
					// No space after "equal"
					to = atoi(&argv[i][1]);
					++i;
				}
			}
		}
	}
}

