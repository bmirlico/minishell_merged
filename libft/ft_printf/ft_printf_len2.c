/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_len2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:05:45 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:05:30 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	calcul_len_d(t_options *ptr, int count_arg, long long n)
{
	int	flagp;
	int	len_pr;
	int	len_d;

	flagp = is_plus_neg(n, ptr);
	len_pr = ft_max(ptr->precision + is_neg(n) + flagp, count_arg + flagp);
	len_d = ft_max(ptr->width, len_pr);
	return (len_d);
}

int	calcul_len_u(t_options *ptr, int count_arg, unsigned long n)
{
	int	flagp;
	int	len_pr;
	int	len_d;

	flagp = is_plus_neg_u(n, ptr);
	len_pr = ft_max(ptr->precision + flagp, count_arg + flagp);
	len_d = ft_max(ptr->width, len_pr);
	return (len_d);
}

int	calcul_len_x(t_options *ptr, int count_arg, long long n)
{
	int	flagp;
	int	len_pr;
	int	len_x;

	flagp = is_plus_neg(n, ptr);
	len_pr = ft_max(ptr->precision + flagp, count_arg + flagp);
	len_x = ft_max(ptr->width, len_pr);
	return (len_x);
}

int	calcul_len_s(t_options *ptr, int len_str, char *str)
{
	int	len;

	len = len_str;
	if (str == NULL)
		len = calcul_len_s_minus(ptr, len_str);
	else
		len = calcul_len_s_right(ptr, len_str);
	return (len);
}

int	calcul_len_s_minus(t_options *ptr, int len_str)
{
	int	len;
	int	len_null;

	len = len_str;
	len_null = 6;
	if (ptr->width >= len_null && ptr->point && ptr->precision >= len_null)
		len = ptr->width;
	else if (ptr->width < len_null && ptr->point && ptr->precision >= len_null)
		len = len_null;
	else if (ptr->width < len_null && ptr->point && ptr->precision < len_null)
		len = len_str;
	else if (ptr->width >= len_null)
		len = ptr->width;
	else if (ptr->width < len_null)
		len = len_null;
	return (len);
}
