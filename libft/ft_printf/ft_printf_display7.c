/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display7.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:14:19 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:01:21 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_itoa_x(long long n)
{
	int		i;
	int		x;
	char	*str;

	if (n < 0)
		n = (unsigned int)n;
	i = count_param_x(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
	while (i >= 0)
	{
		x = n % 16;
		if (x >= 0 && x < 10)
			str[i] = x + 48;
		else if (x >= 10)
			str[i] = x + 'a' - 10;
		n /= 16;
		i--;
	}
	return (str);
}

char	*ft_itoa_xx(long long n)
{
	int		i;
	int		x;
	char	*str;

	if (n < 0)
		n = (unsigned int)n;
	i = count_param_x(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
	while (i >= 0)
	{
		x = n % 16;
		if (x >= 0 && x < 10)
			str[i] = x + 48;
		else if (x >= 10)
			str[i] = x + 'A' - 10;
		n /= 16;
		i--;
	}
	return (str);
}

void	put_in_array_ptr(char *array, char *hexa_str, unsigned long hexa,
		t_options *ptr)
{
	int		len;
	int		len_nb;
	char	*nil;

	len = ftm_strlen(array);
	len_nb = ftm_strlen(hexa_str);
	nil = "(nil)";
	if (hexa == 0)
		put_in_array_ptrn(array, nil, ptr, len);
	else
	{
		if (ptr->minus)
			put_in_array_ptr_minus(array, hexa_str, len);
		else
			put_in_array_ptr_right(array, hexa_str, len, len_nb);
	}
}

void	put_in_array_ptrn(char *array, char *nil, t_options *ptr, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ptr->minus == 1)
	{
		while (nil[j] != '\0')
		{
			array[i + j] = nil[j];
			j++;
		}
	}
	else
	{
		if (ptr->width > 5)
			i = len - 5;
		while (nil[j] != '\0')
		{
			array[i + j] = nil[j];
			j++;
		}
	}
}

void	put_in_array_ptr_minus(char *array, char *hexa_str, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	array[i] = '0';
	array[i + 1] = 'x';
	i = 2;
	while (hexa_str[j] != '\0' && i < len)
	{
		array[i] = hexa_str[j];
		i++;
		j++;
	}
}
