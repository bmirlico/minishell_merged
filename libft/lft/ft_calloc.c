/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:13:03 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:17:29 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
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
