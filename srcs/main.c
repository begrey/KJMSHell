#include "minishell.h"

void sigint_cursor()
{
	//int		len;
	t_cursor cursor;
	tgetent(NULL, "xterm");

	cursor.cm = tgetstr("cm", NULL); //cursor motion
	cursor.ce = tgetstr("ce", NULL); //clear line from cursor
	get_cursor_position(&cursor);
	delete_line(&cursor);
}

void signalHandler(int sig){

        if(sig==SIGINT){ //ctrl-c
				if (g_line[0] != 0)
				{
					free(g_line);
					g_line = ft_strdup("");
					sigint_cursor();
				}
				else
					write(1, "\nKJMSHell(｡☌ᴗ☌｡) >> ", 30);

        }
        if(sig==SIGQUIT){ //ctrl-'\'
			if (g_line[0] != 0)
                printf("Quit: %d\n", sig);
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

int main(int argc, char **argv, char **envp)
{
	int		read;
	t_list	*history;
	t_line	*list;
	t_env	*env;
	int		i;

	i = -1;
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
	env = init_env(envp);
	signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    signal(SIGQUIT, signalHandler);
	write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
	while((read = parse_line(history)) > 0)						// 방향키(왼, 위, 오, 아) 들어올 때 처리해야 함
	{
		//히스토리 리스트 추가
		ft_lstadd_back(&history, ft_lstnew(ft_strdup(g_line)));
		if ((i = make_list(list, g_line, env)) == 0)
		;
		//	break;
		write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
		free(g_line);
		if (!(g_line = malloc(1)))
			return (-1);
		(g_line)[0] = 0;
	} //$?
	iter_history(history);
	printf("exit\n");
	return (return_return(env)); //i
	argv = NULL;
}
