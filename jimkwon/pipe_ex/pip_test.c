#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1

void exec_pipe(int pipe1[2], int pipe2[2], char *command, char**arg)
{
	pid_t pid;

	if ((pid = fork()) < 0)
	{
            printf("fork error\n");
            exit(1);
    }

	if (pid > 0)
	{ //parent process
		wait(&status);
    }
	else
	{  //child process 명령어 실행부 호출 
		dup2(fd[WRITE], 1);
		close(fd[READ]);
		close(fd[WRITE]);
		execve(command, argv2, 0);
	}
}

int main()
{
	int fd[2], fd2[2];
    pid_t pid, pid2;
    char buf[MAX_BUF];
	char result[MAX_BUF];
	int status;
	char *argv[] = {"ls", (char*)0};
	char *argv2[] = {"pwd", (char*)0};
	char *argv3[] = {"wc", (char*)0};
	if(pipe(fd) < 0)
	{
        printf("pipe error\n");
        exit(1);
    }
    if((pid = fork()) < 0)
	{
            printf("fork error\n");
            exit(1);
    }
    if(pid>0)
	{ //parent process
		wait(&status);
		dup2(fd[READ], 0);
        close(fd[WRITE]);
        close(fd[READ]);
		execve("/usr/bin/sort", argv3, 0);
    }
	else
	{  //child process 명령어 실행부 호출 
		dup2(fd[WRITE], 1);
		close(fd[READ]);
		close(fd[WRITE]);
		execve("/bin/ls", argv2, 0);
	}
	if(pipe(fd2) < 0)
	{
        printf("pipe error\n");
        exit(1);
    }
	if((pid2 = fork()) < 0)
	{
            printf("fork error\n");
            exit(1);
    }
    if(pid2>0)
	{ //parent process
		wait(&status);
		dup2(fd[READ], 0);
        close(fd[WRITE]);
        close(fd[READ]);
		execve("/usr/bin/sort", argv3, 0);
    }
	else
	{  //child process 명령어 실행부 호출 
		dup2(fd[WRITE], 1);
		close(fd[READ]);
		close(fd[WRITE]);
		execve("/bin/ls", argv2, 0);
	}
}