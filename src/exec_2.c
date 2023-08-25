/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:49:29 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/25 17:05:11 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui wait les child process et recupere l'exit code de la
// derniere commande, et l'affecte a l'env ($?)
void	wait_exit_code(t_pipex vars)
{
	t_command	*tmp;
	int			status;
	int			exit_code;
	char		*str_exit;
	int			i;

	i = 0;
	tmp = *(vars.copy_cmds);
	while (tmp != NULL)
	{
		waitpid(vars.tab_pid[tmp->index], &status, 0);
		if (WIFEXITED(status) && tmp->index == vars.nb_cmds - 1)
		{
			exit_code = WEXITSTATUS(status);
			str_exit = ft_itoa(exit_code);
			if (vars.badsubst_heredoc == 0)
				new_return_value(vars.copy_t_env, str_exit);
			free(str_exit);
		}
		else if (WIFSIGNALED(status))
			handle_signals_in_parent(status, vars, tmp, &i);
		tmp = tmp->next;
	}
}

// fonction qui recupere le path de l'env et le split
// pour préparer l'execution de la commande
void	exec_cmd(t_command *tmp, t_pipex vars)
{
	char	*cmd_with_path;

	if (count_slash(tmp->cmd_args[0]) > 0 || vars.path == NULL)
		cmd_with_path = ft_strdup(tmp->cmd_args[0]);
	else if (tmp->cmd_args[0][0] == '\0')
		cmd_with_path = ft_strdup("");
	else
	{
		cmd_with_path = get_cmd_with_path(tmp->cmd_args[0], vars.paths);
		if (cmd_with_path == NULL)
			cmd_with_path = ft_strdup("");
	}
	handle_exec(cmd_with_path, tmp, vars);
}

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
		perror(cmd_p);
	else
	{
		error = ft_strjoin(tmp->cmd_args[0], ": command not found\n");
		ft_putstr_fd(error, 2);
	}
	if (error != NULL)
		free(error);
	free(cmd_p);
	free_and_exit(vars);
	if (errno == 20)
		exit(126);
	else
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
