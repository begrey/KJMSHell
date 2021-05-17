#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1
int main()
{
	int fd[2];
    pid_t pid;
    char buf[MAX_BUF];
	char result[MAX_BUF];
	int status;
	char *argv[] = {"ls", (char*)0};
	char *argv2[] = {"pwd", (char*)0};
	char *argv3[] = {"wc", (char*)0};
	// for (int i = 0; i < 3; i ++)
	// {
		if(pipe(fd) < 0){
            printf("pipe error\n");
            exit(1);
    	}
        if((pid=fork())<0){
                printf("fork error\n");
                exit(1);
        }
        if(pid>0)
		{ //parent process
			wait(&status);
			dup2(fd[READ], 0);
            close(fd[WRITE]);
            close(fd[READ]);
			// read(0, buf, MAX_BUF);
			// printf("%s\n", buf);
			
			execve("/usr/bin/wc", argv3, 0);
        }
		else
		{  //child process 명령어 실행부 호출 
			dup2(fd[WRITE], 1);
			close(fd[READ]);
			close(fd[WRITE]);
			// if (i == 0)
            // 	execve("/bin/pwd", argv2, 0);
			// else if (i == 1)
			// 	execve("/bin/ls", argv2, 0);
			// else
				execve("/bin/ls", argv2, 0);
            //write(fd[WRITE],buf,strlen(buf));
			//exit(0);
		}
	//}
}