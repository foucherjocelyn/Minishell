/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:09 by jfoucher          #+#    #+#             */
/*   Updated: 2022/07/03 13:16:49 by lfchouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "builtins.h"
#include "executor.h"

int	g_status;

static char	**cpy_exp(char **env, char **cpy)
{
	int		i;

	i = 0;
	cpy = malloc(sizeof(char *) * (len_env(env) + 1000));
	if (!cpy)
		return (printf("\e[1;31mCopy failed\e[0m"), NULL);
	while (env[i])
	{
		cpy[i] = ft_strdup(env[i]);
		if (!cpy[i])
			return (free_2d_tab(&cpy),
				printf("\e[1;31Copy failed\n\e[0m"), NULL);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

static int	check_for_unexpected_pipe(t_list *token_list)
{
	if (get_token(token_list)->type == PIPE)
		return (-1);
	token_list = token_list->next;
	while (token_list)
	{
		if (get_token(token_list)->type == PIPE)
			if (!token_list->next || get_token(token_list->next)->type == PIPE)
				return (-1);
		token_list = token_list->next;
	}
	return (0);
}

int	check_for_unexpected_token(t_list *token_list)
{
	if (check_for_unexpected_pipe(token_list) != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_status = 2;
		return (-1);
	}
	while (token_list && token_list->next)
	{
		if (get_token(token_list)->type != WORD
			&& get_token(token_list)->type != PIPE)
		{
			if (get_token(token_list->next)->type != WORD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(get_token(token_list->next)->value->buffer, 2);
				ft_putstr_fd("'\n", 2);
				g_status = 2;
				return (-1);
			}
		}
		token_list = token_list->next;
	}
	if (get_token(token_list)->type != WORD
		&& get_token(token_list)->type != PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		g_status = 2;
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **argp)
{
	char			*line;
	t_list			*token_list;
	t_syntax_node	*syntax_tree;
	t_tab			tabs;

	(void)argc;
	(void)argv;
	tabs.env = cpy_exp(argp, tabs.env);
	tabs.exp = cpy_exp(argp, tabs.exp);
	g_status = 0;
	line = readline("$ ");
	while (line)
	{
		if (line[0] == '\0')
			free(line);
		else
		{
			add_history(line);
			token_list = lexer(line);
			free(line);
			if (token_list)
			{
				if (check_for_unexpected_token(token_list) == -1)
					ft_lstclear(&token_list, NULL);
				else
				{
					syntax_tree = parser(token_list, tabs.env);
					ft_lstclear(&token_list, NULL);
					executor(syntax_tree, &tabs);
					delete_syntax_tree(syntax_tree);
				}
			}
		}
		line = readline("$ ");
	}
	close_standard_fds();
	rl_clear_history();
	free_2d_tab(&tabs.env);
	free_2d_tab(&tabs.exp);
	return (g_status);
}
