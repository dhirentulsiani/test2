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
	//what if nit in firstt block
	//fprintf(stdout, "hello");
	
	if (strnlen(filename, 13) > 11) {
		fprintf(stderr, "nme toolong\n");
	}
	int i;
	FILE *fp = openfs(filesystem, "r");
	fentry f;
	int count = -20;
	//int foundspace;
	for (i = 0; i < MAXFILES; i++) {
		if ((fread(&f, sizeof(fentry), 1, fp)) == 0) {
				fprintf(stderr, "Error: could not read file entries\n");
        closefs(fp);
        exit(1);
			} 
		else {
			// can the input ever be emty
			fprintf(stdout, "hello");
			if (f.name[0] == '\0' && f.size == 0 && f.firstblock == -1) {
				count = i;
				break;
				}
			}
	
	
	}
	if (count == -20) {
		fprintf(stderr, "No spce\n");
	}
	//close fk
	closefs(fp);
	
	fentry newfile;
	strncpy(newfile.name, filename, 12);
	newfile.size = 0;
	newfile.firstblock = -1;
	
	printf("%d\n", count);
	printf("%s\n", newfile.name);
	//what if notnin firat bloxk
	FILE *writefile = openfs(filesystem, "r+");
	fseek(writefile, sizeof(fentry) * count, SEEK_SET);
	fwrite(&newfile, sizeof(fentry), 1, writefile);
	
}
