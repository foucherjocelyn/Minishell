/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:01:58 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/05 08:54:50 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "libft/libft.h"
# include "minishell.h"

int		expand_variable(t_vector *word, int *iter, char **envp);
void	expander(t_list **tokens, t_vector *word, char **envp);
#endif
