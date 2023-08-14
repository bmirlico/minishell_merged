/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:27:11 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/14 21:05:57 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui ferme les redirections
void	close_rdirs(t_token **redirections, t_command *tmp)
{
	t_token	*temp;

	temp = *redirections;
	if (is_bad_subst_cmd(tmp))
		return ;
	while (temp != NULL)
	{
		if (temp->type == T_INFILE || temp->type == T_OUTFILE
			|| temp->type == T_OUTFILE_APPEND || temp->type == T_LIMITOR)
		{
			if (check_bad_env_variable(temp->str) == 2 || temp->str[0] == '\0')
				return ;
			if (temp->fd >= 0)
				close(temp->fd);
		}
		temp = temp->next;
	}
}

// fonction qui remplit le fichier tmp/here_doc avec le contenu du heredoc
void	fill_heredoc(t_token *tmp, t_command *tmpc, t_pipex vars)
{
	char	*str;
	int		fd_tmp;
	int		old_stdin;

	init_vars_heredoc(&fd_tmp, &old_stdin);
	signal_sigint_heredoc();
	while (1)
	{
		str = readline("> ");
		if (g_sig == 1)
		{
			printf("OK\n");
			close_heredoc_sigint(fd_tmp, old_stdin, tmpc);
			new_return_value(vars.copy_t_env, "130");
			return ;
		}
		else if (str == NULL)
			handle_ctrld(fd_tmp, vars, tmpc, old_stdin);
		else if (!ft_strncmp(str, tmp->str, ft_strlen(tmp->str) + 1))
		{
			close_heredoc_(fd_tmp, tmpc, old_stdin);
			return ;
		}
		ft_putstr_fd(str, fd_tmp);
		free(str);
	}
}

void	close_heredoc_sigint(int fd_tmp, int old_stdin, t_command *tmpc)
{
	close(fd_tmp);
	unlink("/tmp/here_doc");
	close_rdirs(&(tmpc->redirections), tmpc);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
}

void	close_heredoc_(int fd_tmp, t_command *tmpc, int old_stdin)
{
	close(fd_tmp);
	close(old_stdin);
	unlink("/tmp/here_doc");
	close_rdirs(&(tmpc->redirections), tmpc);
}

void	handle_ctrld(int fd_tmp, t_pipex vars, t_command *tmpc,
			int old_stdin)
{
	close_heredoc_(fd_tmp, tmpc, old_stdin);
	free_and_exit(vars);
	ft_printf("exit\n");
	exit (0);
}
