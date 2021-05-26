#include "minishell.h"

void		ft_pwd()
{
	char	*str;
	char	*buf;

	buf = NULL;
	if (!(str = getcwd(buf, 1)))
	{
		printf("pwd error!\n");
		exit(1);
	}
	printf("%s\n", str);
	exit(0);
}

