/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:29:26 by bmirlico          #+#    #+#             */
/*   Updated: 2023/03/26 18:01:02 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line_bonus.h"

int	is_chr(char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	else
	{
		while (s[i] != '\0')
		{
			if (s[i] == c)
				return (1);
			i++;
		}
		if (s[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin((char const *)s1, (char const *)s2);
	free(s1);
	s1 = tmp;
	return (s1);
}

void	init_save(char **s)
{
	*s = malloc(sizeof(char) * 1);
	if (!*s)
		return ;
	(*s)[0] = '\0';
}

void	free_after_get_line(char *s, char **save)
{
	if (s[0] != '\0')
		*save = s;
	else
	{
		free(s);
		*save = NULL;
	}
}
