#include "minishell.h"

void		ft_env_sort(t_env **env)
{
	t_env	*repeat;
	t_env	*again;
	char	*tmp;

	again = *env;
	while (again)
	{
		repeat = *env;
		while (repeat)
		{
			if (repeat->next && ft_strcmp(repeat->key, repeat->next->key) > 0)		// 앞이 더 크면 자리 바꿈
			{
				tmp = ft_strdup(repeat->key);
				repeat->key = ft_strdup(repeat->next->key);
				repeat->next->key = ft_strdup(tmp);
				tmp = ft_strdup(repeat->value);
				repeat->value = ft_strdup(repeat->next->value);
				repeat->next->value = ft_strdup(tmp);
			}
			repeat = repeat->next;
		}
		again = again->next;
	}

}
