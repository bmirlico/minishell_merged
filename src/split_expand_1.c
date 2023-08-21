/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:14:59 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 16:33:11 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_new_tab_size(char **tab)
{
	int		new_size;
	char	**new_tab;
	int		i;

	i = 0;
	new_size = 0;
	new_tab = NULL;
	while (tab != NULL && tab[i])
	{
		if (nb_quotes(tab[i]) == 0)
		{
			new_tab = ft_split(tab[i], ' ');
			new_size += get_len_tab(new_tab);
		}
		else
			new_size++;
		if (new_tab != NULL)
		{
			free_tab(new_tab);
			new_tab = NULL;
		}
		i++;
	}
	return (new_size);
}

int	fill_new_split_tab(char **tab, char ***new, int index, int size)
{
	int	i;

	i = 0;
	(void)size;
	while (tab[i] != NULL && index < size)
	{
		(*new)[index] = ft_strdup(tab[i]);
		index++;
		i++;
	}
	return (index);
}

int	fill_new_str_alone(int index, char *str, char ***new)
{
	(*new)[index] = ft_strdup(str);
	index++;
	return (index);
}

void	replace_split_tab(t_command *tmp)
{
	int		i;
	char	**new;
	char	**temp;
	int		k;

	init_split_tab(&new, &temp, &i, &k);
	new = ft_calloc(sizeof(char *), count_new_tab_size(tmp->cmd_args) + 1);
	if (new == NULL)
		return ;
	while (tmp->cmd_args[i])
	{
		if (nb_quotes(tmp->cmd_args[i]) == 0)
		{
			temp = ft_split(tmp->cmd_args[i], ' ');
			k = fill_new_split_tab(temp, &new, k,
					count_new_tab_size(tmp->cmd_args));
		}
		else
			k = fill_new_str_alone(k, tmp->cmd_args[i], &new);
		free_temp_and_increment(&i, &temp);
	}
	new[k] = NULL;
	free_tab(tmp->cmd_args);
	tmp->cmd_args = new;
}

void	split_after_expand(t_command **cmds)
{
	t_command	*tmp;

	tmp = *cmds;
	while (tmp != NULL)
	{
		if (count_new_tab_size(tmp->cmd_args) != get_len_tab(tmp->cmd_args))
			replace_split_tab(tmp);
		tmp = tmp->next;
	}
}
