/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:40:08 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/18 13:48:31 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// returns the size of the env list
int	lst_env_size(t_env *env)
{
	int		size;
	t_env	*tmp;

	tmp = env;
	size = 0;
	if (!tmp)
		return (0);
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

// Add a list element to the env list
void	add_back_to_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
		*env = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_envlst(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (*env != NULL)
	{
		tmp = (*env)->next;
		if ((*env)->var_name != NULL)
			free((*env)->var_name);
		if ((*env)->var_value != NULL)
			free((*env)->var_value);
		free(*env);
		*env = tmp;
	}
}

// This functions changes the return_value stocked in the env_list
void	new_return_value(t_env *env, char *return_value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, "?", 1) == 0)
		{
			if (tmp->var_value != NULL)
				free(tmp->var_value);
			tmp->var_value = ft_strdup(return_value);
			return ;
		}
		tmp = tmp->next;
	}
}
