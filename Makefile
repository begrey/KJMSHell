C = clang

NAME		= minishell
LIBFT		= libft.a

SRCS		= ./srcs/convert_env.c \
			  ./srcs/ft_pipeadd_back.c \
			  ./srcs/split_by_null.c \
			  ./srcs/exec_command.c \
			  ./srcs/ft_pipelast.c \
			  ./srcs/test_pip.c \
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
			  ./srcs/util_list.c \
			  ./srcs/ft_listlast.c \
			  ./srcs/init_env.c \
			  ./srcs/redir_syn_check.c \
			  ./srcs/util_str.c \
			  ./srcs/ft_listnew.c \
			  ./srcs/redirection.c \

OBJS		= $(SRCS:.c=.o)
RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : ${LIBFT} $(OBJS)
	$(CC) $(CFLAGS) -o ${NAME} ${OBJS} ${LIBFT}

$(LIBFT) :
	make all -C ./libft
	cp ./libft/$(LIBFT) .

fclean : clean
	$(RM) $(NAME) $(bonus)
	make fclean -C ./libft

clean :
	$(RM) $(OBJS)
	make clean -C ./libft

re : fclean all

bonus : all

.PHONY: all clean fclean re bonus .c.o
