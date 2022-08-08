#include "minishell.h"

void	handle_interactiv_signals(int signum)
{
	if (signum == SIGINT)
		rl_on_new_line();
	if (signum == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}