#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

void fget(FILE* file, int offset, int length, void* out)
{
	fseek(file, offset, SEEK_SET);
	fread(out, 1, length, file);
}
