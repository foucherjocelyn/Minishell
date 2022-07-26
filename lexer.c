/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:09:04 by jfoucher          #+#    #+#             */
/*   Updated: 2022/07/26 01:28:58 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	ft_vecadd(token->value, *iter);
	ft_vecadd(token->value, "\0");
	(*iter)++;
	return (token);
}

static	int check_for_unclosed_quotes(char *line)
{
	while (*line)
	{
		if (*line == '\'')
		{
			line = ft_strchr(line + 1, '\'');
			if (line == NULL)
				return (ft_putstr_fd("minishell: unexpected EOF "
						"while looking for matching `''\n", 2), -1);
		}
		else if (*line == '\"')
		{
			line = ft_strchr(line + 1, '\"');
			if (line == NULL)
				return (ft_putstr_fd("minishell: unexpected EOF "
						"while looking for matching `\"'\n", 2), -1);
		}
		line++;
	}
	return (0);
}

t_list	*lexer(char *line)
{
	t_list	*token_list;
	char	*iter;
	t_token	*token;

	if (check_for_unclosed_quotes(line) == -1)
		return (g_status = 2, NULL);
	iter = line;
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
			ft_lstadd_back(&token_list, ft_lstnew(token));
		}
	}
	return (token_list);
}
