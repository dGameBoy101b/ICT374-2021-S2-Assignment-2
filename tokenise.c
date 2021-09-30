#include "tokenise.h"
#include <stdlib.h>
int tokenise(struct CharVecVec*const out, const struct CharVec*const str)
{
	if (out == NULL || str == NULL)
		return 0;
	if (!clearCharVecVec(out))
		return 0;
	struct CharVec* token = createCharVec();
	int is_token = 0;
	for (unsigned int c = 0; c < str->count; ++c)
	{
		switch (str->vec[c])
		{
			case TOKEN_SEP:
				if (is_token)
				{
					is_token = 0;
					if (!appendEleCharVecVec(out, token))
						return 0;
				}
				break;
			default:
				if (!is_token)
				{
					is_token = 1;
					if (!clearCharVec(token))
						return 0;
				}
				if (!appendEleCharVec(token, str->vec[c]))
					return 0;
		}
	}
	if (is_token)
		if (!appendEleCharVecVec(out, token))
			return 0;
    return 1;
}
