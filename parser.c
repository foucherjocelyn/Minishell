/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:14 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/05 10:25:04 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "expander.h"

void	advance_to_next_command_argument(t_dlist **token)
{
	while (*token && get_token(*token)->type != PIPE)
	{
		if (get_token(*token)->type == WORD)
			break ;
		if (get_token(*token)->type == GREAT
			|| get_token(*token)->type == GREATGREAT
			|| get_token(*token)->type == LESS)
		{
			(*token) = (*token)->next;
			(*token) = (*token)->next;
		}
	}
}

t_syntax_node	*parse_redirection(t_dlist **token, char **envp)
{
	t_syntax_node	*node;

	while (*token && (get_token(*token)->type != GREAT
			&& get_token(*token)->type != LESS
			&& get_token(*token)->type != GREATGREAT)
		&& get_token(*token)->type != PIPE)
		(*token) = (*token)->next;
	if ((*token) == NULL || get_token(*token)->type == PIPE)
		return (NULL);
	node = create_node();
	node->type = REDIRECTION;
	node->token = get_token(*token);
	(*token) = (*token)->next;
	node->left = create_node();
	node->left->type = FILENAME;
	node->left->token = get_token(*token);
	(*token) = (*token)->next;
	if (*token)
		node->right = parse_redirection(token, envp);
	return (node);
}

t_syntax_node	*parse_command(t_dlist **token, char **envp)
{
	t_syntax_node	*node;
	t_dlist			*head_token;

	node = create_node();
	node->type = COMMAND;
	head_token = *token;
	while ((*token) && get_token(*token)->type != PIPE)
	{
		if (get_token(*token)->type == WORD)
			expander(token, get_token(*token)->value, envp);
		(*token) = (*token)->next;
	}
	*token = head_token;
	node->right = parse_redirection(token, envp);
	*token = head_token;
	advance_to_next_command_argument(token);
	if ((*token) && get_token(*token)->type == WORD)
		node->left = parse_simple_command(token, envp);
	return (node);
}

t_syntax_node	*parse_job(t_dlist **token, char **envp)
{
	t_syntax_node	*node;

	node = create_node();
	node->type = JOB;
	node->left = parse_command(token, envp);
	if ((*token))
	{
		if (get_token(*token)->type == PIPE)
		{
			node->token = get_token(*token);
			(*token) = (*token)->next;
			node->right = parse_job(token, envp);
		}
	}
	return (node);
}

t_syntax_node	*parser(t_dlist *token, char **envp)
{
	t_syntax_node	*node;

	if (!token)
		return (NULL);
	node = parse_job(&token, envp);
	return (node);
}
