/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:02:58 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/21 17:03:35 by bmirlico         ###   ########.fr       */
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
