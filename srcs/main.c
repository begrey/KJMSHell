#include "minishell.h"

void	split_pipes(char *command_line)
{
	char **pipe_line;
	char *str;
	int i;

	i = 0;
	pipe_line = ft_split(command_line, '|');
	while(pipe_line[i] != NULL)
	{
		str = parse_command(pipe_line[i], str);
		i++;
	}
	if (str)		// 있어야 아무 명령어나 입력했을 때 세그폴트 안 뜸
		write(1, str, ft_strlen(str));
}
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
	//char	*p_line;
	char	**command_line;
	int		i;
	int		read;
	t_list	*history;
	//t_list	*temp;

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
	//printf("%d\n", (int)ft_strlen("(｡☌ᴗ☌｡)"));
	while((read = parse_line(&line, history)) > 0)						// 방향키(왼, 위, 오, 아) 들어올 때 처리해야 함
	{
		//히스토리 리스트 추가
		if (history == NULL)
			history = ft_lstnew(line);
		else
			ft_lstadd_back(&history, ft_lstnew(line));
		i = 0;
		command_line = ft_split(line, ';');
		while(command_line[i] != NULL)
		{
			split_pipes(command_line[i]);
			i++;
		}
		//temp = ft_lstlast(history);  히스토리 출력부분
		//printf("history: %s\n", temp->content);
		write(1, "KJMSHell(｡☌ᴗ☌｡) >> ", 29);
	}
	if (read == 0)
		exit(0);
	else
		write(1, "parseError!\n", 12);
	return (0);
	//printf("%s\n", argv[0]);
	argc = 1;
	argv = NULL;
	envp = NULL;
}

