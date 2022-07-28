/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:08:51 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:08:53 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "executor.h"
#include "minishell.h"
#include <stdio.h>

int	execute_redirection(t_syntax_node *command_tree)
{
	char	*pathname;
	int		oldfd;
	int		newfd;
	int		flags;

	if (command_tree->token->type == GREAT)
	{
		flags = O_CREAT | O_WRONLY;
		newfd = STDOUT_FILENO;
	}
	else if (command_tree->token->type == GREATGREAT)
	{
		flags = O_CREAT | O_WRONLY | O_APPEND;
		newfd = STDOUT_FILENO;
	}
	else
	{
		flags = O_RDONLY;
		newfd = STDIN_FILENO;
	}
	pathname = command_tree->left->token->value->buffer;
	oldfd = open(pathname, flags, 0644);
	if (oldfd == -1)
	{
		perror("minishell: invalid_file");
		g_status = 1;
		return (-1);
	}
	dup2(oldfd, newfd);
	close(oldfd);
<<<<<<< HEAD
    if (command_tree->right)
		return (execute_redirection(command_tree->right));
=======
>>>>>>> 6b16524cecc1780fb656448c617d26512105777e
	return (0);
}

int	execute_command(t_syntax_node *tree_root, t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	if (command_tree->right)
		if (execute_redirection(command_tree->right) == -1)
			return (-1);
	if (command_tree->left)
		execute_simple_command(tree_root, command_tree->left, redirect, tabs);
	dup2(redirect->fdout, STDOUT_FILENO);
	return (0);
}

void	execute_pipe(t_syntax_node *tree_root, t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	assert(pipe(redirect->pipefd) != -1);
	dup2(redirect->pipefd[1], STDOUT_FILENO);
	close(redirect->pipefd[1]);
	execute_command(tree_root, command_tree->left, redirect, tabs);
	dup2(redirect->fdout, STDOUT_FILENO);
	dup2(redirect->pipefd[0], STDIN_FILENO);
	close(redirect->pipefd[0]);
	execute_job(tree_root, command_tree->right, redirect, tabs);
	dup2(redirect->fdin, STDIN_FILENO);
}

void	execute_job(t_syntax_node *tree_root, t_syntax_node *command_tree,
		t_redirections *redirect, t_tab *tabs)
{
	int	wstatus;

	wstatus = 0;
	if (command_tree->right == NULL)
	{
		execute_command(tree_root, command_tree->left, redirect, tabs);
	}
	else
	{
		execute_pipe(tree_root, command_tree, redirect, tabs);
	}
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		g_status = WEXITSTATUS(wstatus);
}

void	executor(t_syntax_node *command_tree, t_tab *tabs)
{
	t_redirections	redirect;

<<<<<<< HEAD
	if (!command_tree)
		return ;
=======
>>>>>>> 6b16524cecc1780fb656448c617d26512105777e
	redirect.fdin = dup(STDIN_FILENO);
	redirect.fdout = dup(STDOUT_FILENO);
	redirect.pipefd[0] = -1;
	redirect.pipefd[1] = -1;
	execute_job(command_tree, command_tree, &redirect, tabs);
	dup2(redirect.fdin, STDIN_FILENO);
	dup2(redirect.fdout, STDOUT_FILENO);
	close(redirect.fdin);
	close(redirect.fdout);
}
