/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:02:58 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 14:23:17 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui free uniquement les elements de la structure vars hors listes
void	free_pipex(t_pipex vars)
{
	free_pipefd(vars.pipefd, vars.nb_pipes);
	if (vars.path != NULL)
	{
		free(vars.path);
		free_tab(vars.paths);
	}
	free(vars.tab_pid);
	free_tab(vars.copy_env_tmp);
	free_envlst(&(vars.copy_t_env));
}

// fonction qui free la structure vars ds le parent process
void	free_vars(t_pipex vars)
{
	free_pipefd(vars.pipefd, vars.nb_pipes);
	if (vars.path != NULL)
	{
		free(vars.path);
		free_tab(vars.paths);
	}
	free(vars.tab_pid);
	free_tab(vars.copy_env_tmp);
}

void	init_vars_heredoc(int *fd_tmp, int *old_stdin)
{
	*fd_tmp = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	*old_stdin = dup(0);
}

// fonction qui regroupe les vars du heredoc, et la gestion des signaux
// pour la norme
void	set_heredoc(int *fd_tmp, int *old_stdin)
{
	init_vars_heredoc(fd_tmp, old_stdin);
	signal_sigint_heredoc();
}

// FONCTION QUI PERMET D'INITIALISER LES FDS avant meme d'ouvrir les rdirs
// et empeche d'avoir un conditional move (ex d'erreur qu'on avait avec
// << ok > ol)
void	init_fds(t_command **cmds)
{
	t_command	*tmp;
	t_token		*temp;

	tmp = *cmds;
	while (tmp != NULL)
	{
		temp = tmp->redirections;
		while (temp != NULL)
		{
			temp->fd = -3;
			temp = temp->next;
		}
		tmp = tmp->next;
	}
}
