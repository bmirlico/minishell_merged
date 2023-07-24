/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_post_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:10:26 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/24 20:01:12 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function replaces a char ** by a copy of a copy whithout empty lines
char	**replace_tab(char **tab, int new_len)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	j = 0;
	new_tab = (char **)malloc(sizeof(char *) * (new_len + 1));
	if (new_tab == NULL)
		return (NULL);
	while (tab[i])
	{
		if (tab[i][0] != '\0')
			new_tab[j++] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[j] = NULL;
	free_tab(tab);
	return (new_tab);
}

// This function clean the command list by removing the empty string
// in each tab args
void	clean_lst(t_command *cmds)
{
	t_command	*tmp;
	char		**tab_tmp;
	int			new_len;

	tmp = cmds;
	while (tmp != NULL)
	{
		tab_tmp = tmp->cmd_args;
		new_len = get_len_tab(tab_tmp) - get_nb_empty(tab_tmp);
		if (get_nb_empty(tab_tmp) != 0)
			tmp->cmd_args = replace_tab(tab_tmp, new_len);
		tmp = tmp->next;
	}
}
