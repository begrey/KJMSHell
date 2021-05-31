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

int		where_token(char *str)	// is_token_quote와 구조 비슷	// 토큰의 인덱스 반환
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
	int		next_split;
	int		split_num;
	int		word_num;
	int		i;
	int		j;

	s = (char *)arg;
	split_num = is_token_quote(arg);

	split_token = (char **)malloc(sizeof(char *) * (split_num + 1));
	split_token[split_num] = NULL;




	i = 0;
	next_split = where_token(s);
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
		next_split = where_token(s + next_split + 1);
		i++;
	}
	return (split_token);
}

void	list_split_addback(t_line **lst, char *arg)
{

	int		i;
	char	**split_token;		// 토큰 기준으로 스플릿

	i = 0;
	split_token = ft_token_split(arg);
	
	while (split_token[i])
	{
		ft_listadd_back(lst, ft_listnew(split_token[i]));
		i++;
	}
}

int		check_single_escape(char *s)
{
	char *temp;

	temp = s;
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

int		make_list(t_line *line,t_env *env)
{
	char	**split_line;
	char	*escape_line;
	int i;

	escape_line = convert_escape(ft_strdup(g_line));
	escape_line[ft_strlen(escape_line) - 1] = '\0';
	if (check_single_escape(escape_line) == -1)
		return (ft_strerror("syntax error\n"));

	if (!(split_line = ft_split_quote(escape_line)))
		return (ft_strerror("syntax error\n"));





	int k  = 0;
	while (split_line[k])
	{
		split_line[k] = ft_strtrim(split_line[k], " ");
		k++;
	}

	i = 0;
	while (split_line[i])
	{
		split_line[i] = convert_env(split_line[i], env);
		i++;
	}
	i = 0;
	while (split_line[i])
	{
		if (is_token_quote(split_line[i]))
			list_split_addback(&line, split_line[i]);
		else
			ft_listadd_back(&line, ft_listnew(split_line[i]));
		i++;
	}

	if ((redir_syn_check(line)) == -1)		// >>로 바꿔서 다시 만들어야
		return (-1);

	if ((token_syn_check(line)) == -1)
		return (-1);	// 토큰이 처음에 오거나, 연속으로 두개 나오는 경우
	i = split_by_semi(line, env);	// 이 함수 안에서 실행
	return (i);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	char	*input_line;
// //	char *input = "echo hi | everyone ; pwd | grep ; ls";
// 	t_line	*line;
// 	t_line	*down;
// 	int	lvl;

// 	if (argc != 1 || argv[1])
// 	{
// 		write(1, "cannot excute binary file\n", 26);
// 		return (0);
// 	}
// 	init_env(envp);
// 	write(1, "KJMSHell(OoO) >> ", 17);
// 	while ((parse_line(&input_line)) > 0)
// 	{
// 		if (input_line[0] == '$' && input_line[1] == '?')
// 		{
// 			printf("ft_errno %d\n", ft_errno);
// 		}
// 		if ((make_list(&line, input_line)) == -1)
// 		{
// 			;
// 		}
// 		write(1, "KJMSHell(OoO) >> ", 17);
// 		free(line);
// 	}
// 	return (0);
// }
