/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_len4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:12:45 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:05:06 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	is_plus_neg(long long n, t_options *ptr)
{
	if (n < 0 && ptr->plus == 1 && ptr->sharp == 0)
		return (0);
	else if (n < 0 && ptr->plus == 0 && ptr->sharp == 0)
		return (0);
	else if (n >= 0 && ptr->plus == 0 && ptr->space == 0 && ptr->sharp == 0)
		return (0);
	else if (n >= 0 && ptr->plus == 0 && ptr->space == 1 && ptr->sharp == 0)
		return (1);
	else if (n >= 0 && ptr->plus == 1 && ptr->space == 0 && ptr->sharp == 0)
		return (1);
	else if (n >= 0 && ptr->plus == 1 && ptr->space == 1 && ptr->sharp == 0)
		return (1);
	else if (n != 0 && ptr->sharp == 1)
		return (2);
	return (0);
}

int	is_plus_neg_u(unsigned long n, t_options *ptr)
{
	if (ptr->plus == 0 && ptr->space == 0 && ptr->sharp == 0)
		return (0);
	else if (ptr->plus == 0 && ptr->space == 1 && ptr->sharp == 0)
		return (1);
	else if (ptr->plus == 1 && ptr->space == 0 && ptr->sharp == 0)
		return (1);
	else if (ptr->plus == 1 && ptr->space == 1 && ptr->sharp == 0)
		return (1);
	else if (n > 0 && ptr->sharp == 1)
		return (2);
	return (0);
}
