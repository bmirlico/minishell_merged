/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:27:22 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 15:27:33 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui gere le CTRL+backslash 
void	signal_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_signals_in_parent(int status, t_pipex vars,
			t_command	*tmp, int *i)
{
	int	term_signal;

	term_signal = WTERMSIG(status);
	if (term_signal == SIGQUIT && tmp->next == NULL)
	{
		ft_printf("Quit (core dumped)\n");
		new_return_value(vars.copy_t_env, "131");
		g_sig = 131;
	}
	else if (term_signal == SIGINT)
	{
		if (*i == 0)
			ft_printf("\n");
		if (tmp->next == NULL)
		{
			new_return_value(vars.copy_t_env, "130");
			g_sig = 130;
		}
		*i += 1;
	}
}
