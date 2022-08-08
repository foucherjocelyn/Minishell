/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:28:47 by jfoucher          #+#    #+#             */
/*   Updated: 2022/08/05 08:55:44 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "../builtins.h"

static long long	ft_atoll(const char *nptr)
{
	long long	result;
	int			i;

	i = 0;
	result = 0;
	if (!ft_strcmp(nptr, "-9223372036854775808"))
		return (LONG_MIN);
	if (nptr[0] == '-' || nptr[0] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i++] - '0';
		if (result < 0)
		{
			ft_putstr_fd("minishell: exit: numeric argument required", 2);
			return (2);
		}
	}
	if (nptr[i])
		return (ft_putstr_fd("minishell: exit: numeric argument required", 2),
			2);
	if (nptr[0] == '-')
		result = -result;
	return (result);
}

int	execute_builtin_exit(char **argv, t_tab *tabs)
{
	// unsigned int	status;
	int	exit_status;
	// status = exit_status % 256;
	free_2d_tab(&tabs->env);
	free_2d_tab(&tabs->exp);
	printf("exit\n");
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("bash: exit: too many arguments", 2);
		exit (1);
	}
	if (argv[1])
	{
		/*if (!ft_isstrdigit(argv[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required", 2);
			exit(2);
		}*/
		exit_status = ft_atoll(argv[1]);
		free_2d_tab(&argv);
		exit(exit_status);
	}
	else
	{
		free_2d_tab(&argv);
		exit(g_status);
	}
	/*	si exit est un token il faut juste ft_putendl("exit"); et 
		mettre le exit status a 0
		sinon faut tout bien free si c pas deja fait et exit(1);
		SIGQUIT	131
		SIGINT	130
		command not found	127
		A file to be executed was found, but it was not an 
		executable utility.	126
		si tout se passe bien 0
		sinon >0 mais si >255 cest undefined behavior donc on modulo 256 donc
		on peut avoir un faux 0 comme si tout se passait bien	*/
}
