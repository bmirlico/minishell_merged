/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:03:45 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:14:19 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	int		len_cat;
	int		len_s1;
	int		len_s2;

	if (!s1 && !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_cat = len_s1 + len_s2;
	cat = (char *)malloc(sizeof(char) * (len_cat + 1));
	if (!cat)
		return (0);
	ft_strlcpy(cat, s1, len_s1 + 1);
	ft_strlcat(cat, s2, len_cat + 1);
	return (cat);
}	
