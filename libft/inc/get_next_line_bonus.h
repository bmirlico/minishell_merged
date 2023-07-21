/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:19:13 by bmirlico          #+#    #+#             */
/*   Updated: 2023/03/26 18:01:24 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# if (BUFFER_SIZE < 0)
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "./libft.h"

int		is_chr(char *s, char c);

char	*ft_strfjoin(char *s1, char *s2);

void	init_save(char **s);

void	free_after_get_line(char *s, char **save);

char	*get_next_line(int fd);

void	read_and_save(int fd, char **save);

void	get_line(char **line, char **save);

void	after_get_line(char **save);

#endif
