/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:19 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/15 19:03:44 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui ouvre les redirections s'il y en a
void	open_rdirs(t_token **redirections, t_command *tmpc, t_pipex vars)
{
	t_token	*tmp;

	tmp = *redirections;
	while (tmp != NULL)
	{
		if ((tmp->type == T_INFILE || tmp->type == T_OUTFILE
				|| tmp->type == T_OUTFILE_APPEND)
			&& (check_bad_env_variable(tmp->str) == 2 || tmp->str[0] == '\0'
				|| !ft_strncmp(tmp->str, "\"\"", 3)))
		{
			tmp->fd = -2;
			return ;
		}
		handle_open_rdirs(tmp, tmpc, vars);
		tmp = tmp->next;
	}
}

void	handle_open_rdirs(t_token *tmp, t_command *tmpc, t_pipex vars)
{
	(void)tmpc;
	(void)vars;
	if (tmp->type == T_INFILE)
		tmp->fd = open(tmp->str, O_RDONLY, S_IRUSR);
	else if (tmp->type == T_OUTFILE)
		tmp->fd = open(tmp->str, O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
	else if (tmp->type == T_OUTFILE_APPEND)
		tmp->fd = open(tmp->str, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR);
	// else if (tmp->type == T_LIMITOR)
	// {
	// 	tmp->fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC,
	// 			S_IRUSR | S_IWUSR);
	// 	fill_heredoc(tmp, tmpc, vars);
	// }
}

// fonction appelée ds le child process qui permet de gére les erreurs de rdir
// i.e. les open qui ont échoué (ou le ambiguous redirect, voir avec Clément)
void	handle_errors_rdirs(t_command *tmpc, t_pipex vars, t_token **rdirs)
{
	t_token	*tmp;

	tmp = *rdirs;
	while (tmp != NULL)
	{
		if ((tmp->type == T_INFILE || tmp->type == T_LIMITOR)
			&& ((tmp->fd != -3) && ((tmp->fd < 0 && access(tmp->str, F_OK) == -1)
					|| (tmp->fd < 0))))
			check_error_rdirs(tmpc, vars, tmp, rdirs);
		else if ((tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
			&& tmp->fd != -3 && tmp->fd < 0)
			check_error_rdirs(tmpc, vars, tmp, rdirs);
		tmp = tmp->next;
	}
}

void	check_error_rdirs(t_command *tmpc, t_pipex vars, t_token *tmp,
			t_token **rdirs)
{
	char	*error;

	error = NULL;
	if (check_bad_env_variable(tmp->str) == 2)
	{
		error = ft_strjoin(tmp->str, ": bad substitution\n");
		ft_putstr_fd(error, 2);
		free(error);
	}
	else if (tmp->str[0] == '\0')
		ft_putstr_fd("Ambiguous redirect\n", 2);
	else if (!ft_strncmp(tmp->str, "\"\"", 3))
		ft_putstr_fd(" : No such file or directory\n", 2);
	else
		perror(tmp->str);
	close_rdirs(rdirs, tmpc);
	if (vars.nb_pipes > 0)
		close_previous_pipe(vars, tmpc->index);
	close_pipe_and_free(vars, tmpc->index);
}

// fonction qui ferme le pipe et free le tab de pipes
// en cas d'erreur sur les rdirs (no such file or directory
// ou permission denied)
void	close_pipe_and_free(t_pipex vars, int index)
{
	if (index < vars.nb_pipes)
		close_pipe(vars, index);
	free_and_exit(vars);
	exit(EXIT_FAILURE);
}
