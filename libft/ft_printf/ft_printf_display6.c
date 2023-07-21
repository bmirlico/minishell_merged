/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:59:57 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:05:13 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_in_array_xx(char *array, char *nb_str, unsigned long n,
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
		put_sharp_xx(ptr, array, len_nb);
}

char	*ftm_itoa(long long n)
{
	int		i;
	char	*str;

	if (n == -2147483648)
		return (ftm_strdup("-2147483648"));
	i = count_param(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	return (str);
}

char	*ftm_strdup(char *s)
{
	char	*d;
	int		len_s;
	int		i;

	if (!s)
		return (NULL);
	len_s = ftm_strlen(s);
	i = 0;
	d = (char *)malloc(sizeof(char) * (len_s + 1));
	if (!d)
		return (0);
	while (s[i])
	{	
		d[i] = (char)s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_itoa_u(long long n)
{
	int		i;
	char	*str;

	if (n < 0)
		n = (unsigned int)n;
	i = count_param(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
	while (n > 0)
	{
		str[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa_ux(unsigned long n)
{
	int		i;
	int		x;
	char	*str;

	i = count_param_ux(n);
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
