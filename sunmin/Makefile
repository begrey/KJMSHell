NAME = mshell

CC = gcc

SRCS = *.c *.h

C_FLAGS = -fsanitize=address

all : $(NAME)

$(NAME) : $(SRCS)
	gcc $(C_FLAGS) $(SRCS)
