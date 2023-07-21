/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:42:03 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:58:26 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_conditions_flags(t_options *ptr, char *s, int count_param,
		long long n)
{
	if (ptr->minus == 1)
		ft_conditions_dminus(ptr, s, count_param, n);
	else
		ft_conditions_dright(ptr, s, count_param, n);
}

void	ft_conditions_dminus(t_options *ptr, char *s, int count_param,
		long long n)
{
	int		len;
	int		pos_len_count;
	int		pr;
	int		flag_zero;
	size_t	max;

	len = ftm_strlen(s);
	pos_len_count = len - count_param - 1;
	pr = ptr->precision - count_param;
	flag_zero = is_zero(n);
	max = ft_max(ptr->precision, count_param);
	if (ptr->point == 1 && ptr->precision > count_param - is_neg(n))
		put_zero_left(s, pos_len_count + is_neg(n), pr + is_neg(n));
	if (ptr->width > ((int)max) - flag_zero)
		put_space_right(s, max - flag_zero, ptr->width - (int)max + flag_zero);
}

void	ft_conditions_dright(t_options *ptr, char *s, int count_param,
		long long n)
{
	int		len;
	int		pos_len_count;
	int		pr;
	int		flag_zero;
	size_t	max;

	len = ftm_strlen(s);
	pos_len_count = len - count_param - 1;
	pr = ptr->precision - count_param;
	flag_zero = is_zero(n);
	max = ft_max(ptr->precision, count_param);
	if (ptr->point == 1 && ptr->precision > count_param - is_neg(n))
		put_zero_left(s, pos_len_count + is_neg(n), pr + is_neg(n));
	if (ptr->zero == 0 && ptr->width > ((int)max) - flag_zero)
	{
		if (ptr->precision > 1)
			put_space_left(s, ptr->width - (int)max - is_neg(n));
		else
			put_space_left(s, ptr->width - (int)max + flag_zero);
	}
	else if (ptr->zero && ptr->point && ptr->width > ((int)max) - flag_zero)
		ft_conditions_dright2(ptr, s, count_param, n);
	else if (ptr->zero == 1 && ptr->point == 0 && ptr->width > count_param)
		put_zero_left(s, pos_len_count, ptr->width - count_param);
}

void	ft_conditions_dright2(t_options *ptr, char *s, int count_param,
		long long n)
{
	size_t	max;
	int		flag_zero;

	max = ft_max(ptr->precision, count_param);
	flag_zero = is_zero(n);
	if (ptr->precision > 1)
	{
		if (ptr->precision > count_param)
			put_space_left(s, ptr->width - (int)max - is_neg(n));
		else
			put_space_left(s, ptr->width - (int)max);
	}
	else
		put_space_left(s, ptr->width - (int)max + flag_zero);
}

void	ft_conditions_flags_str(t_options *ptr, char *s, int len_str, char *str)
{
	size_t	min;
	int		len;
	int		pos_len_count;

	min = ft_min(ptr->precision, len_str);
	len = ftm_strlen(s);
	pos_len_count = len - min;
	if (ptr->minus == 1)
	{
		if (str && ptr->point == 1 && ptr->precision < len_str)
			put_sub_s(s, pos_len_count, str, ptr->precision);
		if (ptr->width > (int)min)
			put_space_right(s, (int)min, ptr->width - (int)min);
	}
	else
	{
		if (str && ptr->point == 1 && ptr->precision < len_str)
			put_sub_s(s, pos_len_count, str, ptr->precision);
		if (str && ptr->width > (int)min)
			put_space_left(s, ptr->width - (int)min);
		else if (!str && ptr->width > (int)min)
			put_space_left(s, ptr->width - (int)ft_min(ptr->precision, 6));
	}
}
