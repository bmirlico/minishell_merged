/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:33:40 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/21 19:26:28 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction d'excution des commandes
// A quel moment vient le syntax error rdir => hypothèse : ds le child process
void	execution(t_pipex vars)
{
	t_command	*tmp;
	char		*cmd;

	tmp = *(vars.copy_cmds);
	cmd = (*(vars.copy_cmds))->cmd_args[0];
	init_struct(&vars);
	while (tmp != NULL)
	{
		open_rdirs(&(tmp->redirections));
		if (tmp->cmd_args != NULL && vars.nb_pipes == 0
			&& is_builtin(tmp->cmd_args[0]))
			exec_builtin(tmp, vars);
		else if (vars.nb_pipes >= 0)
			pipex(tmp, vars, &(tmp->redirections));
		tmp = tmp->next;
	}
	if ((vars.nb_pipes == 0 && !is_builtin(cmd)) || vars.nb_pipes > 0)
		wait_exit_code(vars);
	free_vars(vars);
}

// fonction qui réalise le fork et l'exécution des commandes ds un child process
void	pipex(t_command *tmp, t_pipex vars, t_token **rdirs)
{

	init_pipe(vars, tmp->index);
	vars.tab_pid[tmp->index] = fork();
	if (vars.tab_pid[tmp->index] == -1)
		return (perror("fork"));
	else if (vars.tab_pid[tmp->index] == 0)
		child_process(tmp, vars, rdirs);
	else if (vars.tab_pid[tmp->index] > 0)
	{
		close_previous_pipe(vars, tmp->index);
		close_rdirs(&(tmp->redirections));
	}
}

// fonction qui gere le process child, i.e. redirige les fd et execute la cmd
void	child_process(t_command *tmp, t_pipex vars, t_token **rdirs)
{
	handle_errors_rdirs(tmp, vars, rdirs);
	if (tmp->cmd_args != NULL)
		pipe_redirection(vars, rdirs, tmp->index);
	if (tmp->cmd_args == NULL)
	{
		close_previous_pipe(vars, tmp->index);
		if (tmp->index < vars.nb_pipes)
			close_pipe(vars, tmp->index);
		close_rdirs(rdirs);
		free_and_exit(vars);
		exit(EXIT_SUCCESS);
	}
	if (is_builtin(tmp->cmd_args[0]))
		exec_builtin(tmp, vars);
	else
		exec_cmd(tmp, vars);
}

// fonction qui wait les child process et recupere l'exit code de la 
// derniere commande, et l'affecte a l'env ($?)
void	wait_exit_code(t_pipex vars)
{
	t_command	*tmp;
	int			status;
	int			exit_code;
	char		*str_exit;

	tmp = *(vars.copy_cmds);
	while (tmp != NULL)
	{
		waitpid(vars.tab_pid[tmp->index], &status, 0);
		if (WIFEXITED(status) && tmp->index == vars.nb_cmds - 1)
		{
			exit_code = WEXITSTATUS(status);
			str_exit = ft_itoa(exit_code);
			new_return_value(vars.copy_t_env, str_exit);
			free(str_exit);
			printf("Exit status: %d\n", exit_code);
		}
		tmp = tmp->next;
	}
}

// fonction qui recupere le path de l'env et le split
// pour préparer l'execution de la commande
void	exec_cmd(t_command *tmp, t_pipex vars)
{
	char		*cmd_with_path;

	if (count_slash(tmp->cmd_args[0]) > 0 || vars.path == NULL)
		cmd_with_path = ft_strdup(tmp->cmd_args[0]);
	else
	{
		cmd_with_path = get_cmd_with_path(tmp->cmd_args[0], vars.paths);
		if (cmd_with_path == NULL)
			cmd_with_path = ft_strdup("");
	}
	handle_exec(cmd_with_path, tmp, vars);
}
