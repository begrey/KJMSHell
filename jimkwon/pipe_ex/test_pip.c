#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define STDIN_PIPE 0x1
#define STDOUT_PIPE 0x2
#define READ 0
#define WRITE 1

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


int main() {
        int pipefd1[2], pipefd2[2];
        pipe(pipefd1);
        pipe(pipefd2);

        exec_command("/bin/pwd", pipefd1, STDOUT_PIPE);
        close(pipefd1[WRITE]);
        exec_command("/usr/bin/wc", pipefd2, STDIN_PIPE);
        close(pipefd2[READ]);

        int temp_pipefd[] = {pipefd1[READ], pipefd2[WRITE]};
        exec_command("/bin/ls", temp_pipefd, STDIN_PIPE | STDOUT_PIPE);
        //printf("%d %d %d\n", STDOUT_PIPE, STDIN_PIPE, STDIN_PIPE | STDOUT_PIPE);
        close(pipefd1[READ]);
        close(pipefd2[WRITE]);

        int wstatus;
        while (wait(&wstatus) > 0);
		printf("$$%d\n", STDIN_PIPE | STDOUT_PIPE);
        return 0;
}