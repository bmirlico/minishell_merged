/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_display2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:42:22 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:58:30 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_conditions_flags_ptr(t_options *ptr, char *s, int len_nb)
{
	if (ptr->minus == 1)
	{
		if (ptr->width > len_nb)
			put_space_right(s, len_nb, ptr->width - len_nb);
	}
	else
	{
		if (ptr->width > len_nb)
			put_space_left(s, ptr->width - len_nb);
	}
}

void	put_zero_left(char *s, int pos, int add)
{
	int	i;
	int	j;

	i = pos;
	j = 0;
	while (j < add && i - j >= 0)
	{
		s[i - j] = '0';
		j++;
	}
}

void	put_space_left(char *s, int add)
{
	int	i;

	i = 0;
	while (i < add && s[i] != '\0')
	{
		s[i] = ' ';
		i++;
	}
}

void	put_space_right(char *s, int pos, int add)
{
	int	i;
	int	j;
	int	len;

	i = pos;
	j = 0;
	len = ftm_strlen(s);
	while (j < add && i + j < len)
	{
		s[i + j] = ' ';
		j++;
	}
}

void	put_sub_s(char *s, int pos, char *str, int add)
{
	int		i;
	int		j;

	i = pos;
	j = 0;
	while (j < add && str[j] != '\0')
	{
		s[i + j] = str[j];
		j++;
	}
}
