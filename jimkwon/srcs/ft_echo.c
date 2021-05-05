/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 09:28:27 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/03 23:29:52 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*append_char(char *line, char c)
{
	char *str; //이어붙힌 문자열
	int i;

	i = 0;
	if(!(str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
			return NULL;
	while(line[i] != '\0')
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

int			append_syntax(char *arg, char **line, int i)
{
	int escape;

	escape = 0;
	if (arg[i] == 34 || arg[i] == 39)
	{
		i++;
		if (ft_strchr(arg + i, arg[i]) == NULL)
			return (-1);
		while (arg[i] != '\0' && arg[i] != 34 && arg[i] != 39)
		{
			if (arg[i] == '$')
			{
				i = find_env(arg, *line, i); //다시 구현해야함
			}
			else if(arg[i] == 92 && escape == 0 && arg[i] != 39)
			{
				escape = 1;
				if (arg[i + 1] == 34)
					i++;
				i++;
			}
			else
			{
				*line = append_char(*line, arg[i]);
				i++;
			}
		}
	}
	else
	{
		while (arg[i] != '\0' && arg[i] != 96)
		{
			*line = append_char(*line, arg[i]);
			i++;
		}
	}
	if (arg[i] != '\0')
		i++;
	return (i);
}

char		*append_args(char *arg, char *line)
{
	int		i;
	int		escape;

	i = 0;
	escape = 0;
	while (arg[i] == ' ')//""문이 아니면 다중공백이 허용되지 않는다.
		i++;
	while (arg[i] != '\0')
	{
		if ((arg[i] == 34 || arg[i] == 39 || arg[i] == 96) && escape != 1)
			i = append_syntax(arg, &line, i);
		else if (arg[i] == 92 && escape == 0)
		{
			escape = 1;
			i++;
		}
		else
		{
			if (arg[i] == ' ' && arg[i + 1] != '\0')
			{
				line = append_char(line, ' ');
				while (arg[i] == ' ')//""문이 아니면 다중공백이 허용되지 않는다.
					i++;
			}
			line = append_char(line, arg[i]);
			escape = 0;
			i++;
		}
		if (i == -1)
		{
			free(line);
			line = ft_strdup("syntax Error!\n");
			return (line);
		}
	}
	line = append_char(line, '\n');
	return (line);
}

char		*ft_echo(char *args)
{
	char	*echo_content;
	char	*line;

	if (!(line = malloc(1)))
		return NULL;
	(line)[0] = 0;
	echo_content = append_args(args, line);
	return (echo_content);
}
