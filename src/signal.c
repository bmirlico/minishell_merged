/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:07:56 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/26 17:27:56 by bmirlico         ###   ########.fr       */
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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 130;
}

// fonction qui gere le CTRL+backslash 
void	signal_sigquit(void)
{
	struct sigaction	sa;
	struct termios		original_attributes;
	struct termios		new_attributes;

	tcgetattr(0, &original_attributes);
	new_attributes = original_attributes;
	new_attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_attributes);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	//tcsetattr(STDIN_FILENO, TCSANOW, &original_attributes);
}
