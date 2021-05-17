#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int		temp;

int		ft_strlen(char *s);

void	ft_printf(char *s)
{
	printf("%s\n", s);
}


void	dupdup(int argc, char *argv[])
{
	int		fd1;
	int		fd2;
	int		*fd;
	int		status;
	int		ret;

	fd = (int *)malloc(sizeof(int) * 2);
	//"abcd" -->  fd[1] ------>>> fd[0]  -> 1.txt
	//
	dup2(fd[1], 1);
	dup2(fd1, fd[0]);


	status = pipe(fd);
	fd1 = open("./1.txt", O_RDWR | O_CREAT, 00777);

	printf("2temp %d\n", temp);
	ret = dup2(1, temp);
	printf("ret %d\n", ret);
	close(1);
	dup2(temp, STDOUT_FILENO);
	printf("3temp %d\n", temp);
	dup2(fd1, 1);
	close(1);
	if (argc >= 2)
		write(1, argv[1], ft_strlen(argv[1]));
	if (argc >= 3)
		write(fd1, argv[2], ft_strlen(argv[2]));

}

int		main(int argc, char *argv[], char *envp[])
{
	printf("1zz\n");
	dupdup(argc, argv);
	printf("4 1234\n");
	ft_printf("5 asdf\n");
	dup2(temp, 1);
	printf("temp = %d\n", temp);
	printf("6 one lae dae ro\n");
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
