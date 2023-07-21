/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:40:26 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/21 20:39:45 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function diplays the env
void	built_in_env(t_command *tmp, t_pipex vars)
{
	if (get_len_tab(tmp->cmd_args) != 1)
	{
		ft_putstr_fd("env must take no options or arguments\n", 2);
		new_return_value(vars.copy_t_env, "1");
		if (vars.nb_pipes > 0)
		{
			free_and_exit(vars);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (tmp)
			display_tab(vars.copy_env_tmp);
		new_return_value(vars.copy_t_env, "0");
		if (vars.nb_pipes > 0)
		{	
			free_and_exit(vars);
			exit(EXIT_SUCCESS);
		}
	}
}
