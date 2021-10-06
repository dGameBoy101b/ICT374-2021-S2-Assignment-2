#include "command.h"
#include <stdlib.h>

struct Command* createCom()
{
	struct Command* com = malloc(sizeof(struct Command));
	if (com == NULL)
		return NULL;
	struct CharVec* path = createCharVec();
	if (path == NULL)
	{
		free(com);
		return NULL;
	}
	com->path = path;
	struct CharVecVec* args = createCharVecVec();
	if (args == NULL)
	{
		free(com);
		destroyCharVec(path);
		return NULL;
	}
	com->args = args;
	com->input_file = NULL;
	com->output_file = NULL;
	com->input_pipe = NULL;
	com->output_pipe = NULL;
	return com;
}

void destroyCom(struct Command* com)
{
	if (com == NULL)
		return;
	destroyCharVec(com->path);
	destroyCharVecVec(com->args);
	if (com->input_file != NULL)
		destroyCharVec(com->input_file);
	if (com->output_file != NULL)
		destroyCharVec(com->output_file);
	if (com->input_pipe != NULL)
		com->input_pipe->output_pipe = NULL;
	if (com->output_pipe != NULL)
		com->output_pipe->input_pipe = NULL;
	free(com);
}

int copyCom(struct Command* dst, const struct Command* src)
{
	if (dst == NULL || src == NULL)
		return 0;
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
	dst->input_pipe = src->input_pipe;
	dst->output_pipe = src->output_pipe;
	return 1;
}

int equalCom(const struct Command* com1, const struct Command* com2)
{
	return com1 != NULL
		&& com2 != NULL
		&& com1->input_pipe == com2->input_pipe
		&& com1->output_pipe == com2->output_pipe
		&& equalCharVec(com1->path, com2->path)
		&& equalCharVecVec(com1->args, com2->args)
		&& ((com1->input_file == NULL && com2->input_file == NULL)
			|| (com1->input_file != NULL && equalCharVec(com1->input_file, com2->input_file)))
		&& ((com1->output_file == NULL && com2->output_file == NULL)
			|| (com1->output_file != NULL && equalCharVec(com1->output_file, com2->output_file)));
}
