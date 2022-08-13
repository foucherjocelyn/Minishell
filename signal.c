#include "minishell.h"

void	handle_non_interactiv_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		g_status = 130;
	}
	if (signum == SIGQUIT)
	{	
		write(1, "Quit (core dumped)\n", 19);
		g_status = 131;
	}
}

void	handle_interactiv_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}
