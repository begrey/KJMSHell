C = clang

NAME		= minishell
LIBFT		= libft.a

SRCS		= ./srcs/main.c \
			  ./srcs/parse_line.c \
			  ./srcs/parse_token.c \
			  ./srcs/parse_command.c \

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