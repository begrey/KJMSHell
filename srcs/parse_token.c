/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 01:24:03 by jimkwon           #+#    #+#             */
/*   Updated: 2021/04/30 02:17:25 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_token(char **line, int i)
{
	char token[2];

	token[0] = line[i][0];
	if (ft_strlen(line[i]) > 1 && token[0] == line[i][1]) //같은 토큰이 연속되어 들어오면 최대 2개까지만 인식 나머지는 버림
		token[1] = line[i][1];
	else 
		token[1] = 0;
	//printf("토큰확인%s\n", token);
	if (i == 0 || (ft_strlen(line[i]) > 1 && token[0] != '>')) //토큰이 첫 인자로 들어오는 경우 예외처리
	{
		printf("syntax error near unexpected token \'%s\'\n", token);
		return ;
	}
	if (token[0] == ';')
		printf("다중커맨드 토큰입니다.\n");
	else if (token[0] == '|')
		printf("파이프 토큰입니다.\n");
	else if (token[0] == '<')
		printf("리다이렉션 < 토큰입니다.\n");
	else if (token[0] == '>' && token[1] == 0)
		printf("리다이렉션 > 토큰입니다.\n");
	else
		printf("리다이렉션 >> 토큰입니다.\n");

}