#include "command_parse.h"
#include <stdlib.h>

int parseCommands(struct JobVec*const out, const struct CharVecVec*const tokens)
{
	if (out == NULL || tokens == NULL)
		return 0;
	struct Job* job = createJob();
	if (job == NULL)
		return 0;
	struct Command* com = createCom();
	if (com == NULL)
	{
		destroyJob(&job);
		return 0;
	}
	struct CharVec* str = createCharVec();
	if (str == NULL)
	{
		destroyJob(&job);
		destroyCom(&com);
		return 0;
	}
	int redir_in = 0;
	int redir_out = 0;
	for (unsigned int i = 0; i < tokens->count; ++i)
	{
		switch (tokens->vec[i]->vec[0])
		{
		case JOB_SEP_ASYNC:
			job->async = 1;
		case JOB_SEP_SEQ:
			if (!appendEleJob(job, com) || !clearCom(com) || !appendEleJobVec(out, job) || !clearJob(job))
			{
				destroyJob(&job);
				destroyCom(&com);
				destroyCharVec(str);
				return 0;
			}
			redir_in = 0;
			redir_out = 0;
			break;
		case COM_SEP_PIPE:
			if (!appendEleJob(job, com) || !clearCom(com))
			{
				destroyJob(&job);
				destroyCom(&com);
				destroyCharVec(str);
				return 0;
			}
			redir_in = 0;
			redir_out = 0;
			break;
		case REDIR_IN:
			redir_in = 1;
			break;
		case REDIR_OUT:
			redir_out = 1;
			break;
		default:
			if (redir_in)
			{
				redir_in = 0;
				if (com->input_file == NULL)
					com->input_file = createCharVec();
				if (!copyCharVec(com->input_file, tokens->vec[i]))
				{
					destroyJob(&job);
					destroyCom(&com);
					destroyCharVec(str);
					return 0;
				}
			}
			else if (redir_out)
			{
				redir_out = 0;
				if (com->output_file == NULL)
					com->output_file = createCharVec();
				if (!copyCharVec(com->output_file, tokens->vec[i]))
				{
					destroyJob(&job);
					destroyCom(&com);
					destroyCharVec(str);
					return 0;
				}
			}
			else
			{
				if (!clearCharVec(str) || !reserveCharVec(str, tokens->vec[i]->count)
						|| (tokens->vec[i]->vec[0] != COM_PARSE_ESCAPE && !appendEleCharVec(str, tokens->vec[i]->vec[0])))
				{
					destroyJob(&job);
					destroyCom(&com);
					destroyCharVec(str);
					return 0;
				}
				for (unsigned int j = 1; j < tokens->vec[i]->count; ++j)
				{
					if (!appendEleCharVec(str, tokens->vec[i]->vec[j]))
					{
						destroyJob(&job);
						destroyCom(&com);
						destroyCharVec(str);
						return 0;
					}
				}
				if (com->path->count < 1 && !copyCharVec(com->path, str))
				{
					destroyJob(&job);
					destroyCom(&com);
					destroyCharVec(str);
					return 0;
				}
				if (!appendEleCharVecVec(com->args, str))
				{
					destroyJob(&job);
					destroyCom(&com);
					destroyCharVec(str);
					return 0;
				}
			}
		}
	}
	if (com->path->count > 0 && (!appendEleJob(job, com) || !appendEleJobVec(out, job)))
	{
		destroyJob(&job);
		destroyCom(&com);
		destroyCharVec(str);
		return 0;
	}
	destroyJob(&job);
	destroyCom(&com);
	destroyCharVec(str);
	return 1;
}
