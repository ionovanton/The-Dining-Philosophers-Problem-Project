NAME				=	philo
CC					=	cc
FLAGS				=	-pthread -Wall -Wextra -Werror
SRCS				=	main.c init.c philo_1.c philo_2.c utils.c time.c
OBJECT_DIRECTORY	=	objs
OBJECT_LIST			=	$(SRCS:.c=.o)
OBJS				=	$(addprefix $(OBJECT_DIRECTORY)/,$(OBJECT_LIST))
HEADER_DIRECTORY	=	includes
HEADER_LIST			=	philo.h
HDRS				=	$(addprefix $(HEADER_DIRECTORY)/,$(HEADER_LIST))
INCLUDE				=	-I $(HEADER_DIRECTORY)
TMP					=	philo_debug *.dSYM vgcore.*

all: $(OBJECT_DIRECTORY) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) $(OBJS) -o $@

$(OBJECT_DIRECTORY)/%.o: %.c $(HDRS)
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECT_DIRECTORY):
	mkdir -p $@

clean:
	rm -rfd $(OBJECT_DIRECTORY)
	rm -rf $(TMP)

fclean: clean
	rm -f $(NAME)

re: cls fclean all

cls:
	printf "\33c\e[3J"

n: norminette $(SRCS) $(HDRS)

.PHONY: all clean fclean re cls n
