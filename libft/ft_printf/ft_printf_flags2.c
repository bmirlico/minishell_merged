/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:55:36 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:02:26 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_space_u(t_options *ptr, char *array, int len_nb, unsigned long n)
{
	int		len;
	size_t	max;
	int		is_plus;

	len = ftm_strlen(array);
	max = ft_max(ptr->precision, len_nb);
	is_plus = is_plus_neg_u(n, ptr);
	if (ptr->minus == 1)
			array[0] = ' ';
	else
	{
		if (ptr->zero == 1 && ptr->width <= (int)max)
			array[0] = ' ';
		else if (ptr->zero == 1 && ptr->width > (int)max)
			array[len - ft_max(ptr->precision, len_nb + is_plus) - 1] = ' ';
		else
			array[len - ft_max(ptr->precision, len_nb) - 1] = ' ';
	}
}

void	put_sharp_x(t_options *ptr, char *array, int len_nb)
{
	if (ptr->minus == 1)
		put_sharp_minus(ptr, array, len_nb);
	else
		put_sharp_right(ptr, array, len_nb);
}

void	put_sharp_minus(t_options *ptr, char *array, int len_nb)
{
	if (ptr->precision > len_nb)
	{
		array[0] = '0';
		array[1] = 'x';
	}
	else
	{
		array[len_nb] = '0';
		array[len_nb + 1] = 'x';
		ft_swap(&array[0], &array[len_nb]);
		ft_swap(&array[1], &array[len_nb + 1]);
	}
}

void	put_sharp_right(t_options *ptr, char *array, int len_nb)
{
	int	len;

	len = ftm_strlen(array);
	if (ptr->zero == 1 && ptr->width <= (int)ft_max(ptr->precision, len_nb))
	{
		array[0] = '0';
		array[1] = 'x';
	}
	else
	{
		array[len - ft_max(ptr->precision, len_nb) - 2] = '0';
		array[len - ft_max(ptr->precision, len_nb) - 1] = 'x';
	}
}

void	put_sharp_xx(t_options *ptr, char *array, int len_nb)
{
	if (ptr->minus == 1)
		put_sharp_xminus(ptr, array, len_nb);
	else
		put_sharp_xright(ptr, array, len_nb);
}
