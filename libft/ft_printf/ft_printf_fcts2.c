/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fcts2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:58:11 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:03:57 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

/* 	PUTINT_PF => gere le flag 'i', que les nbs positifs */
void	ft_putint_pf(va_list p, int *count, int *i, t_options *ptr)
{
	long long	n;
	char		*array;
	char		*nb_str;
	int			len;
	int			len_nb;

	n = (long long)va_arg(p, int);
	nb_str = ftm_itoa(n);
	len_nb = ftm_strlen(nb_str);
	if (n == 0 && ptr->point == 1 && ptr->precision == 0 && ptr->width == 0)
		len = 0;
	else
		len = calcul_len_d(ptr, len_nb, n);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	ft_conditions_flags(ptr, array, len_nb, n);
	put_in_array(array, nb_str, n, ptr);
	ft_putstr_count(array, count);
	double_free(nb_str, array);
	*i += 1;
}

/* 	PUTDECIMAL_US_PF => gere le flag 'u' */
void	ft_putdecimal_us_pf(va_list p, int *count, int *i, t_options *ptr)
{
	unsigned long	n;
	char			*array;
	char			*nb_str;
	int				len;
	int				len_nb;

	n = (unsigned long)va_arg(p, int);
	nb_str = ft_itoa_u(n);
	len_nb = ftm_strlen(nb_str);
	if (n == 0 && ptr->point == 1 && ptr->precision == 0 && ptr->width == 0)
		len = 0;
	else
		len = calcul_len_u(ptr, len_nb, n);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	ft_conditions_flags(ptr, array, len_nb, n);
	put_in_array_u(array, nb_str, n, ptr);
	ft_putstr_count(array, count);
	double_free(nb_str, array);
	*i += 1;
}

void	ft_puthexa_min_pf(va_list p, int *count, int *i, t_options *ptr)
{
	long long		n;
	char			*array;
	char			*nb_str;
	int				len;
	int				len_nb;

	n = (long long)va_arg(p, int);
	nb_str = ft_itoa_x(n);
	len_nb = ftm_strlen(nb_str);
	if (n == 0 && ptr->point == 1 && ptr->precision == 0 && ptr->width == 0)
		len = 0;
	else
		len = calcul_len_x(ptr, len_nb, n);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	if (n < 0)
		n *= -1;
	ft_conditions_flags(ptr, array, len_nb, n);
	put_in_array_u(array, nb_str, n, ptr);
	ft_putstr_count(array, count);
	double_free(nb_str, array);
	*i += 1;
}

void	ft_puthexa_maj_pf(va_list p, int *count, int *i, t_options *ptr)
{
	long long		n;
	char			*array;
	char			*nb_str;
	int				len;
	int				len_nb;

	n = (long long)va_arg(p, int);
	nb_str = ft_itoa_xx(n);
	len_nb = ftm_strlen(nb_str);
	if (n == 0 && ptr->point == 1 && ptr->precision == 0 && ptr->width == 0)
		len = 0;
	else
		len = calcul_len_x(ptr, len_nb, n);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	if (n < 0)
		n *= -1;
	ft_conditions_flags(ptr, array, len_nb, n);
	put_in_array_xx(array, nb_str, n, ptr);
	ft_putstr_count(array, count);
	double_free(nb_str, array);
	*i += 1;
}
