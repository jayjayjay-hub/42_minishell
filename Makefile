
NAME = minishell

CC = cc
# FLAGS = -Wall -Wextra -Werror
IFRAGS = -Iinclude -Iutils/gnl -Iutils/printf -Iutils/libft
MFLAGS = -lreadline

SRCS = $(wildcard ./src/*.c \
		./utils/libft/*.c \
		./utils/printf/*.c \
		./utils/gnl/*.c)
OBJS = $(SRCS:.c=.o)

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

%.o : %.c
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(IFRAGS) $(FLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@printf $(CUT)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(OBJS) $(MFLAGS) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)
	@echo

clean:
	@rm -rf $(OBJS)
	@echo $(R)Removed [$(OBJS)]$(X)

fclean: clean
	@rm -rf $(NAME)
	@echo $(R)Removed [$(NAME)]$(X)

re: fclean all

norm:
	@norminette $(SRCS) | grep Error | wc -l
	@norminette $(SRCS) | grep Error || true
	
.PHONY: all clean fclean re
