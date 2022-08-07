#include "../builtins.h"

static int	display_export_error(int error_count, char *error)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	error_count++;
	return (error_count);
}

static int	check_args(char **to_export, t_tab *tabs, int j, int error_count)
{
	int	i;

	if (to_export[0] && !to_export[1])
		return (display(tabs->exp), EXIT_FAILURE);
	while (to_export[j])
	{
		if (ft_isalpha(to_export[j][0]) == EXIT_SUCCESS &&
			to_export[j][0] != '_')
		{
			error_count = display_export_error(error_count, to_export[j++]);
			continue ;
		}
		i = -1;
		while (to_export[j][++i] && to_export[j][i] != '=')
		{
			if (ft_isalnum(to_export[j][i]) == EXIT_SUCCESS &&
				to_export[j][i] != '_'/* && to_export[j][i] != '='*/)
			{	
				error_count = display_export_error(error_count, to_export[j]);
				break ;
			}
		}
		j++;
	}
	return (error_count);
}

static void	change_value(char **to_change, char *to_export)
{
	int	i;

	i = 0;
	while (to_export[i])
	{
		(*to_change)[i] = to_export[i];
		i++;
	}
	(*to_change)[i] = '\0';
	// display(to_change);
}

char	*to_find(char *to_change)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(ft_strlen(to_change) + 1);
	if (!res)
		return (printf("Malloc failed, can't change the value of %s\n",
			to_change), NULL);
	while (to_change[++i] != '=')
		res[i] = to_change[i];
	res[i] = 0;
	return (res);
}

int	execute_builtin_export(t_tab *tabs, char **to_export)
{
	int		index[4];
	char	*to_free;

	if (check_args(to_export, tabs, 1, 0))
		return (EXIT_FAILURE);
	index[1] = 1;
	while (to_export[index[1]])
	{
		index[0] = len_env(tabs->env);
		index[3] = len_env(tabs->exp);
		index[2] = 0;
		if (found_name(tabs->exp, to_export[index[1]]) != -1)
		{
			index[1]++;
			continue ;
		}
		else if (found_export_name_with_value(tabs->exp, to_export[index[1]]) != -1)
		{
			// printf("ca rentre\n\n\n%d\n\n\n", found_export_name_with_value(tabs->exp, to_export[index[1]]));
			change_value(&tabs->exp[found_export_name_with_value(tabs->exp, to_export[index[1]])], to_export[index[1]]);
			// display(tabs->env);
			to_free = to_find(to_export[index[1]]);
			if (!to_free)
				return (EXIT_FAILURE);
			if (found_name(tabs->env, to_free) != -1)
				change_value(&tabs->env[found_export_name_with_value(tabs->env, to_export[index[1]])], to_export[index[1]]);
			else
				tabs->env[index[0]++] = ft_strdup(to_export[index[1]]);
			free(to_free);
		}
		else
		{
			while (to_export[index[1]][index[2]])
			{
				if (to_export[index[1]][index[2]] == '=')
					break ;
				index[2]++;
			}
			if (to_export[index[1]][index[2]] == '=')
				tabs->env[index[0]++] = ft_strdup(to_export[index[1]]);
			tabs->exp[index[3]++] = ft_strdup(to_export[index[1]]);
		}
		tabs->env[index[0]++] = NULL;
		tabs->exp[index[3]++] = NULL;
		index[1]++;
	}
	return (EXIT_SUCCESS);
}