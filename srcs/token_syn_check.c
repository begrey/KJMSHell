#include "minishell.h"

static int	semi_pipe(char *s)
{
	if (ft_strcmp(s, ";") == 0 || ft_strcmp(s, "|") == 0)
		return (1);
	return (0);
}

int		token_syn_check(t_line *line)
{
	t_line *temp;

	temp = line;

	if (semi_pipe((line)->arg))		// 처음부터 세미 파이프면 안됨
	{
		printf("syntax error near unexpected token \'%c\'\n", line->arg[0]);
		return (-1);
	}
	while (temp)
	{
		if (is_token(temp->arg))
		{
			if (temp->next == NULL && temp->arg[0] != ';')
			{
				printf("zz syntax error near unexpected token \'%c\'\n", temp->arg[0]);
				return (-1);
			}
			temp = temp->next;
			if (temp && is_token(temp->arg))
			{
				printf("syntax error near unexpected token \'%c\'\n", temp->arg[0]);
				return (-1);
			}
		}
		temp = temp->next;
	}
	return (0);
}
