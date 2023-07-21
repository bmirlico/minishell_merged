/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:19 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/21 17:56:06 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui ouvre les redirections s'il y en a
void	open_rdirs(t_token **redirections)
{
	t_token	*tmp;

	tmp = *redirections;
	while (tmp != NULL)
	{
		if (tmp->type == T_INFILE)
			tmp->fd = open(tmp->str, O_RDONLY, S_IRUSR);
		else if (tmp->type == T_OUTFILE)
			tmp->fd = open(tmp->str, O_RDWR | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR);
		else if (tmp->type == T_OUTFILE_APPEND)
			tmp->fd = open(tmp->str, O_RDWR | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR);
		else if (tmp->type == T_LIMITOR)
		{
			tmp->fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR);
			fill_heredoc(tmp);
		}
		tmp = tmp->next;
	}
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
			&& ((tmp->fd < 0 && access(tmp->str, F_OK) == -1) || (tmp->fd < 0)))
		{
			perror(tmp->str);
			close_rdirs(rdirs);
			close_pipe_and_free(vars, tmpc->index);
		}
		else if ((tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
			&& tmp->fd < 0)
		{
			perror(tmp->str);
			close_rdirs(rdirs);
			if (vars.nb_pipes > 0)
				close_previous_pipe(vars, tmpc->index);
			close_pipe_and_free(vars, tmpc->index);
		}
		tmp = tmp->next;
	}
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

// fonction qui ferme les redirections
void	close_rdirs(t_token **redirections)
{
	t_token	*tmp;

	tmp = *redirections;
	while (tmp != NULL)
	{
		if (tmp->type == T_INFILE || tmp->type == T_OUTFILE
			|| tmp->type == T_OUTFILE_APPEND || tmp->type == T_LIMITOR)
		{
			if (tmp->fd >= 0)
				close(tmp->fd);
		}
		tmp = tmp->next;
	}
}

// fonction qui remplit le fichier tmp/here_doc avec le contenu du heredoc
void	fill_heredoc(t_token *tmp)
{
	char	*str;
	char	*limitor;
	int		fd_tmp;

	fd_tmp = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	limitor = ft_strjoin(tmp->str, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (str == NULL || !ft_strncmp(str, limitor, ft_strlen(limitor) + 1))
		{
			free(str);
			free(limitor);
			close(fd_tmp);
			unlink("/tmp/here_doc");
			return ;
		}
		ft_putstr_fd(str, fd_tmp);
		free(str);
	}
	free(limitor);
}
