#include "minishell.h"

void		ft_pwd()
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
	exit(0);
}

