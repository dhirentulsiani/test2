#include <stdio.h>
#include "simfstypes.h"

/* File system operations */
void printfs(char *);
void initfs(char *);

/* Internal functions */
FILE *openfs(char *filename, char *mode);
void closefs(FILE *fp);
void createfile(char *filesystem, char *filename);
void writefile(char *filesystem, char *filename, int start, int length, char *towrite);
