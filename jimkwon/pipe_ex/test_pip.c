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


int main() { // cat  |  wc  |   wc
        int pipefd1[2];
        int pipefd2[2];
        //int pipefd3[2];
        pipe(pipefd1);
        pipe(pipefd2);
        //pipe(pipefd3);

        exec_command("/bin/ls", pipefd1, STDOUT_PIPE); //처음
        close(pipefd1[WRITE]);


        // int temp_pipefd[] = {pipefd1[READ], pipefd2[WRITE]};
        // exec_command("/bin/ls", temp_pipefd, STDIN_PIPE | STDOUT_PIPE); //중간
        // close(pipefd1[READ]);
        // close(pipefd2[WRITE]);

        exec_command("/usr/bin/grep", pipefd1, STDIN_PIPE); //마지막
        close(pipefd1[READ]);

        // temp_pipefd[0] = pipefd2[READ];
        // temp_pipefd[1] = pipefd3[WRITE];
        // exec_command("/usr/bin/wc", temp_pipefd, STDIN_PIPE | STDOUT_PIPE); //중간 2
        // close(pipefd2[READ]);
        // close(pipefd3[WRITE]);
        int status;
        while (wait(&status) > 0);

        return 0;
        
}