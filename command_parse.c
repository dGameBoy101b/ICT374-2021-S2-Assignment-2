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
		destroyJob(job);
		return 0;
	}
	int redir_in = 0;
	int redir_out = 0;
	for (unsigned int i = 0; i < tokens->count; ++i)
	{
		switch (tokens->vec[i].vec[0])
		{
		case JOB_SEP_ASYNC:
			job->async = 1;
		case JOB_SEP_SEQ:
			for (unsigned int j = 0; j < job->count - 1; ++j)
			{
				job->coms[j].output_pipe = job->coms + j + 1;
				job->coms[j + 1].input_pipe = job->coms + j;
			}
			if (!appendEleJobVec(out, job) || !clearJob(job) || !clearCom(com))
			{
				destroyJob(job);
				destroyCom(com);
				return 0;
			}
			redir_in = 0;
			redir_out = 0;
			break;
		case COM_SEP_PIPE:
			if (!appendEleJob(job, com) || !clearCom(com))
			{
				destroyJob(job);
				destroyCom(com);
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
				if (!copyCharVec(com->input_file, tokens->vec + i))
				{
					destroyJob(job);
					destroyCom(com);
					return 0;
				}
			}
			else if (redir_out)
			{
				redir_out = 0;
				if (!copyCharVec(com->output_file, tokens->vec + i))
				{
					destroyJob(job);
					destroyCom(com);
					return 0;
				}
			}
			else if (com->path->count < 1)
			{
				if (!copyCharVec(com->path, tokens->vec + i))
				{
					destroyJob(job);
					destroyCom(com);
					return 0;
				}
			}
			else
			{
				if (!appendEleCharVecVec(com->args, tokens->vec + i))
				{
					destroyJob(job);
					destroyCom(com);
					return 0;
				}
			}
		}
	}
	if (out->count > 0)
	{
		for (unsigned int j = 0; j < job->count - 1; ++j)
		{
			job->coms[j].output_pipe = job->coms + j + 1;
			job->coms[j + 1].input_pipe = job->coms + j;
		}
		if (!appendEleJobVec(out, job))
		{
			destroyJob(job);
			destroyCom(com);
			return 0;
		}
	}
	destroyJob(job);
	destroyCom(com);
	return 1;
}
