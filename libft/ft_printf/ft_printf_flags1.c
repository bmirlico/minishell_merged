/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:55:20 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:02:18 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_swap(char *c1, char *c2)
{
	char	tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void	put_plus_d(t_options *ptr, char *array, int len_nb, long long n)
{
	int		len;
	size_t	max;
	int		is_plus;

	len = ftm_strlen(array);
	max = ft_max(ptr->precision, len_nb);
	is_plus = is_plus_neg(n, ptr);
	if (ptr->minus == 1)
			array[0] = '+';
	else
	{
		if (ptr->zero == 1 && ptr->width <= (int)max)
			array[0] = '+';
		else if (ptr->zero == 1 && ptr->width > (int)max)
			array[len - ft_max(ptr->precision, len_nb + is_plus) - 1] = '+';
		else
			array[len - ft_max(ptr->precision, len_nb) - 1] = '+';
	}
}

void	put_space_d(t_options *ptr, char *array, int len_nb, long long n)
{
	int		len;
	size_t	max;
	int		is_plus;

	len = ftm_strlen(array);
	max = ft_max(ptr->precision, len_nb);
	is_plus = is_plus_neg(n, ptr);
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

void	put_neg_d(t_options *ptr, char *array, int len_nb)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ftm_strlen(array);
	if (ptr->point == 1 && ptr->precision > len_nb - 1)
	{
		while (array[i] != '0' && i < len)
			i++;
		while (array[j] != '-' && j < len)
			j++;
		ft_swap(&array[i], &array[j]);
	}
	else if (ptr->zero == 1 && ptr->width > len_nb - 1)
	{
		while (array[i] != '0' && i < len)
			i++;
		while (array[j] != '-' && j < len)
			j++;
		if (ptr->width != len_nb && ptr->point == 0)
			ft_swap(&array[i], &array[j]);
	}
}

void	put_plus_u(t_options *ptr, char *array, int len_nb, unsigned long n)
{
	int		len;
	size_t	max;
	int		is_plus;

	len = ftm_strlen(array);
	max = ft_max(ptr->precision, len_nb);
	is_plus = is_plus_neg_u(n, ptr);
	if (ptr->minus == 1)
			array[0] = '+';
	else
	{
		if (ptr->zero == 1 && ptr->width <= (int)max)
			array[0] = '+';
		else if (ptr->zero == 1 && ptr->width > (int)max)
			array[len - ft_max(ptr->precision, len_nb + is_plus) - 1] = '+';
		else
			array[len - ft_max(ptr->precision, len_nb) - 1] = '+';
	}
}
