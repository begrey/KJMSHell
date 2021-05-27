#include "minishell.h"

void		ft_pwd(int pip_flag)
{
	char	*str;
	char	*buf;

	buf = NULL;
	if (!(str = getcwd(buf, 1)))
	{
		printf("pwd: %s\n", strerror(errno));
		exit(1);
	}
	printf("%s\n", str);
	if (pip_flag == 0)
		exit(0);
}

