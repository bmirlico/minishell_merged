/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:26 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/10 17:47:17 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function removes the var_env (name) from the env_list
void	unset(t_env *env, char *name)
{
	t_env	*tmp;
	t_env	*previous;
	int		i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, name, ft_strlen(name) + 1) == 0)
		{
			if (i == 0)
				delete_first(env);
			else
			{
				previous->next = tmp->next;
				free(tmp->var_name);
				free(tmp->var_value);
				free(tmp);
			}
			break ;
		}
		previous = tmp;
		tmp = tmp->next;
		i++;
	}
}

// This function unset the fist element of the env_list
void	delete_first(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	env = tmp->next;
	free(tmp->var_name);
	free(tmp->var_value);
	free(tmp);
}

void	built_in_unset(t_command *cmd, t_env *env)
{
	int		i;

	// Gestion des rdirs en cas de unset seul
	i = 1;
	if (get_len_tab(cmd->cmd_args) > 1)
	{
		while (cmd->cmd_args[i] != NULL)
		{
			if (ft_strncmp(cmd->cmd_args[i], "?", ft_strlen("?") + 1) != 0)
				unset(env, cmd->cmd_args[i]);
			i++;
		}
	}
	new_return_value(env, "0");
}
