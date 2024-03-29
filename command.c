#include "command.h"
#include <stdlib.h>

struct Command* emplaceCom(struct Command* com)
{
	if (com == NULL)
		return NULL;
	com->path = NULL;
	com->args = NULL;
	com->input_file = NULL;
	com->output_file = NULL;
	return com;
}

struct Command* createCom()
{
	struct Command* com = malloc(sizeof(struct Command));
	if (com == NULL)
		return NULL;
	emplaceCom(com);
	com->path = createCharVec();
	com->args = createCharVecVec();
	return com;
}

void destroyCom(struct Command** com)
{
	if (com == NULL || *com == NULL)
		return;
	destroyCharVec((*com)->path);
	destroyCharVecVec(&((*com)->args));
	if ((*com)->input_file != NULL)
		destroyCharVec((*com)->input_file);
	if ((*com)->output_file != NULL)
		destroyCharVec((*com)->output_file);
	free(*com);
	*com = NULL;
}

int copyCom(struct Command* dst, const struct Command* src)
{
	if (dst == NULL || src == NULL)
		return 0;
	if (dst->path == NULL)
		dst->path = createCharVec();
	if (dst->args == NULL)
		dst->args = createCharVecVec();
	if (!copyCharVec(dst->path, src->path))
		return 0;
	if (!copyCharVecVec(dst->args, src->args))
		return 0;
	if (src->input_file == NULL)
	{
		if (dst->input_file != NULL)
			destroyCharVec(dst->input_file);
		dst->input_file = NULL;
	}
	else
	{
		if (dst->input_file == NULL)
			dst->input_file = createCharVec();
		if (!copyCharVec(dst->input_file, src->input_file))
			return 0;
	}
	if (src->output_file == NULL)
	{
		if (dst->output_file != NULL)
			destroyCharVec(dst->output_file);
		dst->output_file = NULL;
	}
	else
	{
		if (dst->output_file == NULL)
			dst->output_file = createCharVec();
		if (!copyCharVec(dst->output_file, src->output_file))
			return 0;
	}
	return 1;
}

int equalCom(const struct Command* com1, const struct Command* com2)
{
	return com1 != NULL
		&& com2 != NULL
		&& equalCharVec(com1->path, com2->path)
		&& equalCharVecVec(com1->args, com2->args)
		&& ((com1->input_file == NULL && com2->input_file == NULL)
			|| (com1->input_file != NULL && equalCharVec(com1->input_file, com2->input_file)))
		&& ((com1->output_file == NULL && com2->output_file == NULL)
			|| (com1->output_file != NULL && equalCharVec(com1->output_file, com2->output_file)));
}

int clearCom(struct Command*const com)
{
	if (com == NULL)
		return 0;
	clearCharVec(com->path);
	clearCharVecVec(com->args);
	if (com->input_file != NULL)
		destroyCharVec(com->input_file);
	com->input_file = NULL;
	if (com->output_file != NULL)
		destroyCharVec(com->output_file);
	com->output_file = NULL;
	return 1;
}
