/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display8.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:50:47 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:01:26 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_in_array_ptr_right(char *array, char *hexa_str, int len, int len_nb)
{
	int	i;
	int	j;

	i = len - len_nb - 2;
	j = 0;
	array[i] = '0';
	array[i + 1] = 'x';
	i = len - len_nb;
	while (hexa_str[j] != '\0' && i < len)
	{
		array[i] = hexa_str[j];
		i++;
		j++;
	}
}

void	ft_putstr_count(char *s, int *count)
{
	int	len;

	len = ftm_strlen(s);
	write(1, s, len);
	*count += len;
}

void	ft_putstr_c(char *s, int *count, int len)
{
	write(1, s, len);
	*count += len;
}

void	double_free(void *ptr, void *ptr1)
{
	free(ptr);
	free(ptr1);
}
