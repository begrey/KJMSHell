#include "minishell.h"

void make_list(t_line **line, char *s_line, char lvl)
{
	char **split_line;
	int i;

	i = 0;
	split_line = ft_split_syn(s_line, lvl);
	while (split_line[i] != NULL)
	{
		if (!(split_line[i][0] == '<' || split_line[i][0] == '>'))
			ft_listadd_back(&(*line), ft_listnew(split_line[i]));
		i++;
	}
}

void split_arg(t_line **line, char *arg_line) // echo c
{
	t_line *arg_list;

	arg_list = NULL;
	make_list(&arg_list, arg_line, ' ');
	ft_exec(&arg_list);
	(*line)->line = arg_list;
}


void split_pipe(t_line **line, char *pipe_line) // echo >a >b c | pwd
{
	t_line *pipe_list;
	t_line *temp;
	int i;

	i = 0;
	pipe_list = NULL;
	make_list(&pipe_list, pipe_line, '|');
	(*line)->line = pipe_list; 
	temp = pipe_list;
	while(temp != NULL)
	{
		split_arg((&temp), temp->arg);
		temp = temp->next;
		i++;
	}
}

void  split_semi(t_line **line) // echo >a >b >c | pwd ; ls
{
	t_line *semi_list;
	t_line *temp;
	int	i;

	i = 0;
	semi_list = NULL;
	make_list(&semi_list, (*line)->arg, ';');
	(*line)->line = semi_list;
	temp = semi_list;
	while(temp != NULL)
	{
		split_pipe((&temp), temp->arg);
		temp = temp->next;
		i++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char	*input_line;
//	char *input = "echo hi | everyone ; pwd | grep ; ls";
	t_line	*line;
	t_line	*down;
	t_line	*right;
	t_line	*right_;
	t_env	*head = NULL;
	int	lvl;

	if (argc != 1)
	{
		write(1, "cannot excute binary file\n", 26);
		return (0);
	}
	init_env(envp);
	write(1, "KJMSHell(OoO) >> ", 17);		 // 3번째 인자 22로 하면 터집니다..
	while ((parse_line(&input_line)) > 0)
	{
		lvl = 1;
		line = ft_listnew(input_line);
		split_semi(&line);
		down = line;
		write(1, "KJMSHell(OoO) >> ", 17);
		free(line);
	}
	return (0);
}
