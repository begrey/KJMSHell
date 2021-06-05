/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:07:59 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/05 15:14:22 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_num(char *line)
{
	while (*line != '\0')
	{
		if (!(*line >= '0' && *line <= '9'))
			return (-1);
		line++;
	}
	return (0);
}

void	exit_with_num(t_line *line, t_env *env)
{
	int	status;

	status = 0;
	if (line->next != NULL)
	{
		printf("exit\nexit: too many arguments\n");
		put_return(1, env);
		return ;
	}
	else if ((ft_strlen(line->arg) > 2) &&
	(ft_atoi(line->arg) == -1 || ft_atoi(line->arg) == 0))
	{
		printf("exit: %s numeric argument required\n", line->arg);
		status = 255;
	}
	else
		status = ft_atoi(line->arg) % 256;
	exit(status);
}

int		set_return_value(t_line *line, t_env *env)
{
	int	ret;

	if (line)
		ret = ft_atoi(line->arg);
	else
		ret = return_return(env);
	return (ret);
}

void	ft_exit(t_line *line, t_env *env, int pip_flag)
{
	int	status;
	int	return_value;

	return_value = set_return_value(line, env);
	status = 0;
	if (pip_flag == 0)
		exit(return_value);
	if (line == NULL)
	{
		free(g_line);
		exit(return_return(env));
	}
	else
	{
		if (is_num(line->arg) == -1)
		{
			printf("exit\nexit: %s: numeric argument required\n", line->arg);
			exit(255);
		}
		else
		{
			exit_with_num(line, env);
			return ;
		}
	}
}

void	exit_not_directory(char **argv)
{
	if (errno && (argv[0][0] == '.' || argv[0][0] == '/'))
	{
		printf("%s: %s\n", argv[0], strerror(errno));
		exit(126);
	}
}
