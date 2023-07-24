/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:49:29 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/24 22:24:44 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui gere l'execution de la commande et les differents
// cas d'erreurs possibles avec les exit status associes
// ATTENTION A BIEN FREE TOUTES LES LISTES, etc
void	handle_exec(char *cmd_p, t_command *tmp, t_pipex vars)
{
	struct stat	buf;
	char		*error;

	error = NULL;
	if (stat(cmd_p, &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		error = ft_strjoin(cmd_p, ": Is a directory\n");
		ft_putstr_fd(error, 2);
		free(error);
		free(cmd_p);
		free_and_exit(vars);
		exit(126);
	}
	else if (access(cmd_p, F_OK) == -1)
		if_file_unexists(cmd_p, tmp, vars);
	else if (access(cmd_p, F_OK) == 0)
		if_file_exists(cmd_p, tmp, vars);
}

// fonction qui gere le cas ou le fichier n'existe pas
void	if_file_unexists(char *cmd_p, t_command *tmp, t_pipex vars)
{
	char		*error;

	error = NULL;
	if (count_slash(tmp->cmd_args[0]) > 0 || !is_path_set(vars.copy_env_tmp))
	{
		error = ft_strjoin(cmd_p, ": No such file or directory\n");
		ft_putstr_fd(error, 2);
	}
	else
	{
		error = ft_strjoin(tmp->cmd_args[0], ": command not found\n");
		ft_putstr_fd(error, 2);
	}
	free(error);
	free(cmd_p);
	free_and_exit(vars);
	exit(127);
}

// fonction qui gere le cas ou le fichier existe et est executable ou non
void	if_file_exists(char *cmd_p, t_command *tmp, t_pipex vars)
{
	char		*error;

	error = NULL;
	if (access(cmd_p, X_OK) == -1)
	{
		error = ft_strjoin(cmd_p, ": Permission denied\n");
		ft_putstr_fd(error, 2);
		free(error);
		free(cmd_p);
		free_and_exit(vars);
		exit(126);
	}
	else
	{
		execve(cmd_p, tmp->cmd_args, vars.copy_env_tmp);
		free(cmd_p);
		free_and_exit(vars);
		exit(EXIT_FAILURE);
	}
}

void	check_bad_subst_cmd(t_command *tmp, t_pipex vars, t_token **rdirs)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (tmp->cmd_args == NULL)
		return ;
	while (tmp->cmd_args[i] != NULL)
	{
		//printf("%d\n", check_bad_env_variable(tmp->cmd_args[i]));
		if (check_bad_env_variable(tmp->cmd_args[i]) == 2)
		{
			str = ft_strjoin(tmp->cmd_args[i], ": bad substitution\n");
			ft_putstr_fd(str, 2);
			free(str);
			close_rdirs(rdirs, tmp);
			if (vars.nb_pipes > 0)
				close_previous_pipe(vars, tmp->index);
			close_pipe_and_free(vars, tmp->index);
		}
		i++;
	}
}

int	is_bad_subst_cmd(t_command *tmp)
{
	int	i;

	i = 0;
	if (tmp->cmd_args == NULL)
		return (0);
	while (tmp->cmd_args[i] != NULL)
	{
		if (check_bad_env_variable(tmp->cmd_args[i]) == 2)
			return (1);
		i++;
	}
	return (0);
}
