#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		main(int argc, char *argv[], char *envp[])
{
	char *path;
	char **command_line;
	char *command;
	char *ex1;
	char *ex2;
	int		a;
	
	path = strdup("/bin/lss");

	command_line = (char **)malloc(sizeof(char *) * (4));
	command_line[3] = NULL;

	command_line[0] = strdup("ls");

	command_line[1] = strdup("./1");	//
//	command_line[2] = strdup("");
	a = execve(path, command_line, NULL);
	printf("%d\n", a);
//	printf("command not found\n");

	
	return (0);
}
