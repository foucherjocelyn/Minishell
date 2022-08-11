#include "../builtins.h"

int	execute_builtin_env(char **env)
{
	int	i;

	i = 0;
	// if (found_name(env, "PATH") == -1)
	// 	return (perror("minishell: env: "), EXIT_FAILURE);
	while (env[i])
		ft_putendl_fd(env[i++], 1);
	return (EXIT_SUCCESS);
}
