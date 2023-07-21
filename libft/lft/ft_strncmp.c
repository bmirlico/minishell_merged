/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:19:55 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:13:39 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((const unsigned char)s1[i] - (const unsigned char)s2[i]);
		i++;
	}
	if (s1[i] && i < n)
		return ((const unsigned char)s1[i]);
	if (s2[i] && i < n)
		return (-(const unsigned char)s2[i]);
	return (0);
}
