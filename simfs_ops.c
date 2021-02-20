/* This file contains functions that are not part of the visible "interface".
 * They are essentially helper functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simfs.h"

/* Internal helper functions first.
 */

FILE *
openfs(char *filename, char *mode)
{
    FILE *fp;
    if((fp = fopen(filename, mode)) == NULL) {
        perror("openfs");
        exit(1);
    }
    return fp;
}

void
closefs(FILE *fp)
{
    if(fclose(fp) != 0) {
        perror("closefs");
        exit(1);
    }
}

/* File system operations: creating, deleting, reading, and writing to files.
 */

// Signatures omitted; design as you wish.
void
createfile(char *filesystem, char *filename)
{
	// make sure filename less than 12
	// 
	// Open file in read mode, do error checking
    // Loop through using fread with one femerry strUCT. keep count of current position. Once empty femerry found
	// Close readmode file do error checking
	int i;
	FILE *fp = openfs(filesystem, "r");
	fentry f;
	for (i = 0; i < MAXFILES; i++) {
		if ((fread(&f, sizeof(fentry), 1, fp)) == 0) {
				fprintf(stderr, "Error: could not read file entries\n");
        closefs(fp);
        exit(1);
			} 
		else {
			// can the input ever be emty
			if (f.name[0] == '\0' && f.size == 0 && f.firstblock == -1) {
				break;
				}
			}
	
	fprintf(stdout, "hello");
	}
}
