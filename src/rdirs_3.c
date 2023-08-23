/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:38:21 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/23 17:06:01 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_in_heredoc(char **str, int fd_tmp)
{
	*str = ft_strfjoin(*str, "\n");
	ft_putstr_fd(*str, fd_tmp);
	free(*str);
}

void	close_heredoc_sigint(int fd_tmp, int old_stdin, t_command *tmpc)
{
	close(fd_tmp);
	unlink("/tmp/here_doc");
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	(void)tmpc;
}

void	close_heredoc_(int fd_tmp, t_command *tmpc, int old_stdin)
{
	close(fd_tmp);
	close(old_stdin);
	unlink("/tmp/here_doc");
	(void)tmpc;
}

void	handle_ctrld(int fd_tmp, t_pipex vars, t_command *tmpc,
			int old_stdin)
{
	close_heredoc_(fd_tmp, tmpc, old_stdin);
	free_and_exit(vars);
	ft_printf("exit\n");
	exit (0);
}

int	is_varenv_in_single_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && var_env_declaration_heredoc(str, i) == 0)
			return (0);
		i++;
	}
	return (1);
}
