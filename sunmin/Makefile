NAME	= minishell
LIBFT	= libft.a


SRCS	= ./srcs/main.c	\
		  ./srcs/parse_line.c \
		  ./srcs/parse_token.c \
		  ./srcs/parse_command.c \
		  ./srcs/exec_pwd.c \
		  ./srcs/exec_export.c \
		  ./srcs/init_env.c \
		  ./srcs/util_list.c 


OBJS	= $(SRCS:.c=.o)
RM		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : ${LIBFT} $(OBJS)
	$(CC) $(CFLAGS) -o ${NAME} ${OBJS} ${LIBFT}

${LIBFT} :
	make -C ./libft
	make bonus -C ./libft
	cp ./libft/$(LIBFT) .

clean	:
	make clean -C ./libft
	$(RM) $(OBJS) $(LIBFT)

fclean 	: clean
	$(RM) $(NAME)

re : fclean all

bonus : all

.PHONY : all clean fclean re bonus
