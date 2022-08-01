CFLAGS	?= -Wall -Werror -Wextra
LDFLAGS ?=

OBJS	= main.o lexer.o parser.o executor.o execute_simple_command.o \
			destroy_token.o lexer_redirections.o lexer_quotes.o \
			expand_variables.o expand_quotes.o syntax_tree_utils.o \
			parse_simple_command.o builtins/cd.o builtins/echo.o	\
			builtins/env.o builtins/exit.o builtins/export.o		\
			builtins/pwd.o builtins/unset.o builtins/utils.o		\
			builtins/utils_cd.o	builtins/utils_export.o				\
			builtins/utils_unset.o builtins/execute_builtins.o	\
			check_for_unexpected_token.o close_standard_fds.o \
			create_token.o get_token.o get_file_path.o

NAME		= minishell

LIBFT		= libft/libft.a

all:	$(NAME)

%.o : %.c
	$(CC) -c $(CFLAGS) -I libft -I. $< -o $@

$(LIBFT):
	$(MAKE) -C libft

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lncurses -lreadline -I libft -I. libft/libft.a

clean:
	$(MAKE) fclean -C libft
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
