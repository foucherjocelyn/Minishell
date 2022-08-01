/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:08:41 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:08:44 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "minishell.h"

static int	count_arguments(t_syntax_node *token_list)
{
	int	nb_arguments;

	nb_arguments = 1;
	while (token_list)
	{
		nb_arguments++;
		token_list = token_list->right;
	}
	return (nb_arguments);
}

static char	**compose_argv(t_syntax_node *command_tree)
{
	int		i;
	char	**argv;
	int		nb_args;

	nb_args = count_arguments(command_tree->right) + 1;
	argv = malloc(sizeof(t_syntax_node) * (nb_args));
	i = 0;
	while (command_tree)
	{
		argv[i] = ft_strdup(command_tree->left->token->value->buffer);
		command_tree = command_tree->right;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	is_a_builtin(const char *command)
{
	int			i;
	const char	*builtins[] = {"cd", "echo", "env", "exit",
		"export", "pwd", "unset", NULL};

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(command, builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	execute_in_child(t_syntax_node **tree_root,
		t_redirections *redirect, char **argv, t_tab *tabs)
{
	char	*filepath;

	close(redirect->pipefd[0]);
	close(redirect->pipefd[1]);
	close(redirect->fdin);
	close(redirect->fdout);
	if (is_a_builtin(argv[0]))
		g_status = execute_builtins(argv, tabs);
	else
	{
		filepath = get_filepath(argv[0], tabs->env);
		if (filepath)
		{
			execve(filepath, argv, tabs->env);
			perror ("minishell");
			g_status = 126;
			free(filepath);
		}
	}
	close_standard_fds();
	free_2d_tab(&argv);
	delete_syntax_tree(tree_root);
	free_2d_tab(&(tabs->env));
	free_2d_tab(&(tabs->exp));
	exit(g_status);
}

int	execute_simple_command(t_syntax_node **tree_root,
		t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	pid_t	pid;
	char	**argv;

	argv = compose_argv(command_tree);
	if (is_a_builtin(argv[0]) && (*tree_root)->right == NULL)
	{
		delete_syntax_tree(tree_root);
		g_status = execute_builtins(argv, tabs);
		return (0);
	}
	pid = fork();
	if (pid == 0)
		execute_in_child(tree_root, redirect, argv, tabs);
	free_2d_tab(&argv);
	return (0);
}
