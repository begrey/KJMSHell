#include "minishell.h"

void sigint_cursor()
{
	t_cursor cursor;
	tgetent(NULL, "xterm");

	cursor.cm = tgetstr("cm", NULL); //cursor motion
	cursor.ce = tgetstr("ce", NULL); //clear line from cursor
	get_cursor_position(&cursor);
	delete_line(&cursor);
}

void signalHandler(int sig){
    if(sig==SIGINT){ //ctrl-c
/*			if (ft_strchr(g_line, '\n') != NULL)
			{
				g_line[0] = -1;
				printf("\n");
			}
			else
			{
				if (g_line[0] != 0)
				{
					free(g_line);
					g_line = ft_strdup("");
				}
				g_line[0] = -3;
				write(1, "\nKJMSHell(｡☌ᴗ☌｡) >> ", 30);
			} */
		exit(0);
    }	
    if(sig==SIGQUIT){ //ctrl-'\'
		if (ft_strchr(g_line, '\n') != NULL)
		{
			g_line[0] = -2; 
            printf("Quit: %d\n", sig);
		}
    }
}

void	iter_history(t_list *history)
{
	while (history != NULL)
	{
		printf("history: %s -> ", history->content);
		history = history->next;
	}
	printf("\n");
}

void	set_signal_return(t_env *env)
{
	if (g_line[0] == -1) // 명령어 실행 중  ctrl-c
		put_return(130, env);
	else if (g_line[0] == -2) // 명령어 실행 중 ctrl-'\'
		put_return(131, env);
}

int main(int argc, char **argv, char **envp)
{
	t_list	*history;
	t_env	*env;
	int		read;
	char	*list;
	int		i;

	i = -1;
	env = NULL;
	list = NULL;
	history = NULL;
	if (!(g_line = malloc(1)))
		return (-1);
	(g_line)[0] = 0;
	if (argc != 1)											// 쉘에서 bash aa 이런 식으로 배쉬를 실행할 때
	{
		write(1, "cannot excute binary file\n", 26);
		return (126);
	}
	env = init_env(envp, env);
	signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    signal(SIGQUIT, signalHandler);
	write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
	int j = 0;
	while((read = parse_line(history, env)) > 0)						// 방향키(왼, 위, 오, 아) 들어올 때 처리해야 함
	{
		//히스토리 리스트 추가
		list = ft_strdup(g_line);
		list[ft_strlen(list) - 1] = '\0';
		ft_lstadd_back(&history, ft_lstnew(list));
		i = make_list(env);
			while(1)
		;
		
		//	break;
		write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
		set_signal_return(env);
		free(g_line);
		if (!(g_line = malloc(1)))
			return (-1);
		(g_line)[0] = 0;
		j++;
		if (j == 4)
			break;
		
		//free(list);
	}
	printf("exit\n");
	return (return_return(env)); //i
	argv = NULL;
}
