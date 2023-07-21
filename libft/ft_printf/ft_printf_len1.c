/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_len1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:00:33 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:05:37 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	*ft_calloc_zero(size_t nmemb, size_t size)
{
	char	*array;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > __SIZE_MAX__ / size)
		return (0);
	array = malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, nmemb * size);
	return ((void *)array);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if ((!s) || (n <= 0))
		return ;
	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '0';
		i++;
	}
}

int	count_param(long long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	else if (n == 0)
		count++;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	count_param_x(long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

int	count_param_ux(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}
