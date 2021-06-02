/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:44:30 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/02 17:07:26 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**make_list_argv(t_line *line, char *file_name)
{
	int		len;
	char	**argv;

	len = ft_listsize(line);
	if (file_name != NULL)
		len++;
	argv = (char **)malloc(sizeof(char *) * (len + 1));
	argv[len] = NULL;
	len = 0;
	while (line != NULL)
	{
		argv[len] = line->arg;
		line = line->next;
		len++;
	}
	if (file_name != NULL)
		argv[len++] = file_name;
	argv[len] = NULL;
	return (argv);
}

void		other_command(t_line *line, t_env *env,
char *file_name, int pip_flag)
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
			put_return(status, env);
		}
		else
			other_command_exec(line, env, file_name);
	}
	else
		other_command_exec(line, env, file_name);
}

char		*make_env_path(t_line *line, char *path)
{
	char	*env_path;
	char	*path_slash;
	char	*temp_slash;

	path_slash = ft_strjoin(path, "/");
	temp_slash = path_slash;
	env_path = ft_strjoin(path_slash, line->arg);
	free(temp_slash);
	return (env_path);
}

void		not_found_command(char **a, char **p, t_line *line, t_env *env)
{
	free_split(a);
	free_split(p);
	write(2, line->arg, ft_strlen(line->arg));
	write(2, ": command not found\n", 20);
	put_return(127, env);
	exit(127);
}

void		other_command_exec(t_line *line, t_env *env, char *file_name)
{
	int		i;
	char	**path;
	char	*new_path;
	char	**argv;
	char	*temp_env;

	temp_env = extract_env("$PATH", env);
	path = ft_split(temp_env, ':');
	free(temp_env);
	i = 0;
	argv = make_list_argv(line, file_name);
	execve(line->arg, argv, NULL);
	while (path[i])
	{
		if ((ft_strncmp(path[i], line->arg, ft_strlen(path[i]))) != 0)
			new_path = make_env_path(line, path[i]);
		else
			new_path = ft_strdup(line->arg);
		execve(new_path, argv, NULL);
		free(new_path);
		i++;
	}
	not_found_command(argv, path, line, env);
}
