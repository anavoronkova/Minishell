# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 18:55:18 by aboiarin          #+#    #+#              #
#    Updated: 2024/04/29 18:13:25 by aboiarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

RM = rm -f

RM_DIR = rm -r

NAME = minishell

LIBFT_PATH = ./src/libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC = src/main.c \
	src/lexer/lexer.c src/lexer/handle_nonwords.c src/lexer/init_tokens.c \
	src/parser/parser.c src/parser/token_checks.c src/parser/check_redirections.c \
	src/parser/handle_redirect.c src/parser/handle_quotes.c src/parser/handle_env.c \
 	src/parser/parser_utils.c src/parser/add_input.c src/parser/init_cmds.c\
	src/builtins/builtins.c src/builtins/builtins2.c src/builtins/builtins_utils.c \
	src/builtins/builtins_utils2.c src/builtins/builtins_utils3.c  \
	src/executor/executor.c src/executor/ex_redirections.c src/executor/pipeline.c src/executor/ex_utils.c \
	src/executor/execve.c \
	src/free.c src/signals.c src/main_utils.c src/echoctl.c \

OBJ_DIR = obj

OBJ = $(patsubst %,$(OBJ_DIR)/%,$(SRC:.c=.o))

READLINE_LIB = -lreadline -lhistory -L$(READLINE_DIR)/lib

READLINE_INC = -I$(READLINE_DIR)/include

LDFLAGS = $(READLINE_LIB)

all: start_message $(NAME) success_message

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo 'minishell done ✅'

$(LIBFT):
	@echo 'Compiling libft... 📀'
	@make -C $(LIBFT_PATH) all --no-print-directory
	@echo 'libft done ✅'

clean:
	@$(RM) $(OBJ)
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@echo 'Object files removed ✨'

start_message:
	@echo 'Compiling minishell... 🐚'

success_message:
	@echo 'All done ✅'

re_message:
	@echo 'Starting over... ⏪'

fclean:	clean
		@make -C $(LIBFT_PATH) fclean --no-print-directory
		@$(RM_DIR) $(OBJ_DIR)
		@echo 'Object folder removed ✨'
		@$(RM) $(NAME)
		@echo 'Executable removed ✨'

re: re_message fclean all

.PHONY: all clean fclean re