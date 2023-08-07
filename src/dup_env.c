/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:27:48 by clbernar          #+#    #+#             */
/*   Updated: 2023/08/04 13:35:43 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function fills a list with the env at the beiginning
// of the program
void	dup_env(char **envp, t_env **env)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (new == NULL)
			return ;
		fill_t_env(new, envp[i]);
		add_back_to_env(env, new);
		i++;
	}
	if (already_exist(*env, "?") == 1)
		return ;
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return ;
	new->var_name = ft_strdup("?");
	new->var_value = ft_strdup("0");
	new->next = NULL;
	add_back_to_env(env, new);
}

// This function fill an element of the list with a var_env
void	fill_t_env(t_env *new, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	new->var_name = ft_substr(str, 0, i);
	i++;
	new->var_value = ft_substr(str, i, ft_strlen(str) - i);
	new->next = NULL;
}

void	display_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		ft_printf("%s=%s\n", tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
}

void	display_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

// This function duplicates the env in char** from the list
char	**create_env_tab(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	*str;
	char	**env_tmp;

	str = NULL;
	i = 0;
	tmp = env;
	env_tmp = (char **)malloc(sizeof(char *) * (lst_env_size(env) + 1));
	if (env_tmp == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		str = ft_strjoin(tmp->var_name, "=");
		env_tmp[i] = ft_strjoin(str, tmp->var_value);
		i++;
		if (str != NULL)
			free(str);
		tmp = tmp->next;
	}
	env_tmp[i] = NULL;
	return (env_tmp);
}
