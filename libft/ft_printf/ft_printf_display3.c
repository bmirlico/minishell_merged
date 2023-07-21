/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:51:09 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:58:59 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_in_array_c(char *array, char c, t_options *ptr)
{
	int	i;
	int	len;

	i = 0;
	len = ftm_strlen(array);
	if (ptr->minus == 1)
		array[i] = c;
	else
	{
		if (ptr->width > 1)
			i = len - 1;
		array[i] = c;
	}
}

void	put_in_array(char *array, char *nb_str, long long n,
			t_options *ptr)
{
	int	len_nb;

	len_nb = ftm_strlen(nb_str);
	if (ptr->minus == 1)
		put_d_minus(ptr, array, nb_str, n);
	else
		put_d_right(ptr, array, nb_str, n);
	if (n >= 0 && ptr->plus == 1)
		put_plus_d(ptr, array, len_nb, n);
	else if (n >= 0 && ptr->space == 1 && ptr->plus == 0)
		put_space_d(ptr, array, len_nb, n);
	else if (n < 0)
		put_neg_d(ptr, array, len_nb);
}

void	put_d_minus(t_options *ptr, char *array, char *nb_str, long long n)
{
	int	i;
	int	j;
	int	len_nb;
	int	len;

	len_nb = ftm_strlen(nb_str);
	len = ftm_strlen(array);
	i = put_d_minus_pr(ptr, len_nb, n);
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

int	put_d_minus_pr(t_options *ptr, int len_nb, long long n)
{
	int	i;

	i = 0;
	if (ptr->precision > len_nb - is_neg(n))
	{
		while (i < ptr->precision - len_nb + is_neg(n) + is_plus_neg(n, ptr))
			i++;
	}
	else
	{
		while (i < is_plus_neg(n, ptr))
			i++;
	}
	return (i);
}

void	put_d_right(t_options *ptr, char *array, char *nb_str, long long n)
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
