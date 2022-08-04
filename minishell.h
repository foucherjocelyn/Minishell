/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:10:54 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/04 04:46:15 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <linux/limits.h>
# include <string.h>
# include <signal.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"

extern int	g_status;

typedef struct s_redirections
{
	int	fdin;
	int	fdout;
	int	pipein[2];
	int pipeout[2];
}t_redirections;

typedef struct s_tab
{
	char	**env;
	char	**exp;
}	t_tab;

int		execute_simple_command(t_syntax_node **tree_root,
			t_syntax_node *command_tree, t_tab *tabs);
void	close_standard_fds(void);
int		check_for_unexpected_token(t_list *token_list);
#endif
