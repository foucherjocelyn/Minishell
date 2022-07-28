/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_unexpected_token.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:03:11 by jfoucher          #+#    #+#             */
/*   Updated: 2022/07/28 16:03:13 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
