/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_len3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:08:56 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:05:25 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	calcul_len_s_right(t_options *ptr, int len_str)
{
	int	len;
	int	min;

	len = len_str;
	min = (int)ft_min(ptr->precision, len_str);
	if (ptr->width == 0 && ptr->point == 1 && ptr->precision == 0)
		len = ptr->precision;
	else if (ptr->width == 0 && ptr->point == 1 && ptr->precision > 0)
		len = (int)min;
	else if (ptr->width > 0 && ptr->point == 1 && ptr->precision >= 0)
		len = ft_max(ptr->width, (int)min);
	else if (ptr->width > 0)
		len = ft_max(ptr->width, len_str);
	return (len);
}

size_t	ft_max(int a, int b)
{
	int	max;

	max = a;
	if (b > a)
		max = b;
	return (max);
}

size_t	ft_min(int a, int b)
{
	size_t	min;

	min = a;
	if (a > b)
		min = b;
	return (min);
}

int	is_neg(long long n)
{
	if (n < 0)
		return (1);
	return (0);
}

int	is_zero(long long n)
{
	if (n == 0)
		return (1);
	return (0);
}
