/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:37:00 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/28 12:51:31 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui reset les signaux SIGINT ET SIGQUIT
void	reset_signal(t_pipex vars)
{
	reset_sigint();
	reset_sigquit(vars);
}

// fonction qui reset SIGINT
void	reset_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_ctrlc_cmd;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

// fonction qui reset SIGQUIT
void	reset_sigquit(t_pipex vars)
{
	struct sigaction	sa;
	struct termios		new_attributes;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	new_attributes = vars.original_attributes;
	new_attributes.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_attributes);
}
