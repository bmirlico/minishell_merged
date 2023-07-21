/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_rdir_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:21:38 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/18 15:15:49 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui gere la partie redirection outfiles pour les commandes
// intermédiaires d'un pipe (entre la 1ere et la derniere)
void	pipe_between_outfile(t_token *last_outfile, t_pipex vars, int i)
{
	if (last_outfile != NULL)
	{
		if (dup2(last_outfile->fd, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	else if (!last_outfile && vars.nb_pipes > 0)
	{
		if (dup2(vars.pipefd[i][1], STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
}

// fonction d'initialisation du last infile et du last outfile
void	init_last_rdirs(t_token **last_infile, t_token **last_outfile,
			t_token **rdirs)
{
	*last_infile = get_last_infile(rdirs);
	*last_outfile = get_last_outfile(rdirs);
}

// fonction qui renvoie le dernier infile (celui sur lequel on va rediriger
// l'entree de la commande)
t_token	*get_last_infile(t_token **rdirs)
{
	t_token	*tmp;
	t_token	*last;

	tmp = *rdirs;
	last = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == T_INFILE || tmp->type == T_LIMITOR)
			last = tmp;
		tmp = tmp->next;
	}
	return (last);
}

// fonction qui renvoie le dernier outfile (celui sur lequel on va rediriger
// la sortie de la commande)
t_token	*get_last_outfile(t_token **rdirs)
{
	t_token	*tmp;
	t_token	*last;

	tmp = *rdirs;
	last = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
			last = tmp;
		tmp = tmp->next;
	}
	return (last);
}
