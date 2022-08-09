/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:04 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/09 12:16:43 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static t_token	*take_word(char **iter)
{
	t_token		*token;
	const char	*special_characters = "|<> \t\n";

	token = create_token(WORD);
	if (!token)
		return (NULL);
	while ((*iter) && (*iter)[0]
			&& ft_strchr(special_characters, (*iter)[0]) == NULL)
	{
		if ((*iter)[0] == '\'')
			take_single_quote(token, iter);
		else if ((*iter)[0] == '\"')
			take_double_quote(token, iter);
		else
		{
			ft_vecadd(token->value, *iter);
			(*iter)++;
		}
	}
	ft_vecadd(token->value, "\0");
	return (token);
}

static t_token	*take_pipe(char **iter)
{
	t_token	*token;

	token = create_token(PIPE);
	if (!token)
		return (NULL);
	if (ft_vecadd(token->value, *iter) == 0)
	{
		if (ft_vecadd(token->value, "\0") == 0)
		{
			(*iter)++;
			return (token);
		}
	}
	perror("minishell");
	destroy_token(token);
	return (NULL);
}

t_dlist	*lexer(char *iter)
{
	t_dlist	*token_list;
	t_token	*token;

	token_list = NULL;
	while (*iter)
	{
		if (*iter == ' ' || *iter == '\t' || *iter == '\n')
			iter++;
		else
		{
			if (*iter == '|')
				token = take_pipe(&iter);
			else if (*iter == '>' || *iter == '<')
				token = take_redirection(&iter);
			else
				token = take_word(&iter);
			if (!token)
			{
				ft_dlstclear(&token_list, (void*)destroy_token);
				g_status = 2;
				return (NULL);
			}
			ft_dlstadd_back(&token_list, ft_dlstnew(token));
		}
	}
	return (token_list);
}
