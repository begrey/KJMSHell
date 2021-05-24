#include "minishell.h"


// (*command_line)->arg
// (*command_line)->next->arg

void	exec_export(t_line **command_line)
{
	int		len;
	int		i;
	char	*str;
	t_env	*temp;
	t_env	*idx;
	t_line	*ttemp;

	i = 0;
	ttemp = *command_line;
	while((ttemp))
	{
		ttemp = ttemp->next;
		i++;
	}
	len = i;
	i = 0;

	str = ft_strdup("");

	if ((*command_line)->next == NULL)		// export 단독일 때 환경변수 출력
	{
		idx = env;		// 임시 변수를 사용하지 않으면 한번밖에 사용할 수 없음
		while (idx)
		{
			str = str_append1(str, "declare -x ");
			str = str_append1(str, idx->key);
			if (idx->value)
			{
				str = str_append1(str, "=");
				str = str_append1(str, "\"");
				str = str_append1(str, idx->value);
				str = str_append1(str, "\"");
			}
			str = str_append1(str, "\n");
			idx = idx->next; 
		}
		printf("%s", str);
	}
	else		// 환경변수를 추가할 때
	{

		temp = (t_env *)malloc(sizeof(t_env) * (len));
		*command_line = (*command_line)->next;
		while ((*command_line))
		{
			if (is_alpha((*command_line)->arg[0]) || is_dollar((*command_line)->arg[0]))
			{
				if (ft_envfind(&env, extract_env(find_key((*command_line)->arg))))
					temp = ft_envfind(&env, extract_env(find_key((*command_line)->arg)));
				else
				{
					(*temp).key = extract_env(find_key((*command_line)->arg));
					ft_envadd_back(&env, temp);
				}
				if (ft_strchr((*command_line)->arg, '='))
				{
					(*temp).value = extract_env(find_value((*command_line)->arg));
				}
			}
			else		// 변수명이 숫자나 특수문자로 시작하면 안됨
			{
				str = str_append1(str, "export: ");
				str = str_append2(str, &(*command_line)->arg[0]);
				str = str_append1(str, ": not a valid identifier\n");
			}
			(*command_line) = (*command_line)->next;
		}
	}
//	return (str);
}

void		exec_env(t_line **command_line)
{
	t_env	*idx;
	char	*str;
	int		len;
	int		i;
	t_line	*ttemp;

	i = 0;
	ttemp = *command_line;
	while((ttemp))
	{
		ttemp = ttemp->next;
		i++;
	}
	len = i;
	i = 0;

	if (len > 1)
	{
		str = ft_strdup("env: No such file or directory\n");
		printf("%s", str);
	}
	str = ft_strdup("");
	if ((*command_line)->next == NULL)
	{
		idx = env;
		while (idx)
		{
			if (idx->value)
			{
				str = str_append1(str, idx->key);
				str = str_append1(str, "=");
				str = str_append1(str, idx->value);
				str = str_append1(str, "\n");
			}
			idx = idx->next; 
		}
	}
	printf("%s", str);
}

void	exec_unset(t_line **command_line)
{
	t_env	*now;
	t_env	*begin;
	int		i;
	int		len;
	t_line	*ttemp;

	i = 0;
	ttemp = *command_line;
	while((ttemp))
	{
		ttemp = ttemp->next;
		i++;
	}
	len = i;
	i = 0;

	i = 1;
	while (i < len)
	{
		now = begin;
		begin = env;
		while (begin)
		{
			if (ft_strcmp(begin->key, find_key((*command_line)->next->arg)) == 0)
			{
				if (now->next)
					now->next = begin->next;
			}
			now = begin;
			begin = begin->next;
		}
		i++;
		(*command_line) = (*command_line)->next;
	}
	command_line = NULL;
	len = 0;
}

char	*extract_env(char *str)
{
	char	*s;
	char	*ret;
	t_env	*ex;

	if (*str != '$')
		return (str);
	else if (is_dollar(str[0]) && !str[1])
	{
		return (str);
	}
	s = str + 1;
	ex = ft_envfind(&env, s);
	ret = ex->value;
	if (!ret)
		ret = ft_strdup("");
	return (ret);
}


