#include "get_line.h"
#include "char_vector.h"
#include <stdio.h>

int getLine(struct CharVec* v)
{
	if (!clearCharVec(v)) return 0;
	int c;
	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n') break;
		if (!appendEleCharVec(v, (char)c)) return 0;
	}
	return 1;
}
