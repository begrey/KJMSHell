NAME = minishell

CC = gcc

SRCS = ./gcc_me.c

all : $(NAME)

$(NAME) : $(SRCS)
	gcc $(SRCS)
