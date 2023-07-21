/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:27:08 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:15:18 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	if (!s)
		return (NULL);
	if (n <= 0)
		return (s);
	str = (unsigned char *)s;
	while (n > 0)
	{
		*str++ = (unsigned char)c;
		n--;
	}
	return (s);
}
