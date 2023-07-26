/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:19 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/26 15:18:49 by bmirlico         ###   ########.fr       */
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
			fill_heredoc(tmp, tmpc, vars);
		}
		tmp = tmp->next;
	}
}

// fonction appelée ds le child process qui permet de gére les erreurs de rdir
// i.e. les open qui ont échoué (ou le ambiguous redirect, voir avec Clément)
void	handle_errors_rdirs(t_command *tmpc, t_pipex vars, t_token **rdirs)
{
	t_token	*tmp;
	char	*error;

	tmp = *rdirs;
	error = NULL;
	while (tmp != NULL)
	{
		if ((tmp->type == T_INFILE || tmp->type == T_LIMITOR)
			&& ((tmp->fd < 0 && access(tmp->str, F_OK) == -1) || (tmp->fd < 0)) )
		{
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
		else if ((tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
			&& tmp->fd < 0)
		{
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
			if (str == NULL)
			{
				close_rdirs(&(tmpc->redirections), tmpc);
				free_and_exit(vars);
				ft_printf("\nexit\n");
				exit (0);
			}
			else
				return ;
		}
		ft_putstr_fd(str, fd_tmp);
		free(str);
	}
	free(limitor);
}
