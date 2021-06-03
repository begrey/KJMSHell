C = clang

NAME		= minishell
LIBFT		= libft.a

SRCS		= ./srcs/parse/convert_env.c \
			  ./srcs/parse/convert_env_util.c \
			  ./srcs/parse/convert_env_util2.c \
			  ./srcs/parse/split_by_null.c \
			  ./srcs/parse/token_syn_check.c \
			  ./srcs/parse/parse.c \
			  ./srcs/parse/parse_util.c \
			  ./srcs/parse/parse_util2.c \
			  ./srcs//util/util_envlist.c \
			  ./srcs/exec/ft_export.c \
			  ./srcs/exec/ft_export_util.c \
			  ./srcs/exec/ft_export_util2.c \
			  ./srcs/parse/ft_split_quote.c \
			  ./srcs/parse/ft_split_quote_util.c \
			  ./srcs/parse/ft_split_quote_util2.c \
			  ./srcs/parse/ft_split_quote_util3.c \
			  ./srcs/util/util_envlist2.c \
			  ./srcs/util/util_list.c \
			  ./srcs/parse/init_env.c \
			  ./srcs/parse/redir_syn_check.c \
			  ./srcs/util/util_str.c \
			  ./srcs/util/util_str2.c \
			  ./srcs/stream/redirection.c \
			  ./srcs/stream/redirection_util.c \
			  ./srcs/stream/redirection_util2.c \
			  ./srcs/stream/redirection_util3.c \
			  ./srcs/main.c \
			  ./srcs/exec/ft_env_sort.c \
			  ./srcs/parse/convert_escape.c \
			  ./srcs/parse/convert_escape_util.c \
			  ./srcs/util/ft_free.c \
			  ./srcs/stream/pipe.c \
			  ./srcs/util/util_pipe.c \
			  ./srcs/exec/ft_env.c \
			  ./srcs/exec/ft_unset.c \
			  ./srcs/exec/exec_command.c \
			  ./srcs/exec/ft_cd.c \
			  ./srcs/exec/ft_echo.c \
			  ./srcs/exec/ft_pwd.c \
			  ./srcs/exec/ft_exit.c \
			  ./srcs/exec/other_command.c \
			  ./srcs/system/input_line.c \
			  ./srcs/system/signal.c \
			  ./srcs/system/cursor.c \
			  ./srcs/system/history.c \
			  ./srcs/system/term.c \

OBJS		= $(SRCS:.c=.o)
RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-fsanitize=address

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
