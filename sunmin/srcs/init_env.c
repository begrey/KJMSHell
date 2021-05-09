#include "minishell.h"

int		init_env(char *envp[])
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_envadd_back(&env, ft_envnew(find_key(envp[i]), find_value(envp[i])));
		i++;
	}
	return (0);
}

/*
int		init_env(char *envp[])
{
	int		i;
	int		len;
	t_env	*temp;

	i = 0;
	while (envp[i])
		i++;
	len = i;
	temp = (t_env *)malloc(sizeof(t_env) * (len));
	env = ft_envnew(find_key(envp[0]), find_value(envp[0]));
	i = 1;
	while (i < len)
	{
		temp[i].key = find_key(envp[i]);
		temp[i].value = find_value(envp[i]);
		temp[i].if_value = 1;
		ft_envadd_back(&env, &temp[i]);
		i++;
	}
	return (0);
}
*/
