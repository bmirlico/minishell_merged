/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:52:55 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 15:54:12 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
