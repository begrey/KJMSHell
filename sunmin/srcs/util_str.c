#include "./minishell.h"

int		is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int		is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}
