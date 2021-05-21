#include "minishell.h"

char		*root_path()
{
	//환경변수 USER에서 받아옴
	return(ft_strdup(convert_env("$USER")));
}

char		*convert_root_path(t_line *line)
{
	//  ~/42Curses의 경우 /USER/jimkwon으로 치환
	return (ft_strjoin(root_path(), line->arg + 1));
}

void		ft_cd(t_line *line)
{
	int		check;
	char	buf[1024];
	char 	*path;


	//path 정해주기
	if (line == NULL) // cd 만 입력한 경우
		path = root_path();
	else if (line->arg[0] == '~') // 루트 디렉토리
		path = convert_root_path(line->arg);
	else
		path = line->arg;	
	check = chdir(path);
	//ft_pwd();
	if (check != 0)
		printf("cd: no such file or directory: %s\n", line->arg);
}

// int main()
// {
// 	// ~/거나 cd 와 같은 경우 루트는 /Users/$USER 여야함 
// 	t_line *list;

// 	list = NULL;
// 	//ft_listadd_back(&list, ft_listnew("../"));
// 	ft_listadd_back(&list, ft_listnew("~/"));
// 	//ft_listadd_back(&list, ft_listnew("/"));
// 	ft_cd(list);
// 	return 0;
// }