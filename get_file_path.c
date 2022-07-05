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

#include <unistd.h>
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

	i = 0;
	filepath = ft_strdup(pathname);
	if (access(pathname, X_OK) == -1)
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
		free(path);
		free_2d_tab(&patharray);
	}
	return (filepath);
}
