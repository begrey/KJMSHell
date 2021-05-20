#include "minishell.h"

void		ft_pwd(t_line *line)
{
	char	buf[1024];

	if ((getcwd(buf, 1024)) == NULL)
	{
		printf("pwd error!\n")
		exit(1);
	}
	printf("%s\n", getcwd(buf, 1024));
}

