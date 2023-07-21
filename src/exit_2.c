/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:53:28 by bmirlico          #+#    #+#             */
/*   Updated: 2023/06/27 15:04:13 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction similaire à atoi, sauf qu'elle check en plus si
// l'entier résultat ne dépasse LONG_MIN et LONG_MAX
long long	ft_strtoll(const char *nptr)
{
	int			i;
	int			sign;
	long long	res;
	int			digit;

	init_strtoll(&i, &sign, &res, &digit);
	if (!nptr)
		return (res * sign);
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	check_sign(nptr[i], &i, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - 48;
		if ((sign && res > (LONG_MAX - digit) / 10)
			|| (sign == -1 && res < (LONG_MIN - digit) / 10))
		{
			handle_bounds(&sign, &res);
			break ;
		}
		res = res * 10 + digit;
		i++;
	}
	return (res * sign);
}

// sous-fonction de strtoll pour initialiser les variables
// et passer la norme
void	init_strtoll(int *i, int *sign, long long *res, int *digit)
{
	*i = 0;
	*sign = 1;
	*res = 0;
	*digit = 0;
}

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
