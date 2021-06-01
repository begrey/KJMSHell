#include "minishell.h"

void		ft_pwd(int pip_flag, t_env *env)
{
	char	*str;
	char	*buf;

	buf = NULL;
	str = getcwd(buf, 1);
	printf("%s\n", str);
	free(str);
	if (pip_flag == 0)
		exit(0);
	else
		put_return(0, env);
}

