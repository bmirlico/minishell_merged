/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:44:00 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/20 18:53:19 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// initialise un tableau de nb_pipes
pid_t	**init_pipefd(int nb_pipes)
{
	pid_t	**pipefd;
	int		i;

	pipefd = malloc(sizeof(pid_t *) * nb_pipes);
	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		pipefd[i] = malloc(sizeof(pid_t) * 2);
		if (!pipefd[i])
			return (NULL);
		i++;
	}
	return (pipefd);
}

// initialise un pipe par tour de boucle sur la liste
// (uniquement celui dont on a besoin)
void	init_pipe(t_pipex vars, int j)
{
	if (j < vars.nb_pipes)
	{
		if (pipe(vars.pipefd[j]) == -1)
			perror("error opening pipe");
	}
}

// close le pipe dont on n'a plus besoin et que l'on doit fermer
// pour ne pas que le child en herite au prochain fork
void	close_previous_pipe(t_pipex vars, int j)
{
	if (j >= 1)
	{
		if (close(vars.pipefd[j - 1][0]) < 0
			|| close(vars.pipefd[j - 1][1]) < 0)
			return (perror("error closing previous pipe"));
	}
}

// ferme le pipe ds les childs
// qd il y a un cas d'erreur avec les permissions ou
// un no such file or directory
void	close_pipe(t_pipex vars, int j)
{
	if (close(vars.pipefd[j][0]) < 0
		|| close(vars.pipefd[j][1]) < 0)
		return (perror("error closing pipe"));
}

// fonction qui free le tableau de pipes
void	free_pipefd(pid_t **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
}
