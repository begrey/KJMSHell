/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:28:27 by jimkwon           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/20 09:48:17 by jimkwon          ###   ########.fr       */
=======
/*   Updated: 2021/05/05 12:05:59 by jimkwon          ###   ########.fr       */
>>>>>>> 6fe510d2a5feb7718579c8040320b7c844ff6abe
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*append_char(char *line, char c)
{
	char *str; //이어붙힌 문자열
	int i;

<<<<<<< HEAD
	i = 1;
	flag = 0;
	//-nnnnn 옵션 플래그 검사kk
	if (line->arg[0] == '-' && line->arg[1] == 'n')
=======
	i = 0;
	if(!(str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
			return NULL;
	while(line[i] != '\0')
>>>>>>> 6fe510d2a5feb7718579c8040320b7c844ff6abe
	{
		str[i] = line[i];
		i++;
	}
	str[i] = c;
	i++;
	str[i] = 0;
	free(line);
	return (str);
}

int			find_env(char *arg, char *line, int i)
{
	char	*env;

	if (!(env = malloc(1)))
		return -1;
	(env)[0] = 0;
	while (arg[i] != ' ' && arg[i] != '\0' && arg[i] != 34 && arg[i] != 96)
	{
		env = append_char(env, arg[i]);
		i++;
	}
	if (env[0] != 0)
		line = ft_strjoin(line, env);
	return (i);
}

char		*make_echo_arg(char	**arg, char *echo_arg)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	while (arg[i] != NULL)
	{
		flag = 0;
		j = 0;
		while (arg[i][j] != '\0')
		{
			if (arg[i][j] == '\'' || arg[i][j] == '\"')
			{
				if (flag == 0)
					flag = arg[i][j];
				else if (flag != 0 && flag == arg[i][j])
					flag = 0;
				else
					echo_arg = append_char(echo_arg, arg[i][j]);
			}
			else
				echo_arg = append_char(echo_arg, arg[i][j]);
			j++;
		}
		if (arg[i + 1] != NULL)
			echo_arg = append_char(echo_arg, ' ');
		i++;
	}
	echo_arg = append_char(echo_arg, '\n');
	return (echo_arg);
}

char		*ft_echo(char *args)
{
	char	*echo_content;
	char	*line;
	char	**arg;

	if (!(line = malloc(1)))
		return NULL;
	(line)[0] = 0;
	arg = ft_split_syn(args, ' '); //일단 여기에서만 사용해봤음!
	echo_content = make_echo_arg(arg, line);
	return (echo_content);
}
