#include "minishell.h"

void signalHandler(int sig){
        if(sig==SIGINT){ //ctrl-c
                printf("signal SIGINT : %d\n", sig);
                //sleep(3000); //mac 에서는 sleep
                exit(0);
        }
        if(sig==SIGQUIT){ //ctrl-'\'
                printf("signal SIGQUIT : %d\n", sig);
				exit(0);
        }
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	int		read;
	t_list	*history;
	t_line	*list;

	list = NULL;
	history = NULL;
	if (argc != 1)											// 쉘에서 bash aa 이런 식으로 배쉬를 실행할 때
	{
		write(1, "cannot excute binary file\n", 26);
		return (0);
	}
	init_env(envp);
	signal(SIGINT, signalHandler);
    signal(SIGTSTP, signalHandler);
    signal(SIGQUIT, signalHandler);
	write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
	while((read = parse_line(&line, history)) > 0)						// 방향키(왼, 위, 오, 아) 들어올 때 처리해야 함
	{
		//히스토리 리스트 추가
		ft_lstadd_back(&history, ft_lstnew(line));
		if ((make_list(list, line)) == -1)
			printf("syntax error!\n"); //syntax 에러 처리부분
		write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
	}
	return (0);
	argv = NULL;
}
