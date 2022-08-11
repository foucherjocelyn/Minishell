#include "minishell.h"

void	handle_non_interactiv_signals(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}

void	handle_interactiv_signals(int signum)
{
	if (signum == SIGINT)
	{
		// signal(SIGINT, SIG_IGN);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

// void	handle_non_interactiv_signals(int signum)
// {
// 	if (pid != 0)
// 	{
// 		if (signum == SIGINT)
// 		{
// 			rl_on_new_line();
// 			write(1, "\n", 1);
// 		}
// 		if (signum == SIGQUIT)
// 			write(1, "Quit (core dumped)\n", 19);
// 	}
// 	else
// 	{
// 		if (signum == SIGINT)
// 		{
// 			// signal(SIGINT, SIG_IGN);
// 			rl_on_new_line();
// 			write(1, "\n", 1);
// 			rl_redisplay();
// 		}
// 		if (signum == SIGQUIT)
// 			write(1, "\b\b  \b\b", 6);
// 	}
// }

// int	main(void)
// {
// 	while (1)
// 	{
// 		signal(SIGQUIT, &handle_interactiv_signals);
// 		signal(SIGINT, &handle_interactiv_signals);
// 	}
// 	return 0;
// }