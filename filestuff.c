#include <string.h>

#include "globaldefs.h"
#include "filestuff.h"

int loadfilestring(const char * filename, char ** output, int * length){
	FILE *file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	*length = ftell(file);
	if(debugmode) printf("DEBUG -- Opened file %s with length %i bytes\n", filename, *length);
	rewind(file);
	*output = malloc(*length+1);
	fread(*output, 1, *length, file);
	if(debugmode) printf("DEBUG -- Opened file contents: \n %s \n", *output);
	fclose(file);
	if(debugmode) printf("DEBUG -- Closed file %s \n", filename);
	return TRUE;
}
