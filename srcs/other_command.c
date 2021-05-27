#include "minishell.h"

char		**make_list_argv(t_line *line, char *file_name)
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
	if (file_name != NULL)
		len++;
	argv = (char **)malloc(sizeof(char) * (len + 1));
	while (line != NULL)
	{
		argv[i] = line->arg;
		line = line->next;
		i++;
	}
	if (file_name != NULL)
		argv[i++] = file_name;
	argv[i] = NULL;
	return (argv);
}
void		other_command(t_line *line, t_env *env, char *file_name, int pip_flag)
{
	int		status;
	pid_t	pid;

	if (pip_flag != 0)
	{
		pid = fork();
		if (pid != 0)
		{
			wait(&status);
			if (status >= 256)
				status /= 256;
			put_return(status, env); // (미출생)
		}
		else
		{
			other_command_exec(line, env, file_name);
		}
	}
	else
		other_command_exec(line, env, file_name);
}

void		other_command_exec(t_line *line, t_env *env, char *file_name)
{
	int		i;
	char	**path;
	char	*new_path;
	char	**argv;
	char	*path_slash;

	path = ft_split(extract_env("$PATH", env), ':');
	i = 0;
	argv = make_list_argv(line, file_name);
	//printf("%s   %s\n", argv[0], argv[1]);s
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
		argv = make_list_argv(line, file_name);
		execve(new_path, argv, NULL);
		i++;
	}
	write(2, line->arg, ft_strlen(line->arg));
	write(2, ": command not found\n", 20);
	//printf("%s: command not found\n", line->arg);
	put_return(127, env);
	exit(127);
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
