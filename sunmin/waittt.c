#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int		main(int argc, char **argv, char **envp)
{
	pid_t		pid1;
	pid_t		pid2;
	int			*status;

	fork();
	printf("pid1 %d\n", pid1);
	pid2 = wait(status);
	printf("pid2 %d\n", pid2);
	return (0);
}
