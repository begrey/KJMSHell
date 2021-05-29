#include "minishell.h"

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

void	ft_exit(t_line *line, t_env *env, int pip_flag)
{
	int	status; //$?

	status = 0;
	if (pip_flag == 0)
		return;
	if (line == NULL) //exit만 들어온 경우
		exit(return_return(env));
	else
	{
		if (is_num(line->arg) == -1) //255 문자 포함될때
		{
			printf("exit: %s: numeric argument required\n", line->arg);
			exit(255);
		}
		else 
		{//int 범위값 넘어갈때는 255
			if (line->next != NULL) //exit 뒤에 여러 인자
			{
				printf("exit: too many arguments\n");
				put_return(1, env);
				return ;
			}
			else if ((ft_strlen(line->arg) > 2) && (ft_atoi(line->arg) == -1 || ft_atoi(line->arg) == 0))
			{
				printf("exit: %s numeric argument required\n", line->arg);
				status = 255;
			}
			else //256 나머지나누기
				status = ft_atoi(line->arg) % 256;
			exit(status); //나머지 종료
		} 
	}
}