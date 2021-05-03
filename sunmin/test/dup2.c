#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int		main(int argc, char *argv[], char *envp[])
{
	int		fd1;
	int		fd2;

	fd1 = open("./1.txt", O_RDWR);

	pid1 = fork();

	if (pid1 != 0)		// 자식만
	{
		execeve("ls");
		dup2();
	}


	return (0);
}
