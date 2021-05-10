#include "minishell.h"

void	exec_pwd(void)
{
	char	*current_path;
	char	*buf;

	buf = NULL;
	current_path = getcwd(buf, 1);
	printf("%s\n", current_path);
	free(current_path);
}

void	exec_cd(t_line **command_line)
{
	int		check;
	char	*str;

	str = ft_strdup("");
	check = 0;
	if ((*command_line)->next == NULL)
		ft_listadd_back(command_line, ft_listnew("/"));		// 루트가 아니라 홈(~)으로 수정해야 함
	check = chdir((*command_line)->next->arg);
	if (check != 0)
	{
		str = str_append1(str, "cd: ");
		str = str_append1(str, (*command_line)->next->arg);
		str = str_append1(str, ": No such file or directory\n");
	}
	printf("%s", str);
}
