/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:22:09 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:14:32 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		len_s;
	int		i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
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
