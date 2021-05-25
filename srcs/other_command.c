#include "minishell.h"

char		**make_list_argv(t_line *line)
{
	int		i;
	int		len;
	char	**argv;
	t_line	*temp;

	i = 0;
	len = 0;
	temp = line;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	if (len == 0)		//
		return (0);		//
	argv = (char **)malloc(sizeof(char) * (len + 1));
	while (line != NULL)
	{
		argv[i] = line->arg;
		line = line->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void		other_command(t_line *line, char *file_name, t_env *env)
{
	int		i;
	char	**path;
	char	*new_path;
	char	**argv;
	char	*path_slash;

	path = ft_split(extract_env("$PATH", env), ':');
	i = 0;
	if ((argv = make_list_argv(line)) == 0)
	{
		argv = (char **)malloc(sizeof(char *) * 2);
		argv[0] = file_name;
		argv[1] = NULL;
	}
	execve(line->arg, argv, NULL);
	while (path[i])	// 환경변수에서 PATH경로 찾아서 찾음
	{  //ft_strncmp 를 이용해 환경변수 PATH부분과 앞이 똑같으면 그대로 실행, 아니면 직접 붙여주기
		if ((ft_strncmp(path[i], line->arg, ft_strlen(path[i]))) != 0)
		{//직접 환경변수 PATH 접합
			path_slash = ft_strjoin(path[i], "/");
			new_path = ft_strjoin(path_slash, line->arg);
		}
		else
			new_path = line->arg;
		argv = make_list_argv(line);
		execve(new_path, argv, NULL);
		i++;
	}
	printf("%s: command not found\n", line->arg);
	exit(1);
}
// int main()
// {
// 	t_line *list;

// 	list = NULL;
// 	ft_listadd_back(&list, ft_listnew("echo"));
// 	ft_listadd_back(&list, ft_listnew("hi"));
// 	ft_listadd_back(&list, ft_listnew("everyone"));
// 	//char	**argv = make_list_argv(list);
// 	other_command(list);
// 	//char *const argv[] = {"/bin/echo", "hi", NULL};
// 	//execve("/bin/echo", argv, NULL);
// }	
