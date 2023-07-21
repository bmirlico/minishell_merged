/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:15:34 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:59:34 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_in_array_str_right(t_options *ptr, char *array, char *str,
		int len_str)
{
	int	i;
	int	j;
	int	len;
	int	min;

	j = 0;
	len = ftm_strlen(array);
	min = ft_min(ptr->precision, len_str);
	if (ptr->point == 1 && ptr->width > (int)min)
		i = len - (int)min;
	else if (ptr->point == 0 && ptr->width > len_str)
		i = len - len_str;
	else
		i = 0;
	while (str[j] != '\0' && i < len)
	{
		array[i] = str[j];
		i++;
		j++;
	}
}

void	put_in_array_u(char *array, char *nb_str, unsigned long n,
			t_options *ptr)
{
	int	len_nb;

	len_nb = ftm_strlen(nb_str);
	if (ptr->minus == 1)
		put_u_minus(ptr, array, nb_str, n);
	else
		put_u_right(ptr, array, nb_str, n);
	if (ptr->plus == 1 && ptr->sharp == 0)
		put_plus_u(ptr, array, len_nb, n);
	else if (ptr->space == 1 && ptr->plus == 0 && ptr->sharp == 0)
		put_space_u(ptr, array, len_nb, n);
	else if (n != 0 && ptr->sharp == 1)
		put_sharp_x(ptr, array, len_nb);
}

void	put_u_minus(t_options *ptr, char *array, char *nb_str, unsigned long n)
{
	int	i;
	int	j;
	int	len_nb;
	int	len;

	len_nb = ftm_strlen(nb_str);
	len = ftm_strlen(array);
	i = put_u_minus_pr(ptr, len_nb, n);
	j = 0;
	if (!(n == 0 && ptr->point == 1 && ptr->precision == 0 && ptr->width >= 0))
	{
		while (nb_str[j] != '\0' && i < len)
		{
			array[i] = nb_str[j];
			i++;
			j++;
		}
	}
}

int	put_u_minus_pr(t_options *ptr, int len_nb, unsigned long n)
{
	int	i;
	int	is_plus;

	i = 0;
	is_plus = is_plus_neg_u(n, ptr);
	if (ptr->precision > len_nb)
	{
		while (i < ptr->precision - len_nb + is_plus)
			i++;
	}
	else
	{
		while (i < is_plus)
			i++;
	}
	return (i);
}

void	put_u_right(t_options *ptr, char *array, char *nb_str, unsigned long n)
{
	int	len_nb;
	int	len;
	int	i;
	int	j;

	len_nb = ftm_strlen(nb_str);
	len = ftm_strlen(array);
	i = len - len_nb;
	j = 0;
	if (!(n == 0 && ptr->point == 1 && ptr->precision == 0 && ptr->width >= 0))
	{
		while (nb_str[j] != '\0' && i < len)
		{
			array[i] = nb_str[j];
			i++;
			j++;
		}
	}
}
