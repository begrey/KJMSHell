#include "minishell.h"

char	**set_stream(char *stream_line)
{
	return 0;
}

char	*set_body(char *stream_line)
{
	return 0;
}

void	set_redirection(t_line **line, char *redir_line)	//echo >aa >bb hi
{
	char	**stream_temp;
	char	*redir_temp;

	stream_temp = set_stream(redir_line);
	redir_temp = set_body(redir_line);

//	(*line)->stream = stream_temp;
//	(*line)->arg = redir_temp;

	return ;
	line = 0;
	redir_line = 0;
}

void	go_redir(char *redir_stream)
{
	dup2(1, fd_temp);
	fd1 = 1;
	if (redir_stream)
		fd1 = open(redir_stream, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 00777);
	dup2(fd1, 1);
}
