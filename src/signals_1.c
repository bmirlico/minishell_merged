/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:07:56 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 15:27:17 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig;

void	signal_action(void)
{
	signal_sigint();
	signal_sigquit();
}

// fonction qui gere le CTRL+C
void	signal_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_ctrlc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

// fonction de signal handler pour le CTRL+C qui permet de cleaner
// readline
void	signal_ctrlc(int sig)
{
	(void)sig;
	if (g_sig != 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_sig = 130;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// fonction qui gere le CTRL+C ds le here_doc
void	signal_sigint_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_ctrlc_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

// fonction de signal handler pour le CTRL+C qui permet de cleaner
// readline
void	signal_ctrlc_heredoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "> ^C\n", 5);
	g_sig = 1;
}
