#include "../builtins.h"

static char	*ft_strcat(char *dest, char *src)
{
	size_t	dest_len;
	size_t	i;

	i = 0;
	if (dest)
		dest_len = ft_strlen(dest);
	else
		return (src);
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

int	found_name_with_value(char **exp, char *to_find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (exp[i])
	{
		j = 0;
		k = 0;
		if (exp[i][j] == to_find[k])
		{
			while (to_find[k] && exp[i][j] && exp[i][j] == to_find[k])
			{
				j++;
				k++;
			}
			if ((exp[i][j] && (exp[i][j] == '=' && !to_find[k])) ||
				(!exp[i][j] && !to_find[k]))
				return (i);
		}
		i++;
	}
	return (-1);
}

static void	change_oldpwd_value(char **to_change, char *to_cd)
{
	int	i;
	int	j;

	i = 0;
	j = 7;
	if (*to_change)
		ft_bzero((*to_change), ft_strlen(*to_change));
	*to_change = ft_strcat(*to_change, "OLDPWD=");
	while (to_cd[i])
	{
		(*to_change)[j] = to_cd[i];
		i++;
		j++;
	}
	(*to_change)[j] = '\0';
}

static char	*export_oldpwd(char *real_pwd_path)
{
	char	*new_oldpwd;

	new_oldpwd = malloc(PATH_MAX);
	if (!new_oldpwd)
		return (/*nique ta mere les leaks, */NULL);
	new_oldpwd = NULL;
	new_oldpwd = ft_strcat(new_oldpwd, "OLDPWD=");
	new_oldpwd = ft_strcat(new_oldpwd, real_pwd_path);
	return (new_oldpwd);
}

int	deal_with_oldpwd(t_tab *tabs, char *real_pwd_path, char *getenv_pwd_path)
{
	int			j;
	static int	deal;

	if (found_name_with_value(tabs->env, "OLDPWD") == -1)
		return (EXIT_FAILURE);
	j = found_name(tabs->env, "PWD");
	if (j == -1)
	{
		j = found_name(tabs->env, "OLDPWD");
		if (j != -1 && deal == 0)
		{
			while (tabs->env[j])
			{
				tabs->env[j] = tabs->env[j + 1];
				j++;
			}
			tabs->env[j] = 0;
			deal++;
		}
		else if (j == -1 && deal >= 1)
		{
			tabs->env[len_env(tabs->env)] = ft_strdup(export_oldpwd(real_pwd_path));
			tabs->env[len_env(tabs->env) + 1] = 0;
			deal++;
		}
		else
			change_oldpwd_value(&tabs->env[len_env(tabs->env)], real_pwd_path);
	}
	else
	{
		change_oldpwd_value(&tabs->env[found_name(tabs->env, "PWD")], getenv_pwd_path);
		deal = 0;
	}
	return (EXIT_SUCCESS);
}

/*static void	fck_the_norm(char **to_set)
{
	to_set[0][0] = 0;
	to_set[1] = NULL;
}*/

// int	deal_with_pwd(t_tab *tabs)
// {
// 	char	buf[PATH_MAX];
// 	char	**to_change;

// 	if (found_name_with_value(tabs->env, "PWD") != -1)
// 	{
// 		if (getcwd(buf, PATH_MAX))
// 		{
// 			to_change = malloc(sizeof(char *) * 3);
// 			if (!to_change)
// 				return (printf("\e[1;31mPWD n a pas ete mis a jour\e[0m"), 1);
// 			to_change[0] = malloc(2);
// 			to_change[0][0] = 'o';
// 			to_change[0][1] = 0;
// 			to_change[1] = malloc(5 + ft_strlen(buf));
// 			if (!to_change[1])
// 				return (printf("\e[1;31mPWD n a pas ete mis a jour\e[0m"), 1);
// 			// fck_the_norm(to_change);
// 			to_change[1][0] = 0;
// 			to_change[1] = ft_strcat(to_change[1], "PWD");
// 			to_change[2] = NULL;
// 			execute_builtin_unset(tabs, to_change);
// 			to_change[1] = ft_strcat(to_change[1], "=");
// 			to_change[1] = ft_strcat(to_change[1], buf);
// 			// to_change[2] = NULL;
// 			execute_builtin_export(tabs, to_change);
// 			free(to_change);
// 		}
// 		else
// 			return (pwd_not_found(), EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

static void	change_pwd_value(char **to_change, char *to_cd)
{
	int	i;
	int	j;

	i = 0;
	j = 7;
	if (*to_change)
		ft_bzero((*to_change), ft_strlen(*to_change));
	*to_change = ft_strcat(*to_change, "PWD=");
	while (to_cd[i])
	{
		(*to_change)[j] = to_cd[i];
		i++;
		j++;
	}
	(*to_change)[j] = '\0';
}

int	deal_with_pwd(t_tab *tabs)
{
	char	buf[PATH_MAX];
	char	*path;
	int		i;

	i = found_name_with_value(tabs->env, "PWD");
	if (i != -1)
	{
		path = getcwd(buf, PATH_MAX);
		if (path)
			change_pwd_value(&tabs->env[i], path);
		else
			strerror(errno);
	}
	else
		return (strerror(errno), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
