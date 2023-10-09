# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 10:33:46 by bedos-sa          #+#    #+#              #
#    Updated: 2023/10/09 07:23:14 by gcoqueir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c srcs
vpath %.c bonus

NAME = minishell

CC = cc
FLAGS = -lreadline $(LIBFT)/libft.a
CFLAGS = -Wall -Wextra -Werror -I$(LIBS) -O3 -g3

LIBFT = ./libft
LIBS = ./include
OBJ_DIR = build/
INIT_DIR = init_utils/
BUILT_DIR = builtin/
SIG_DIR = signal/
TOKEN_DIR = token/
EXEC_DIR = exec/
VAR_AND_QUOTES_DIR = var_and_quotes/

RM = rm -f
FILES = main.c \
		frees.c \
		$(INIT_DIR)init_utils.c \
		$(BUILT_DIR)exit.c \
		$(BUILT_DIR)env.c \
		$(BUILT_DIR)pwd.c \
		$(BUILT_DIR)unset.c \
		$(BUILT_DIR)export.c \
		$(SIG_DIR)signal.c \
		$(TOKEN_DIR)token.c \
		$(TOKEN_DIR)lexer.c \
		$(TOKEN_DIR)syntax.c \
		$(VAR_AND_QUOTES_DIR)var_and_quotes.c \
		$(VAR_AND_QUOTES_DIR)expansion.c \
		$(VAR_AND_QUOTES_DIR)check_quotes.c \
		$(VAR_AND_QUOTES_DIR)check_tildes.c \
		$(EXEC_DIR)exec.c \
		$(EXEC_DIR)child_process.c \
		$(EXEC_DIR)child_dups.c \
		$(EXEC_DIR)pipes.c \
		$(EXEC_DIR)here_doc.c
		
OBJS = $(FILES:.c=.o)

all: mkdir_obj $(NAME)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

mkdir_obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(INIT_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILT_DIR)
	@mkdir -p $(OBJ_DIR)$(SIG_DIR)
	@mkdir -p $(OBJ_DIR)$(TOKEN_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(VAR_AND_QUOTES_DIR)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJS))
	@make -C $(LIBFT) --silent
	@$(CC) $(addprefix $(OBJ_DIR), $(OBJS)) $(FLAGS) -o $(NAME)
	@echo "\033[0;32mSUCCESS!\033[0m"

run: all
	./$(NAME)

val: all
	valgrind --suppressions=./local.supp --leak-check=full --show-leak-kinds=all ./$(NAME)

bonus: all

clean:
	@make clean -C $(LIBFT) --silent
	@$(RM) $(addprefix $(OBJ_DIR), $(OBJS))
	@echo "\033[0;36mBUILD DIRECTORY CLEAN!\033[0m"

fclean: clean
	@make fclean -C $(LIBFT) --silent
	@$(RM) $(NAME)
	@echo "\033[0;31mBINARY DESTROYED!\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus run val
