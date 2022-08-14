/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:08:51 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/14 17:26:53 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <stdio.h>

int	execute_command(t_syntax_node **tree_root, t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	dup2(redirect->pipein[0], STDIN_FILENO);
	dup2(redirect->pipeout[1], STDOUT_FILENO);
	safe_close(redirect->pipein[0]);
	safe_close(redirect->pipein[1]);
	safe_close(redirect->pipeout[0]);
	safe_close(redirect->pipeout[1]);
	g_status = 0;
	if (command_tree->right)
	{
		if (execute_redirection(command_tree->right) == -1)
			g_status = 1;
	}
	if (!g_status && command_tree->left)
		execute_simple_command(tree_root, command_tree->left, tabs, redirect);
	else
	{
		close_standard_fds();
		delete_syntax_tree(tree_root);
		free_2d_tab(&(tabs->env));
		free_2d_tab(&(tabs->exp));
		exit (g_status);
	}
	return (0);
}

void	execute_last_job(t_syntax_node **tree_root, t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	pid_t	pid;
	int		wstatus;

	redirect->pipeout[0] = -1;
	redirect->pipeout[1] = -1;
	pid = fork();
	if (pid == 0)
		execute_command(tree_root, command_tree->left, redirect, tabs);
	else
	{
		safe_close(redirect->pipein[0]);
		safe_close(redirect->pipein[1]);
		if (waitpid(pid, &wstatus, 0) != -1)
			if (WIFEXITED(wstatus))
				g_status = WEXITSTATUS(wstatus);
	}
}

void	execute_job(t_syntax_node **tree_root, t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	int		wstatus;
	pid_t	pid;

	wstatus = 0;
	redirect->pipein[0] = redirect->pipeout[0];
	redirect->pipein[1] = redirect->pipeout[1];
	if (command_tree->right == NULL)
		execute_last_job(tree_root, command_tree, redirect, tabs);
	else
	{
		pipe(redirect->pipeout);
		pid = fork();
		if (pid == 0)
			execute_command(tree_root, command_tree->left, redirect, tabs);
		else
		{
			safe_close(redirect->pipein[0]);
			safe_close(redirect->pipein[1]);
			execute_job(tree_root, command_tree->right, redirect, tabs);
			wait (&wstatus);
		}
	}
}

void	executor(t_syntax_node **tree_root, t_tab *tabs)
{
	t_redirections	redirect;

	redirect.fdin = STDIN_FILENO;
	redirect.fdout = STDOUT_FILENO;
	redirect.pipein[0] = -1;
	redirect.pipein[1] = -1;
	redirect.pipeout[0] = -1;
	redirect.pipeout[1] = -1;
	if ((*tree_root)->right == NULL
		&& (*tree_root)->left->left
		&& is_a_builtin((*tree_root)->left->left->left->token->value->buffer))
	{
		redirect.save_fdin = dup(STDIN_FILENO);
		redirect.save_fdout = dup(STDOUT_FILENO);
		execute_command(tree_root, (*tree_root)->left, &redirect, tabs);
		dup2(redirect.save_fdin, STDIN_FILENO);
		dup2(redirect.save_fdout, STDOUT_FILENO);
		safe_close(redirect.save_fdin);
		safe_close(redirect.save_fdout);
	}
	else
		execute_job(tree_root, *tree_root, &redirect, tabs);
}
