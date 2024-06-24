NAME = minishell

LIBFT_NAME = libft
LIBFT_DIR = libft/

INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)$(INCLUDE_DIR)

SRC_DIR = src/
OBJ_DIR = .obj/

CC = cc
LDFRAGS = -lreadline
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g
RM = rm -rf
NORM = norminette

# 新しいファイルはここに書いていって！
SRC_FILES = main.c token_list.c\
			tokenizer.c signal.c\
			error.c redirect.c\
			apple.c parser.c\
			ats_list.c cd.c\

OJB_FILES = $(SRC_FILES:%.c=%.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(OJB_FILES))

# color **********************************************
Y 			= "\033[33m"
R 			= "\033[31m"
G 			= "\033[32m"
B 			= "\033[34m"
X 			= "\033[0m"
UP 			= "\033[A"
CUT 		= "\033[K"
# *****************************************************

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo $(Y) "$(NAME) src files successfully compiled\n" $(X)
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "<-- Out of $(LIBFT_DIR)\n" $(X)
	@echo $(B) "$(NAME) creating" $(X)
	@printf $(UP)$(CUT)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFRAGS) $(LIBFT_DIR)$(LIBFT_NAME) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo $(Y) "Compiling $<" $(X)
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@
	@printf $(UP)$(CUT)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo $(R) "$(NAME) cleaned\n" $(X)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo $(R) "$(NAME) fcleaned\n" $(X)

re: fclean all

rebonus: fclean bonus

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | grep -v Error! | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true
	@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re norm
