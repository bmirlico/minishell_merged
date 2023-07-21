/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:13:53 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/13 16:15:34 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui remplit mon tableau de tableaux temporaire
// de ma fonction fill_tab_free
void	fill_in_tmp(char **dest, char **src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}

// fonction qui free les string precedentes pour la protection de malloc
void	free_previous_str(char **tab, int i)
{
	while (i >= 0)
		free(tab[--i]);
	free(tab);
}

// fonction qui renvoie la longueur de mon tableau de tableaux
// la longueur est utilisee ds ma fonction fill_tab_free pour remplir
// tableau temporaire des valeurs precedentes du tableau de tableaux
int	get_len_tab(char **tab)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (tab == NULL)
		return (len);
	while (tab[i] != NULL)
	{
		len++;
		i++;
	}
	return (len);
}

// fonction qui free le tableau de commandes
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
