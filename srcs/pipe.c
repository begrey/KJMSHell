#include "minishell.h"
// car > | -> wc -> | -> wc -> NULL 
void dup_pipe(t_line *list, int pipefd[2], int flags, t_line *list) 
{
        pid_t cpid = fork();
        if (cpid > 0)
                return;
        else if (cpid < 0)
                perror("fork");
        if (flags & STDIN_PIPE) //read pipe인 경우
                if (dup2(pipefd[READ], STDIN_FILENO) < 0)
                        perror("dup2");

        if (flags & STDOUT_PIPE)
                if (dup2(pipefd[WRITE], STDOUT_FILENO) < 0)
                        perror("dup2");

        close(pipefd[READ]);
        close(pipefd[WRITE]);

        // char *const argv[] = {command, NULL};
        // char *const envp[] = {NULL};
        // execve(command, argv, envp);
        ft_redirection(&list);
}

void pipe_exec(t_pipe *pip, t_line **list) //list는 파이프 기준으로 split된 배열 리스트들
{
        t_pipe *pip_temp;
        t_line *lst_temp;
        int     temp_pipefd[2];
        int     i;

        i = 0;
        pip_temp = pip;
        while (pip_temp != NULL)
        {
                pipe(pip_temp->fd);
                pip_temp = pip_temp->next;
        }
        pip_temp = pip;
        dup_pipe(list[i++], pip_temp->fd, STDOUT_PIPE);   //start;
        close(pip_temp->fd[WRITE]);
        while (pip_temp->next != NULL) //pipe가 2개면 이 반복문을 돌지 않는다!
        {       //이전 실행부의 출력을 pipe_read로 받아오고, 
                temp_pipefd[0] = pip_temp->fd[READ];
                //자신의 출력을 다음 pipe_write로 보낸다 
                temp_pipefd[1] = pip_temp->next->fd[WRITE];
                dup_pipe(list[i++], temp_pipefd, STDIN_PIPE | STDOUT_PIPE); // 중앙부 실행
                close(pip_temp->fd[READ]);
                pip_temp = pip_temp->next;
                close(pip_temp->fd[WRITE]);
        }
        dup_pipe(list[i], pip_temp->fd, STDIN_PIPE);   //last;
        close(pip_temp->fd[READ]);
        int status;
        while (wait(&status) > 0);
}


void    split_by_pipe(t_line *list) { // pwd -> | -> ls -> | -> cat -> | -> pwd
        t_line *temp;
        t_line *iter;
        t_pipe *pipe;
        int     pip;
        int     index;
        int     i;
        t_line **arg_list; // 리스트 채워넣는 부분 따로 함수로 빼두기

        pip = 0;
        index = 0;
        i = 0;
        //파이프 개수 세서 그만큼 파이프 생성.
        temp = line;
        while (temp != NULL)
        {
                if (temp->arg[0] == '|')
                        pip++;
                temp = temp->next;
        }
        temp = list;
        iter = list;
        arg_list = (t_line **)malloc(sizeof(t_line *) * (pip + 2));
        while (temp != NULL)
	{
		i = ft_split_list_token(temp, '|');
		temp = ft_list_null_term(temp, i);
		ptr_list[index] = iter;
		index++;
		iter = temp;
	}
        ptr_list[index] = NULL;
        //pipe_list 생성
        while (pip != 0)
        {
                ft_pipeadd_back(&pipe, ft_pipenew(fd));
                pip--;
        }
        if (pip == 0)
                ft_redirection(&list);
        else
                pipe_exec(pipe, ptr_list);
}
