/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fcts1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:32:45 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:03:36 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

/* 	PUTCHAR_PTR => gere tous les caracteres hors flag, et gere le "%%" */
void	ft_putchar_ptr(char c, int *count, int *i)
{
	if (c == '%')
		*i += 1;
	write(1, &c, 1);
	*count += 1;
}

/* 	PUTCHAR_PF => gere le flag 'c' */
void	ft_putchar_pf(va_list p, int *count, int *i, t_options *ptr)
{
	char		c;
	char		*array;
	int			len;

	c = va_arg(p, int);
	len = ft_max(ptr->width, 1);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	ft_conditions_flags_ptr(ptr, array, 1);
	put_in_array_c(array, c, ptr);
	ft_putstr_c(array, count, len);
	free(array);
	*i += 1;
}

/*	PUTSTR_PF => gere le flag 's' */
void	ft_putstr_pf(va_list p, int *count, int *i, t_options *ptr)
{
	char		*str;
	char		*array;
	int			len;
	int			len_str;

	str = va_arg(p, char *);
	len_str = ftm_strlen(str);
	len = calcul_len_s(ptr, len_str, str);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	ft_conditions_flags_str(ptr, array, len_str, str);
	put_in_array_str(array, len_str, str, ptr);
	ft_putstr_count(array, count);
	free(array);
	*i += 1;
}

/*	PUTPTR_PF => gere le flag 'p' */
void	ft_putptr_pf(va_list p, int *count, int *i, t_options *ptr)
{
	unsigned long	hexa;
	char			*hexa_str;
	char			*array;
	int				len_nb;
	int				len;

	hexa = (unsigned long)va_arg(p, void *);
	hexa_str = ft_itoa_ux(hexa);
	if (hexa == 0)
		len_nb = 5;
	else
		len_nb = ftm_strlen(hexa_str) + 2;
	len = ft_max(ptr->width, len_nb);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	ft_conditions_flags_ptr(ptr, array, len_nb);
	put_in_array_ptr(array, hexa_str, hexa, ptr);
	ft_putstr_count(array, count);
	double_free(hexa_str, array);
	*i += 1;
}

/* 	PUTDECIMAL_S_PF => gere le flag 'd', positifs et negatifs */
void	ft_putdecimal_s_pf(va_list p, int *count, int *i, t_options *ptr)
{
	long long	n;
	long long	count_arg;
	char		*array;
	char		*nb_str;
	int			len;

	n = (long long)va_arg(p, int);
	count_arg = count_param(n);
	nb_str = ftm_itoa(n);
	if (n == 0 && ptr->point == 1 && ptr->precision == 0 && ptr->width == 0)
		len = 0;
	else
		len = calcul_len_d(ptr, count_arg, n);
	array = ft_calloc_zero((len + 1), sizeof(char));
	if (!array)
		return ;
	array[len] = '\0';
	ft_conditions_flags(ptr, array, count_arg, n);
	put_in_array(array, nb_str, n, ptr);
	ft_putstr_count(array, count);
	double_free(nb_str, array);
	*i += 1;
}
