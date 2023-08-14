/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:53:28 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/14 13:09:41 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui gere le cas "non numeric" de exit
// fait pour la norme
void	exit_out_bounds(char *error_str, char *str, t_pipex vars)
{
	exit_non_numeric(&error_str, str);
	ft_putstr_fd(error_str, 2);
	free(error_str);
	free_and_exit(vars);
	exit(2);
}

// fonction qui gere le cas "too many arguments" de exit
// fait pour la norme
void	exit_too_many_args(t_pipex vars)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
	new_return_value(vars.copy_t_env, "1");
	if (vars.nb_pipes > 0)
	{
		free_and_exit(vars);
		exit(EXIT_FAILURE);
	}
}

// fonction qui gere les cas "valides" de exit
// fait pour la norme
void	exit_normal_cases(int exit_code, t_pipex vars)
{
	if (!(exit_code >= 0 && exit_code <= 255))
		exit_code %= 256;
	free_and_exit(vars);
	exit(exit_code);
}

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
