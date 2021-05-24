#include "minishell.h"

void signalHandler(int sig){
        if(sig==SIGINT){ //ctrl-c
                printf("signal SIGINT : %d\n", sig);
                //sleep(3000); //mac 에서는 sleep
                exit(0);
        }
        if(sig==SIGQUIT){ //ctrl-'\'
			if (ft_strcmp(g_line, "") != 0)
                printf("^\\Quit: %d\n", sig);
				//exit(0);
        }
}

int main(int argc, char **argv, char **envp)
{
	int		read;
	t_list	*history;
	t_line	*list;

	list = NULL;
	history = NULL;
	if (!(g_line = malloc(1)))
		return (-1);
	(g_line)[0] = 0;
	if (argc != 1)											// 쉘에서 bash aa 이런 식으로 배쉬를 실행할 때
	{
		write(1, "cannot excute binary file\n", 26);
		return (0);
	}
	init_env(envp);
	write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
	signal(SIGQUIT, signalHandler);
	signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
	while((read = parse_line(history)) > 0)						// 방향키(왼, 위, 오, 아) 들어올 때 처리해야 함
	{
		//히스토리 리스트 추가
		ft_lstadd_back(&history, ft_lstnew(g_line));
		if ((make_list(list, g_line)) == -1)
			printf("syntax error!\n"); //syntax 에러 처리부분
		//printf("status : %d\n", status);
		if (status == 10)
		{
			printf("exit\n");
			exit(0);
		}
		write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
		(g_line)[0] = 0;
	}
	printf("exit\n");
	return (0);
	argv = NULL;
}
