/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:42:44 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/07 15:20:20 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui indique si le caractere donne est
// un caractere special
int	is_special_char(char c)
{
	int	i;

	i = 0;
	while (SPECIAL_CHAR[i] != '\0')
	{
		if (SPECIAL_CHAR[i] == c)
			return (0);
		i++;
	}
	return (1);
}

// Cette fonction permet garder un etat d'ouverture ou de
// fermeture des quotes pour pouvoir interpreter ou non
// certains caracteres
int	quotes_state(char c, int prev_state)
{
	if (c == '\'')
	{
		if (prev_state == SINGLE_OPEN)
			return (CLOSED);
		else if (prev_state == CLOSED)
			return (SINGLE_OPEN);
	}
	else if (c == '\"')
	{
		if (prev_state == DOUBLE_OPEN)
			return (CLOSED);
		else if (prev_state == CLOSED)
			return (DOUBLE_OPEN);
	}
	return (prev_state);
}

// fonction qui indique si le caractere donne est un delimiteur ou non
// fonction NON UTILISEE pour le moment
int	is_delimiter(char c, char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i] != '\0')
	{
		if (c == delimiter[i])
			return (1);
		i++;
	}
	return (0);
}

// fonction qui copie une string ds une autre sur une longueur donnee
void	ft_strncpy(char *value, char *input, int len)
{
	int	i;

	if (!value || !input)
		return ;
	i = 0;
	while (i < len)
	{
		value[i] = input[i];
		i++;
	}
	value[i] = '\0';
}

// fonction pour etre a la norme dans la fonction
// check_bad_env_variable du fichier syntax_error_2.c
void	init_bad_env_var(int *i, int *var_env)
{
	*i = -1;
	*var_env = CLOSED;
}
