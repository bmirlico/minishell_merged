/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:03:06 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/07 21:03:27 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// sous-fonction de strtoll pour check le signe si on tombe sur
// un '-' et passer la norme
void	check_sign(char c, int *i, int *sign)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign *= -1;
		*i += 1;
	}
}

// sous-fonction de strtoll qui affecte LONG_MAX et LONG_MIN
// si on dépasse les bornes long long
void	handle_bounds(int *sign, long long *res)
{
	if (*sign == -1)
		*res = LONG_MIN;
	else
		*res = LONG_MAX;
}
