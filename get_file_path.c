/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfoucher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:08:58 by jfoucher          #+#    #+#             */
/*   Updated: 2022/06/11 10:08:59 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "builtins.h"

static char	*ft_strjoin_with_slash(char *s1, char *s2)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, "/");
	result = ft_strjoin(tmp, s2);
	free(tmp);
	return (result);
}

char	*get_filepath(char *pathname, char **env)
{
	char	*filepath;
	char	*path;
	char	**patharray;
	int		i;
	struct stat statbuf;

	i = 0;
	filepath = ft_strdup(pathname);
	if (filepath[0] == '/' || (filepath[0] == '.' && filepath[1] == '/'))
	{
		stat(filepath, &statbuf);
		if (access(filepath, F_OK))
		{
			perror ("minishell");
			g_status = 127;
			free(filepath);
			filepath = NULL;
		}
		else if (!S_ISREG(statbuf.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(filepath, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(EISDIR), 2);
			g_status = 126;
			free(filepath);
			filepath = NULL;
		}
		else if (access(filepath, X_OK))
		{
			perror ("minishell");
			g_status = 126;
			free(filepath);
			filepath = NULL;
		}
	}
	else
	{
		path = ft_getenv(env, "PATH");
		free(filepath);
		patharray = ft_split(path, ':');
		while (patharray[i])
		{
			filepath = ft_strjoin_with_slash(patharray[i], pathname);
			if (access(filepath, X_OK) == 0)
				break ;
			free(filepath);
			filepath = NULL;
			i++;
		}
		if (!filepath)
		{
			ft_putendl_fd(": command not found", 2);
			g_status = 127;
			free(filepath);
			filepath = NULL;
		}
		free(path);
		free_2d_tab(&patharray);
	}
	return (filepath);
}
