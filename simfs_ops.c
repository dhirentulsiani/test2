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
		exit(1);
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
		else if (strncmp(f.name, filename, 12) == 0) {
			fprintf(stderr, "Error: Duplicate name\n");
			closefs(fp);
			exit(1);
			}
		else {
			// can the input ever be emty
			//fprintf(stdout, "hello");
			if (f.name[0] == '\0' && f.size == 0 && f.firstblock == -1) {
				count = i;
				break;
				}
			}
	
	
	}
	if (count == -20) {
		fprintf(stderr, "No spce\n");
		closefs(fp);
		exit(1);
	}
	//close fk
	closefs(fp);
	
	fentry newfile;
	strncpy(newfile.name, filename, 12);
	newfile.size = 0;
	newfile.firstblock = -1;
	
	//printf("%d\n", count);
	//printf("%s\n", newfile.name);
	//what if notnin firat bloxk
	FILE *writefile = openfs(filesystem, "r+");
	fseek(writefile, sizeof(fentry) * count, SEEK_SET);
	if (fwrite(&newfile, sizeof(fentry), 1, writefile) < 1) {
		fprintf(stderr, "sum thing wong\n");
		closefs(writefile);
		exit(1);
		}
	
}
/*
Writefile docs
possible errors:
start > file size
not ennough free blocks available.
stdin less than len argunent,
number of arguments not correct
file not found error.

Start by finding filentry, check start > filesize,
calculate if eniugh free blocks availabke,
fread stdin to a char array, make sure length >= fread.
if firstblock != -1, fill up current block, else/then find next availabke block, fill it up, until all has been written. Make sure to alwys be updating and writing fnodes, remember to update first node if needed


write the finished fentryv(with correct size)


*/

/*
fentry findfile(char *fsystem, char *fname) {
	int i;
	for (i = 0, i < MAXFILES, i++) {
			
		}
	}*/

void writefile(char *filesystem, char *filename, int start, int length, char *towrite) {
	
	//if stdin is empty
	
	//printf("%s%s%d%d", filesystem, filename, start, length);
	FILE *fp = openfs(filesystem, "r+");
	int i;
	int count = -20;
	fentry f;
	for (i = 0; i < MAXFILES; i++) {
		if ((fread(&f, sizeof(fentry), 1, fp)) == 0) {
				fprintf(stderr, "Error: could not read file entries\n");
        closefs(fp);
        exit(1);
			} 
		else if (strncmp(f.name, filename, 12) == 0) {
			count = i;
			break;
			}
	}
	
	if (count == -20) {
		fprintf(stderr, "file not exisy\n");
		closefs(fp);
		exit(1);
	}
	
	//printf("%s\n", f.name);
	if (start > f.size) {
		fprintf(stderr, "start too large\n");
		closefs(fp);
		exit(1);
	}
	
	fseek(fp, sizeof(fentry) * MAXFILES, SEEK_SET);
	fnode fnodes[MAXBLOCKS];
	if ((fread(fnodes, sizeof(fnode), MAXBLOCKS, fp)) == 0) {
        fprintf(stderr, "Error: could not read fnodes\n");
        closefs(fp);
        exit(1);
    }
    
    int freebytesneeded = (sizeof(char) * length) - (f.size - start);
    if (f.firstblock != -1) {
    	//find last node, calculate bytes used
    	int count = -1;
    	int prev = -1;
    	int curr = f.firstblock;
    	while (curr != -1) {
    		prev = curr;
    		curr = fnodes[prev].nextblock;
    		count++;
    	}
    	int numbytes = f.size - (BLOCKSIZE * count);
    	if (numbytes < 0) {
    	fprintf(stderr, "Error: numbytes wrong\n");
        closefs(fp);
        exit(1);
    	}
    	freebytesneeded -= numbytes;
    }
	
    printf("%d %d\n", freebytesneeded, (int) sizeof(char));
    int numBlocks = freebytesneeded / BLOCKSIZE;
    if (freebytesneeded % BLOCKSIZE != 0) {
    		numBlocks += 1;
    }
    
    int countBlocks = 0;
    fnode freeNode[numBlocks];
    for (i = 0; i < MAXBLOCKS; i++) {
    	if (fnodes[i].blockindex < 0) {
    		freeNode[countBlocks] = fnodes[i];
    		countBlocks++;
    	}
    	if (countBlocks == numBlocks) {break;}
    }
    
    if (countBlocks != numBlocks) {
    	fprintf(stderr, "Error: nofree space\n");
        closefs(fp);
        exit(1);
    }
    printf("%d\n", numBlocks);
    
    int startBlockNum= (start * sizeof(char)) / BLOCKSIZE;
    printf("strtblock: %d", startBlockNum);
    if (startBlockNum > numBlocks) {
   		fprintf(stderr, "Error: startblock wrobf\n");
        closefs(fp);
        exit(1);
    }
    fnode cur = fnodes[f.firstblock]
    while(startBlockNum != 0) {
    	cur = fnodes[cur.nextblock];
    	startBlockNum--;
    }
    fseek(fp, (cur.blockindex * B) + (start % BLOCKSIZE), SEEK_SET);
	//fwrite(const void *__buf, size_t __size, size_t __count, FILE *__fp);
		
		
	closefs(fp);
}
