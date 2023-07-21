/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:57:46 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:15:42 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	size_t			i;

	i = 0;
	cs = (unsigned char *)s;
	if (!s)
		return (NULL);
	while (i < n)
	{
		if (cs[i] == (unsigned char)c)
			return (&cs[i]);
		i++;
	}
	return (0);
}
