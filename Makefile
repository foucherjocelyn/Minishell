CFLAGS	?= -Wall -Werror -Wextra -MMD -MP
LDFLAGS ?=

SRCS	= main.c lexer.c parser.c executor.c execute_simple_command.c \
			destroy_token.c lexer_redirections.c lexer_quotes.c \
			expand_variables.c expand_quotes.c syntax_tree_utils.c \
			parse_simple_command.c builtins/cd.c builtins/echo.c	\
			builtins/env.c builtins/exit.c builtins/export.c		\
			builtins/pwd.c builtins/unset.c builtins/utils.c		\
			builtins/utils_cd.c	builtins/utils_export.c				\
			builtins/utils_unset.c builtins/execute_builtins.c	\
			check_for_unexpected_token.c close_standard_fds.c \
			create_token.c get_token.c get_file_path.c

DEPS	:= $(SRCS:%.c=%.d)
OBJS	:= $(DEPS:.d=.o)

NAME		= minishell

LIBFT		= libft/libft.a

all:	$(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lncurses -lreadline -I libft -I. libft/libft.a

clean:
	$(MAKE) fclean -C libft
	rm -rf $(DEPS)
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
