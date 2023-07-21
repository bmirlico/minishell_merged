/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:46:59 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/21 20:41:52 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui check si la commande est un builtin ou pas
int	is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len + 1) || !ft_strncmp(cmd, "cd", len + 1)
		|| !ft_strncmp(cmd, "pwd", len + 1)
		|| !ft_strncmp(cmd, "export", len + 1)
		|| !ft_strncmp(cmd, "unset", len + 1)
		|| !ft_strncmp(cmd, "env", len + 1)
		|| !ft_strncmp(cmd, "exit", len + 1))
		return (1);
	else
		return (0);
}

// Fonction qui appelle les fonctions d'execution
// des builtins
// MODIFIER LES BUILTIN EN RAJOUTANT LES EXIT CODE ET EN RAJOUTANT EN PARAMETRE LA STRUCTURE VARS
void	exec_builtin(t_command *tmp, t_pipex vars)
{
	int		len;
	int		old_stdout;

	len = ft_strlen(tmp->cmd_args[0]);
	if (vars.nb_pipes == 0)
		builtin_redirection(&old_stdout, tmp, vars);
	builtins(len, tmp, vars);
	if (vars.nb_pipes == 0)
	{
		if (dup2(old_stdout, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		if (close(old_stdout) < 0)
			exit(EXIT_FAILURE);
	}
}

void	builtin_redirection(int *old_stdout, t_command *tmp, t_pipex vars)
{
	int		ret;
	t_token	*last_outfile;

	*old_stdout = dup(1);
	ret = errors_rdirs_builtin_alone(tmp, vars);
	last_outfile = get_last_outfile(&(tmp->redirections));
	if (last_outfile != NULL && ret == 0)
	{
		if (dup2(last_outfile->fd, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
	}
	close_rdirs(&(tmp->redirections));
}

// Gestion des cas d'erreur de redirections ds le cas d'un BUILTIN SEUL
int	errors_rdirs_builtin_alone(t_command *tmp, t_pipex vars)
{
	t_token	*temp;

	temp = tmp->redirections;
	while (temp != NULL)
	{
		if ((temp->type == T_INFILE || temp->type == T_LIMITOR)
			&& ((temp->fd < 0 && access(temp->str, F_OK) == -1)
				|| (temp->fd < 0)))
		{
			perror(temp->str);
			new_return_value(vars.copy_t_env, "1");
			return (1);
		}
		else if ((temp->type == T_OUTFILE || temp->type == T_OUTFILE_APPEND)
			&& temp->fd < 0)
		{
			perror(temp->str);
			new_return_value(vars.copy_t_env, "1");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

// fonction qui appelle les fonctions d'execution de builtin
void	builtins(int len, t_command *tmp, t_pipex vars)
{
	if (!ft_strncmp(tmp->cmd_args[0], "cd", len + 1))
		built_in_cd(tmp);
	else if (!ft_strncmp(tmp->cmd_args[0], "pwd", len + 1))
		built_in_pwd();
	else if (!ft_strncmp(tmp->cmd_args[0], "exit", len + 1))
		built_in_exit(tmp);
	else if ((!ft_strncmp(tmp->cmd_args[0], "env", len + 1)))
		built_in_env(tmp, vars);
	else if ((!ft_strncmp(tmp->cmd_args[0], "unset", len + 1)))
		built_in_unset(tmp, vars.copy_t_env);
	else if ((!ft_strncmp(tmp->cmd_args[0], "export", len + 1)))
		built_in_export(tmp, vars.copy_t_env);
	else if ((!ft_strncmp(tmp->cmd_args[0], "echo", len + 1)))
		built_in_echo(tmp, vars.copy_t_env);
}
