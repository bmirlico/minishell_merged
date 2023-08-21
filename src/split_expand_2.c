/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:33:03 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 16:33:37 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_split_tab(char ***new, char ***temp, int *i, int *k)
{
	*new = NULL;
	*temp = NULL;
	*i = 0;
	*k = 0;
}

void	free_temp_and_increment(int *i, char ***temp)
{
	if (*temp != NULL)
		free_tab(*temp);
	*temp = NULL;
	*i += 1;
}
