/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expand_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:11:47 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/24 20:05:34 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Count the nb of empty lines in a char **
int	get_nb_empty(char **tab)
{
	int	i;
	int	len_tab;
	int	empty;

	i = 0;
	empty = 0;
	len_tab = get_len_tab(tab);
	while (i < len_tab)
	{
		if (tab[i][0] == '\0')
			empty++;
		i++;
	}
	return (empty);
}

// this function return the len of the var_env value that will be added
// to the new string
int	get_varenv_value_len(t_env *env, char *str)
{
	int	i;
	int	nb;
	int	quote_state;
	int	var_env;
	int	prev_state;

	i = 0;
	nb = 0;
	quote_state = CLOSED;
	var_env = CLOSED;
	while (str[i])
	{
		prev_state = var_env;
		quote_state = quotes_state(str[i], quote_state);
		var_env = var_env_state(str, i, var_env, quote_state);
		if (var_env == SINGLE_OPEN && prev_state == CLOSED)
			nb += get_varenv_len(env, str, i);
		if (var_env == CLOSED && prev_state == SINGLE_OPEN && str[i] == '$')
			i--;
		i++;
	}
	return (nb);
}

// This function return the index of the last char of the var_env name
int	get_var_env_end(char *str, int i)
{
	while (end_var_env_declaration(str, i) != 0 && str[i] != '\0')
	{
		if (str[i] == '}')
			return (i);
		i++;
	}
	return (i);
}

// Didn't do the ? case A RAJOUTER
// this function return the len of the var_env name in the old string
int	get_varenv_len(t_env *env, char *str, int i)
{
	int		start;
	int		len;
	char	*tmp;
	int		nb;

	start = 0;
	len = 0;
	nb = 0;
	tmp = NULL;
	i++;
	if (str[i] == '{')
		i++;
	start = i;
	len = get_var_env_end(str, i) - start;
	if (len != 0)
	{
		tmp = ft_substr(str, start, len);
		nb = ft_strlen(get_env(env, tmp));
	}
	if (tmp != NULL)
		free(tmp);
	return (nb);
}

// This function return the len of var_env names in a string
// The var_env name char will be removed from the string and changed by
// their value
int	get_varname_len(char *str)
{
	int	i;
	int	nb;
	int	quote_state;
	int	var_env;
	int	prev_state;

	i = 0;
	nb = 0;
	quote_state = CLOSED;
	var_env = CLOSED;
	while (str[i])
	{
		prev_state = var_env;
		quote_state = quotes_state(str[i], quote_state);
		var_env = var_env_state(str, i, var_env, quote_state);
		if (var_env == SINGLE_OPEN)
			nb++;
		if (var_env == CLOSED && prev_state == SINGLE_OPEN && str[i] == '$')
			i--;
		i++;
	}
	return (nb);
}
