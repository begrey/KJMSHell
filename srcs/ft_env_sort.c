#include "minishell.h"

void		ft_env_sort(t_env **env)
{

	t_env	*repeat;
	t_env	*again;
	char	*tmp;
	char	*str_temp;

	again = *env;
	while (again)
	{
		repeat = *env;
		while (repeat)
		{
			if (repeat->next && ft_strcmp(repeat->key, repeat->next->key) > 0)		// 앞이 더 크면 자리 바꿈
			{

				tmp = (repeat->key);

				repeat->key = (repeat->next->key);

				repeat->next->key = (tmp);
				tmp = (repeat->value);
				repeat->value = (repeat->next->value);
				repeat->next->value = (tmp);
			}
			repeat = repeat->next;
		}
		again = again->next;
	}
}
