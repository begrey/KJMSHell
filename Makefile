C = clang

NAME		= minishell
LIBFT		= libft.a

SRCS		= ./srcs/convert_env.c \
			  ./srcs/ft_pipeadd_back.c \
			  ./srcs/split_by_null.c \
			  ./srcs/exec_command.c \
			  ./srcs/ft_pipelast.c \
			  ./srcs/pipe.c \
			  ./srcs/ft_cd.c \
			  ./srcs/ft_pipenew.c \
			  ./srcs/token_syn_check.c \
			  ./srcs/ft_echo.c \
			  ./srcs/ft_pwd.c \
			  ./srcs/parse.c \
			  ./srcs/util_envlist.c \
			  ./srcs/ft_export.c \
			  ./srcs/ft_split_quote.c \
			  ./srcs/parse_line.c \
			  ./srcs/util_envlist2.c \
			  ./srcs/ft_listadd_back.c \
			  ./srcs/ft_split_syn.c \
			  ./srcs/ft_listlast.c \
			  ./srcs/init_env.c \
			  ./srcs/redir_syn_check.c \
			  ./srcs/util_str.c \
			  ./srcs/ft_listnew.c \
			  ./srcs/redirection.c \
			  ./srcs/other_command.c \
			  ./srcs/main.c \
			  ./srcs/ft_listsize.c \
			  ./srcs/ft_env_sort.c \
			  ./srcs/convert_escape.c \
			  ./srcs/exit.c \
			  ./srcs/ft_listfree.c \

OBJS		= $(SRCS:.c=.o)
RM			= rm -f
CC			= gcc
FLAGS		= -Wall -Wextra -Werror -fsanitize=address

all : $(NAME)

$(NAME) : ${LIBFT} $(OBJS)
	$(CC) -lncurses $(CFLAGS) -o ${NAME} ${OBJS} ${LIBFT}

$(LIBFT) :
	make all -C ./libft
	make bonus -C ./libft
	cp ./libft/$(LIBFT) .

fclean : clean
	$(RM) $(NAME) $(bonus)

clean :
	make clean -C ./libft
	$(RM) $(OBJS)

re : fclean all

bonus : all

.PHONY: all clean fclean re bonus .c.o
