#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		main(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	buffer[30];
	pid_t	pid;
	int		state;

	state = pipe(fd);
	if (state == -1)
	{
		printf("pipe() error\n");
		return (1);
	}

	pid = fork();

	if (pid == -1)
	{
		printf("fork error\n");
		return (1);
	}
	else if (pid == 0)
	{
		write(fd[1], "good\n", 5);
	}
	else
	{
		read(fd[0], buffer, 30);
		printf("%s\n", buffer);
	}
	printf("fd[1] : %s\n", buffer);
	return (0);
}

// 위 함수에서
// 자식프로세스 에서 fd[1]에 write를 하면
// 부모프로세스에서 fd[0]를 read해서 buffer에 저장

// 파이프 자체는 fork 함수에 의해 복사되지 않는다
// 파이프는 방향성이 존재하지 않는다
//
