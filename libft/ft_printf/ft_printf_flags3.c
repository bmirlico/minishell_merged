/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:55:58 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:02:30 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_sharp_xminus(t_options *ptr, char *array, int len_nb)
{
	if (ptr->precision > len_nb)
	{
		array[0] = '0';
		array[1] = 'X';
	}
	else
	{
		array[len_nb] = '0';
		array[len_nb + 1] = 'X';
		ft_swap(&array[0], &array[len_nb]);
		ft_swap(&array[1], &array[len_nb + 1]);
	}
}

void	put_sharp_xright(t_options *ptr, char *array, int len_nb)
{
	int	len;

	len = ftm_strlen(array);
	if (ptr->zero == 1 && ptr->width <= (int)ft_max(ptr->precision, len_nb))
	{
		array[0] = '0';
		array[1] = 'X';
	}
	else
	{
		array[len - ft_max(ptr->precision, len_nb) - 2] = '0';
		array[len - ft_max(ptr->precision, len_nb) - 1] = 'X';
	}
}
