/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 13:20:32 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/02 18:54:31 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*exec_export(char **command_line, int len)
{
	int		i;
	char	*str;
	t_env	*temp;
	t_env	*idx;

	str = ft_strdup("");
	if (command_line[1] == NULL)		// export 단독일 때 환경변수 전체 출력
	{
		idx = env;		// 임시 변수를 사용하지 않으면 한번밖에 사용할 수 없음
		while (idx)
		{
			str = ft_strjoin(str, idx->key);		// 메모리 릭 체크해야
//			if (idx->if_value)
//			{
				str = ft_strjoin(str, "=");
				str = ft_strjoin(str, "\"");
				str = ft_strjoin(str, idx->value);
				str = ft_strjoin(str, "\"");
//			}
			str = ft_strjoin(str, "\n");
			idx = idx->next; 
		}
	}
	else								// export 뒤에 설정 값이 있을 때
	{
		temp = (t_env *)malloc(sizeof(t_env) * (len - 1));
		i = 1;
		while (command_line[i])
		{
			if (command_line[i][0] >= '0' && command_line[i][0] <= '9')		// 변수명이 숫자로 시작하면 안됨
			{
				str = ft_strjoin(str, "export: ");
				str = ft_strjoin(str, &command_line[i][0]);
				str = ft_strjoin(str, ": not a valid identifier\n");
			}
			else
			{
				(*temp).key = find_key(command_line[i]);
				(*temp).value = find_value(command_line[i]);
				ft_listadd_back(&env, temp);
			}
			i++;
			temp++;
		}
	}
	return (str);
}


char	*exec_env(int len)		// 환경 변수 중 value가 있는 것만 출력
{
	t_env	*temp;
	char	*str;

	if (len > 1)
	{
		str = ft_strdup("env: No such file or directory\n");
		return (str);
	}
	temp = env;
	str = ft_strdup("");
	while (temp->next)
	{
		if (temp->key)
		{
			str = ft_strjoin(str, temp->key);		// 메모리 릭 체크해야
			str = ft_strjoin(str, "=");
			str = ft_strjoin(str, temp->value);
			str = ft_strjoin(str, "\n");
		}
		temp = temp->next;
	}
	return (str);
}

char	*exec_unset(void)
{

	// 찾아서 해당리스트를 지우기
	return (NULL);
}
