/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:38:29 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:05:46 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	set_struct(const char *s, t_options *ptr, int *i)
{
	init_zero(ptr);
	init_flags(s, ptr, i);
	count_width(s, ptr);
	count_precision(s, ptr);
}

void	init_zero(t_options *ptr)
{
	ptr->minus = 0;
	ptr->zero = 0;
	ptr->width = 0;
	ptr->point = 0;
	ptr->precision = 0;
	ptr->plus = 0;
	ptr->space = 0;
	ptr->sharp = 0;
}

void	init_flags(const char *s, t_options *ptr, int *i)
{
	int	j;

	j = 0;
	while (ftm_strchr(CONVERTERS, s[j]) == 0 && s[j] != '\0')
	{
		if (s[j] == '-')
			ptr->minus = 1;
		else if (s[j] == '.')
			ptr->point = 1;
		else if (s[j] == '#')
			ptr->sharp = 1;
		else if (s[j] == '+')
			ptr->plus = 1;
		else if (s[j] == ' ')
			ptr->space = 1;
		j++;
	}
	*i += j;
	j = 0;
	while (!(s[j] >= '0' && s[j] <= '9') && s[j] != '\0')
		j++;
	if (s[j] == '0')
		ptr->zero = 1;
}

void	count_width(const char *s, t_options *ptr)
{
	int			i;
	long long	len_width;

	i = 0;
	len_width = 0;
	while (s[i] != '.' && ftm_strchr(CONVERTERS, s[i]) == 0 && s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			len_width = len_width * 10 + (s[i] - 48);
		i++;
	}
	ptr->width = len_width;
}

void	count_precision(const char *s, t_options *ptr)
{
	int			i;
	long long	len_precision;

	i = 0;
	len_precision = 0;
	while (s[i] != '.' && ftm_strchr(CONVERTERS, s[i]) == 0 && s[i] != '\0')
		i++;
	if (s[i] == '.')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		len_precision = len_precision * 10 + (s[i] - 48);
		i++;
	}
	ptr->precision = len_precision;
}
