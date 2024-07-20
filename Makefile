# project name
NAME = minishell

# library name
LIBFT_NAME = libft
LIBFT_DIR = libft/

# include
INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)$(INCLUDE_DIR)

SRC_DIR = src/
OBJ_DIR = .obj/

ERROR_DIR = error/

# compiler
CC = cc
LDFRAGS = -lreadline
CFLAGS = -Wall -Wextra -Werror
# debug option
# CFLAGS = -g
RM = rm -rf
NORM = norminette

SRC_FILES = main.c token_list.c\
			tokenizer.c signal.c\
			error.c redirect.c\
			parser.c\
			ats_list.c\
			child.c pipe.c\
			variable_list.c variable.c\
			expansion.c\
			utils.c\
			syntax.c\
			builtin.c\
			builtin_exit.c\
			builtin_cd.c\
			builtin_echo.c\
			builtin_pwd.c\
			builtin_export.c\
			builtin_env.c\
			free.c\
			heredoc.c\
			childset.c\
			env_list.c\
			env_list_utils.c\
			env_init.c\
			expansion_utils.c\
			variable_utils.c\
			tokenizer_utils.c

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
	@$(RM) $(ERROR_DIR)
	@echo $(R) "$(NAME) cleaned\n" $(X)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(RM) $(ERROR_DIR)
	@echo $(R) "$(NAME) fcleaned\n" $(X)

re: fclean all

test: all
	@echo $(Y) "<<< $(NAME) test >>>" $(X)
	@./tester/my_tester/tester.sh

diff: all
	@echo $(Y) "<<< $(NAME) diff >>>" $(X)
	@./tester/my_tester/diff.sh

all_test: all test diff

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | grep -v Error! | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true
	@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re norm
