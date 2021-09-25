#include <stdlib.h>
#include <stdio.h>
#include "prntCWD.h"

void TestGetCWD(char *pathsFile)
{
	char *str = malloc(sizeof(char) * 512);
	if(str == NULL)
	{
		fprintf(stderr, "No memory!");
	}

	FILE *f = fopen(pathsFile, "r");

	while(fgets(str, 512, f) != NULL)
	{
		if(chdir(str) == 0)
		{
			char *temp = GetCWD();
			printf("Test input: %s\n", str);
			printf("GetCWD() returns: %s\n", temp);
			free(temp);
			temp = NULL;
		}
	}
	
	fclose(f);
}
int main(int argc, char *argv[])
{
	
	exit(0);
}
