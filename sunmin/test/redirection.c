#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int		ft_strlen(char *s);

int		main(int argc, char *argv[], char *envp[])
{
	pid_t	pid1;
	int		*status;
	int		fd1;

	pid1 = fork();
	if (pid1 == -1)
	{
		printf("fork error\n");
		exit(0);
	}

	if (pid1)			// 부모 프로세스
	{
		if (argc >= 4)
		{
			fd1 = open (argv[3], O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 00777);
			dup2(fd1, 1);
		}
		waitpid(pid1, status, 0);		// 자식 프로세스가 종료될때까지 대기
		printf("--------------------------\n");
		printf("%d : I'm your father, waiting for you \n", pid1);
		if (argc >= 3)
		{
			printf("argv[2] : %s\n", argv[2]);
			write(1, argv[2], ft_strlen(argv[2]));
			write(1, "\n", 1);
		}
	}
	else				// 자식 프로세스
	{
		printf("%d : I'm your son\n", pid1);
		if (argc >= 2)
		{
			printf("argv[1] : %s\n", argv[1]);
			write(1, argv[1], ft_strlen(argv[1]));
			write(1, "\n", 1);
		}
	}
	return (0);
}

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
