/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:50:33 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 19:05:54 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ftm_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ftm_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/* GET_INDEX => va renvoyer l'index du flag dans la 
chaine de caracteres CONVERTERS qui inclut tous les flags */
int	get_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief GET_ARG => va recuperer l'argument pointe par la pointeur va_list
 * et appliquer la fonction associe au bon index dans notre tableau de fonctions
 * => les fonctions ds le tableau doivent etre ds le meme ordre que 
 * les flags dans CONVERTERS
 * @param flag_char => le flag en caractere
 * @param p => le pointeur va_list qui pointe sur l'element variadique 
 * qui suit la chaine format
 * @param count => pointeur du compteur du nb d'elements, que printf va renvoyer 
 * @param i => pointeur de l'index de la chaine format qui est lue
 */
void	get_arg(const char *flag_string, va_list p, int *count, int *i)
{
	static t_ptr_func	tab[] = {ft_putchar_pf, ft_putstr_pf, ft_putptr_pf,
		ft_putdecimal_s_pf, ft_putint_pf, ft_putdecimal_us_pf,
		ft_puthexa_min_pf, ft_puthexa_maj_pf};
	int					conv_index;
	t_options			flags;
	int					j;

	j = *i;
	set_struct(flag_string, &flags, i);
	conv_index = get_index(CONVERTERS, flag_string[*i - j]);
	if (conv_index != -1)
		(*tab[conv_index])(p, count, i, &flags);
}

/* MA FONCTION PRINTF BONUS */
int	ft_printf(const char *format, ...)
{
	int			i;
	int			count;
	va_list		args;
	int			len;

	i = 0;
	count = 0;
	len = ftm_strlen((char *)format);
	va_start(args, format);
	while (format[i] != '\0' && i < len)
	{
		if (format[i] != '%' || (format[i] == '%' && format[i + 1] == '%'))
			ft_putchar_ptr(format[i], &count, &i);
		else if (format[i] == '%')
			get_arg(&format[i + 1], args, &count, &i);
		i++;
	}
	va_end(args);
	return (count);
}
