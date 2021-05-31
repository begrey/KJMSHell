#include "minishell.h"

int		is_token(char *s)
{
	if (*s == ';' || *s == '|' || (*s == '>' && *(s + 1) != '>') || *s == '<')
		return (1);
	else if (*s == '>' && *(s + 1) == '>')
		return (2);
	return (0);
}

int		is_token_quote(const char *str)
{
	char		*s;
	char		flag;
	int			ret;

	ret = 0;
	flag = 0;
	s = (char *)str;

	if (*s && !is_token(s))
		ret = 1;
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (is_token(s) == 1)
				ret++;
			else if (is_token(s) == 2)
			{
				ret++;
				s++;
			}
			if (is_token(s) && !is_token(s + 1) && *(s + 1))
				ret++;
		}
		s++;
	}
	return (ret);
}

int		where_token(char *str)
{
	char		*s;
	char		flag;
	int			ret;
	int			i;

	i = 0;
	s = (char *)str;
	ret = 0;
	flag = 0;
	while (s[i])
	{
		flag = flag_check(s[i], flag);
		if (!flag)
		{
			if (is_token(&(s[i])))
				return (i);
		}
		i++;
	}
	return (i);
}

char	**ft_token_split(char *arg)
{
	char	*s;
	char	**split_token;
//	int		next_split;
	int		split_num;
	int		word_num;
	int		i;
	int		j;

	s = (char *)arg;
	split_num = is_token_quote(arg);

	split_token = (char **)malloc(sizeof(char *) * (split_num + 1));
	split_token[split_num] = NULL;



	i = 0;
//	next_split = where_token(s);
	while (i < split_num)
	{
		if (is_token(s) == 1)
		{
			split_token[i] = (char *)malloc(sizeof(char) * (2));
			split_token[i][0] = *s;
			split_token[i][1] = '\0';
			s++;
		}
		else if (is_token(s) == 2)
		{
			split_token[i] = (char *)malloc(sizeof(char) * (3));
			split_token[i][0] = '>';
			split_token[i][1] = '>';
			split_token[i][2] = '\0';
			s += 2;
		}
		else
		{
			j = 0;
			word_num = where_token(s);
			split_token[i] = (char *)malloc(sizeof(char) * (word_num + 1));
			split_token[i][word_num] = '\0';
			while (j < word_num)
			{
				split_token[i][j] = *s;
				j++;
				s++;
			}
		}
//		next_split = where_token(s + next_split + 1);
		i++;
	}
	return (split_token);
}

void	list_split_addback(t_line **lst, char *arg)
{

	int		i;
	char	**split_token;

	i = 0;
	split_token = ft_token_split(arg);
	
	while (split_token[i])
	{
		ft_listadd_back(lst, ft_listnew(ft_strdup(split_token[i])));
		i++;
	}
	free_split(split_token);
}

int		check_single_escape(const char *s)
{

	char *temp;

	temp = (char *)s;
	while (*temp)
	{

		if (*temp == '\\')
		{
			temp++;
			if (*temp == '\0')
				return (-1);
		}
		temp++;
	}
	return (0);
}

int		ft_strerror(char *s)
{
	char *temp;

	temp = s;
	printf("%s", temp);
	return (-1);
}

int		make_list(t_env *env)
{

	t_line	*line;
	char	**split_line;
	char	*escape_line;
	int i;
	char	*temp;
	char	*s_line;

	line = NULL;

	s_line = ft_strdup(g_line);
	escape_line = convert_escape(s_line);
	free(s_line);

	escape_line[ft_strlen(escape_line) - 1] = '\0';



	if (check_single_escape(escape_line) == -1)
		return (ft_strerror("syntax error\n"));

	if (!(split_line = ft_split_quote(escape_line)))
		return (ft_strerror("syntax error\n"));









	int k  = 0;
	while (split_line[k])
	{
		temp = split_line[k];
		split_line[k] = ft_strtrim(split_line[k], " ");
		free(temp);
		k++;
	}






	i = 0;
	while (split_line[i])
	{
		temp = split_line[i];
		split_line[i] = convert_env(split_line[i], env);		// 누수 x
		free(temp);
		i++;
	}



	


	i = 0;
	while (split_line[i])							// 누수 발생 ... 
	{
		if ((is_token_quote(split_line[i])))
		{
			list_split_addback(&line, split_line[i]);
		}
		else
		{
			ft_listadd_back(&line, ft_listnew(split_line[i]));
		}
		i++;
	}

	free_split(split_line);


	if ((redir_syn_check(line)) == -1)
		return (-1);


	if ((token_syn_check(line)) == -1)
		return (-1);

	i = split_by_semi(line, env);

	return (i);
}
