/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:27:59 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:13:24 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	find_strchr(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_countset(const char *str, char const *set, int *i)
{
	int	j;

	*i = 0;
	j = 0;
	while (str[*i] && find_strchr(str[*i], set) == 1)
		*i += 1;
	while (str[j])
		j++;
	j--;
	while (j > 0 && str[j] && find_strchr(str[j], set) == 1)
		j--;
	return (j - *i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*ts1;

	j = 0;
	len = ft_countset(s1, set, &i);
	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	if (len <= 0)
		return (ft_strdup(""));
	ts1 = (char *)malloc(sizeof(char) * (len + 1));
	if (!ts1)
		return (0);
	while (s1[i] && j < len)
	{
		ts1[j] = s1[i];
		i++;
		j++;
	}
	ts1[j] = '\0';
	return (ts1);
}
