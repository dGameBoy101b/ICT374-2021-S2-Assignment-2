#include "wildcard_path_expand.h"
#include <glob.h>
#include <stdlib.h>

int expandArgPaths(struct Command*const com)
{
	if (com == NULL)
		return 0;
	struct CharVecVec* args = createCharVecVec();
	if (args == NULL)
		return 0;
	struct CharVec* new_arg = createCharVec();
	if (new_arg == NULL)
	{
		destroyCharVecVec(args);
		return 0;
	}
	char* str = NULL;
	glob_t expand;
	for (struct CharVec* arg = com->args->vec; arg < com->args->vec + com->args->count; ++arg)
	{
		if (!getStrCharVec(&str, arg))
		{
			destroyCharVecVec(args);
			destroyCharVec(new_arg);
			free(str);
			return 0;
		}
		if (glob(str, GLOB_NOSORT | GLOB_NOCHECK | GLOB_NOMAGIC, NULL, &expand) != 0)
		{
			destroyCharVecVec(args);
			destroyCharVec(new_arg);
			free(str);
			return 0;
		}
		for (char** expand_arg = expand.gl_pathv; expand_arg < expand.gl_pathv + expand.gl_pathc; ++expand_arg)
		{
			if (!setCharVec(new_arg, str))
			{
				destroyCharVecVec(args);
				destroyCharVec(new_arg);
				free(str);
				return 0;
			}
            if (!appendEleCharVecVec(args, new_arg))
			{
				destroyCharVecVec(args);
				destroyCharVec(new_arg);
				free(str);
				return 0;
			}
		}
	}
	destroyCharVecVec(com->args);
	com->args = args;
	return 1;
}
