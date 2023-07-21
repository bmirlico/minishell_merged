/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:53:21 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:59:12 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_in_array_str(char *array, int len_str, char *str, t_options *ptr)
{
	int		len;
	char	*str_n;

	len = ftm_strlen(array);
	str_n = "(null)";
	if (str == NULL)
		put_in_array_strnl(ptr, array, str_n, len);
	else
	{
		if (ptr->minus == 1 && len > 0)
			put_in_array_str_minus(ptr, array, str, len_str);
		else if (str && ptr->minus == 0 && len > 0)
			put_in_array_str_right(ptr, array, str, len_str);
	}
}

void	put_in_array_strnl(t_options *ptr, char *array, char *str_n, int len)
{
	if (ptr->minus == 1)
		put_in_array_strnl_minus(ptr, array, str_n);
	else if (ptr->minus == 0)
		put_in_array_strnl_right(ptr, array, str_n, len);
}

void	put_in_array_strnl_minus(t_options *ptr, char *array, char *str_n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((ptr->width >= 0 && !ptr->point) || ptr->precision >= 6)
	{
		while (str_n[j] != '\0')
		{
			array[i + j] = str_n[j];
			j++;
		}
	}
}

void	put_in_array_strnl_right(t_options *ptr, char *array, char *str_n,
		int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ptr->width >= 6)
		i = len - 6;
	if ((ptr->width >= 0 && !ptr->point) || ptr->precision >= 6)
	{
		while (str_n[j] != '\0')
		{
			array[i + j] = str_n[j];
			j++;
		}
	}
}

void	put_in_array_str_minus(t_options *ptr, char *array, char *str,
		int len_str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ftm_strlen(array);
	if (ptr->point == 1 && ptr->precision <= len_str)
	{
		while (str[j] != '\0' && i < ptr->precision)
		{
			array[i] = str[j];
			i++;
			j++;
		}
	}
	else
	{
		while (str[j] != '\0' && i < len)
		{
			array[i] = str[j];
			i++;
			j++;
		}
	}
}
