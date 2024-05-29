CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRCS =	main.c\
		action1.c action2.c\
		initialize_data.c\
		routine_philo.c


NAME = philo
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) Philosopher.h
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
