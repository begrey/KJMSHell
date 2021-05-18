#include "minishell.h"
#define STDIN_PIPE 0x1
#define STDOUT_PIPE 0x2
#define READ 0
#define WRITE 1
// car > | -> wc -> | -> wc -> NULL 
void exec_command(char *command, int pipefd[2], int flags) {
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

        char *const argv[] = {command, NULL};
        char *const envp[] = {NULL};
        execve(command, argv, envp);
        perror("execv");
}

void pipe_exec(t_pipe *pip, t_line *list)
{
        t_pipe *pip_temp;
        t_line *lst_temp;
        int     temp_pipefd[2];

        pip_temp = pip;
        while (pip_temp != NULL)
        {
                pipe(pip_temp->fd);
                pip_temp = pip_temp->next;
        }

        pip_temp = pip;
        //lst_temp = list;
        //i = ft_split_list_token(temp, '|');
        //temp = ft_list_null_term(temp, i);
	//여기서 echo -> aa 와 같은 리스트를 argv 형태의 2차원 배열로 만들어서 exec_command로 보내보자
	
        exec_command("/bin/cat", pip_temp->fd, STDOUT_PIPE);   //start;
        close(pip_temp->fd[WRITE]);
        //iter = temp;
        while (pip_temp->next != NULL) //pipe가 2개면 이 반복문을 돌지 않는다!
        {       //이전 실행부의 출력을 pipe_read로 받아오고, 
                temp_pipefd[0] = pip_temp->fd[READ];
                //자신의 출력을 다음 pipe_write로 보낸다 
                temp_pipefd[1] = pip_temp->next->fd[WRITE];
                exec_command("/bin/cat", temp_pipefd, STDIN_PIPE | STDOUT_PIPE); // 중앙부 실행
                close(pip_temp->fd[READ]);
                pip_temp = pip_temp->next;
                close(pip_temp->fd[WRITE]);
        }
        exec_command("/bin/ls", pip_temp->fd, STDIN_PIPE);   //last;
        close(pip_temp->fd[READ]);
        int status;
        while (wait(&status) > 0);
}


int main() { // pwd -> | -> ls -> | -> cat -> | -> pwd
        t_line *list;
        t_pipe *pipe;
        int     pip;
        int     fd[2];

	list = NULL;
        pipe = NULL;
        pip = 0;
	ft_listadd_back(&list, ft_listnew("cat"));
	ft_listadd_back(&list, ft_listnew("|"));
	ft_listadd_back(&list, ft_listnew("wc"));
	ft_listadd_back(&list, ft_listnew("|"));
	ft_listadd_back(&list, ft_listnew("wc"));
        //파이프 개수 세서 그만큼 파이프 생성.
        while (list != NULL)
        {
                if (list->arg[0] == '|')
                        pip++;
                list = list->next;
        }
        //pipe_list 생성하기
        pip = 4;
        while (pip != 0)
        {
                ft_pipeadd_back(&pipe, ft_pipenew(fd));
                pip--;
        }
        //pipe 함수로 보내자
        pipe_exec(pipe, list);
        //pipe_list 순회하면서 중간 command들 연결해주기

        //command 의 경우 iter 하나씩 2차원 배열을 만들어서 argv에 넣어버리기
        
}