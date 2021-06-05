/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:15:35 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/05 16:02:04 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*root_path(t_env *env)
{
	char	*user;
	char	*user_env;
	char	*root_path;

	user = ft_strdup("/USERS/");
	user_env = convert_env("$USER", env);
	root_path = ft_strjoin(user, user_env);
	free(user);
	free(user_env);
	return (root_path);
}

char		*convert_root_path(t_line *line, t_env *env)
{
	char	*root_path_result;
	char	*env_root;
	char	*line_arg;

	line_arg = ft_strdup(line->arg + 1);
	env_root = root_path(env);
	root_path_result = ft_strjoin(env_root, line_arg);
	free(line_arg);
	free(env_root);
	return (root_path_result);
}

void		cd_exit(t_env *env, int pip_flag)
{
	if (pip_flag == 0)
		exit(0);
	else
		put_return(0, env);
}

void		ft_cd(t_line *line, t_env *env, int pip_flag)
{
	int		check;
	char	*path;
	char	*str;
	char	*buf;

	buf = NULL;
	if (line == NULL)
		path = root_path(env);
	else if (line->arg[0] == '~')
		path = convert_root_path(line, env);
	else
		path = ft_strdup(line->arg);
	str = getcwd(buf, 1);
	check = chdir(path);
	free(path);
	if (check != 0)
	{
		printf("cd: %s: %s\n", line->arg, strerror(errno));
		put_return(1, env);
		free(str);
		return ;
	}
	change_oldpwd(env, str);
	free(str);
	cd_exit(env, pip_flag);
}
