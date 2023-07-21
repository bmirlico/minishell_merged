/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:20:19 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:14:46 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	nb_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	nb_letters(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	free_split(char **tabs, int i)
{
	while (tabs[i] && i >= 0)
	{	
		free(tabs[i]);
		i--;
	}
	free(tabs);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tabs;

	i = 0;
	j = 0;
	tabs = (char **)malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!tabs)
		return (NULL);
	while (i < nb_words(s, c))
	{
		while (s[j] == c)
			j++;
		tabs[i] = ft_substr(s, j, nb_letters(s, c, j));
		if (!tabs[i])
		{
			free_split(tabs, i);
			return (0);
		}
		j += nb_letters(s, c, j);
		i++;
	}
	tabs[i] = NULL;
	return (tabs);
}
