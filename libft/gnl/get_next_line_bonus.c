/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:43:17 by bmirlico          #+#    #+#             */
/*   Updated: 2023/03/26 18:12:59 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line_bonus.h"

void	get_line(char **line, char **save)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*save)[i] != '\0' && (*save)[i] != '\n')
		i++;
	if ((*save)[i] == '\n')
		i++;
	*line = malloc(sizeof(char) * (i + 1));
	if (!*line)
		return ;
	j = 0;
	while (j < i)
	{
		(*line)[j] = (*save)[j];
		j++;
	}
	(*line)[j] = '\0';
}

void	after_get_line(char **save)
{
	size_t	i;
	size_t	j;
	char	*s;

	i = 0;
	while ((*save)[i] != '\0' && (*save)[i] != '\n')
		i++;
	if ((*save)[i] == '\n')
		i++;
	s = malloc(sizeof(char) * (ft_strlen((const char *)(*save)) - i + 1));
	if (!s)
		return ;
	j = 0;
	while (i < ft_strlen((const char *)(*save)))
	{
		s[j] = (*save)[i];
		j++;
		i++;
	}
	s[j] = '\0';
	free(*save);
	free_after_get_line(s, save);
}

void	read_and_save(int fd, char **save)
{
	char	*buf;
	int		nb_bytes;

	nb_bytes = 1;
	while (is_chr(*save, '\n') == 0 && nb_bytes != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		nb_bytes = read(fd, buf, BUFFER_SIZE);
		if (*save == NULL)
			init_save(save);
		if (nb_bytes == -1 || (nb_bytes == 0 && (*save)[0] == '\0'))
		{
			free(buf);
			buf = NULL;
			free(*save);
			*save = NULL;
			return ;
		}
		buf[nb_bytes] = '\0';
		*save = ft_strfjoin(*save, buf);
		free(buf);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[1024];

	line = NULL;
	if (fd > FOPEN_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_save(fd, &save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	get_line(&line, &save[fd]);
	after_get_line(&save[fd]);
	return (line);
}
