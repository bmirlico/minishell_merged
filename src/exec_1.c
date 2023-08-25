/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:33:40 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/25 16:29:56 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction d'excution des commandes
// A quel moment vient le syntax error rdir => hypothèse : ds le child process
void	execution(t_pipex vars)
{
	t_command	*tmp;
	char		*cmd;
	int			ret;

	tmp = *(vars.copy_cmds);
	init_execution(tmp, &cmd, &ret, &vars);
	open_heredocs(&vars);
	if (g_sig == 1 || vars.badsubst_heredoc > 0)
	{
		signal_x_badsubst(vars);
		if (g_sig == 1)
			return ;
	}
	while (tmp != NULL)
	{
		if (!is_bad_subst_cmd(tmp) && g_sig != 1)
			ret = open_rdirs(&(tmp->redirections), tmp, vars);
		if (ret == 1)
			return ;
		do_execution(tmp, vars);
		tmp = tmp->next;
	}
	if ((vars.nb_pipes == 0 && !is_builtin(cmd)) || vars.nb_pipes > 0)
		wait_exit_code(vars);
	free_vars(vars);
}

// fonction pour la norme
void	init_execution(t_command *tmp, char **cmd, int *ret, t_pipex *vars)
{
	*ret = 0;
	if (tmp->cmd_args != NULL)
		*cmd = tmp->cmd_args[0];
	else
		*cmd = NULL;
	init_struct(vars);
}

// fonction pour la norme, qui regroupe la partie d'execution
// ds le cas d'un builtin seul ou bien d'un builtin / commmande ds un pipe
// et commande seule
void	do_execution(t_command	*tmp, t_pipex vars)
{
	if (tmp->cmd_args != NULL && vars.nb_pipes == 0
		&& is_builtin(tmp->cmd_args[0]))
		exec_builtin(tmp, vars);
	else if (vars.nb_pipes >= 0)
		pipex(tmp, vars, &(tmp->redirections));
}

// fonction qui réalise le fork et l'exécution des commandes ds un child process
void	pipex(t_command *tmp, t_pipex vars, t_token **rdirs)
{
	ignore_signal();
	init_pipe(vars, tmp->index);
	vars.tab_pid[tmp->index] = fork();
	if (vars.tab_pid[tmp->index] == -1)
		return (perror("fork"));
	else if (vars.tab_pid[tmp->index] == 0)
		child_process(tmp, vars, rdirs);
	else if (vars.tab_pid[tmp->index] > 0)
	{
		close_previous_pipe(vars, tmp->index);
		close_rdirs(&(tmp->redirections), tmp);
	}
}

// fonction qui gere le process child, i.e. redirige les fd et execute la cmd
void	child_process(t_command *tmp, t_pipex vars, t_token **rdirs)
{
	reset_signal(vars);
	check_bad_subst_cmd(tmp, vars, rdirs);
	handle_errors_rdirs(tmp, vars, rdirs);
	if (tmp->cmd_args != NULL)
		pipe_redirection(vars, tmp);
	if (get_len_tab(tmp->cmd_args) == 0)
	{
		close_previous_pipe(vars, tmp->index);
		if (tmp->index < vars.nb_pipes)
			close_pipe(vars, tmp->index);
		close_rdirs_heredocs(vars);
		close_rdirs(rdirs, tmp);
		free_and_exit(vars);
		exit(EXIT_SUCCESS);
	}
	if (is_builtin(tmp->cmd_args[0]))
		exec_builtin(tmp, vars);
	else
		exec_cmd(tmp, vars);
}
