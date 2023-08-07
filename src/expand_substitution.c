/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:07:25 by clbernar          #+#    #+#             */
/*   Updated: 2023/08/04 13:34:23 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function is similar to getenv. Instead of getting the variable
// from the original env, it gets it from my own env
char	*get_env(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(name, tmp->var_name, ft_strlen(name) + 1) == 0)
			return (tmp->var_value);
		tmp = tmp->next;
	}
	return (NULL);
}

// This function check if a string need to be modified in the EXPAND part
// That means if it contains var_env or quotes
int	to_be_modified(char *str)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = CLOSED;
	while (str[i])
	{
		quote_state = quotes_state(str[i], quote_state);
		if (quote_state != SINGLE_OPEN && str[i] == '$'
			&& var_env_declaration(str, i, quote_state) == 0)
			return (0);
		i++;
	}
	return (1);
}

//This function returns how many opening and closing quotes are in the string
int	nb_quotes(char *str)
{
	int	i;
	int	quote_state;
	int	nb;
	int	prev_state;

	nb = 0;
	i = 0;
	quote_state = CLOSED;
	prev_state = CLOSED;
	while (str[i])
	{
		prev_state = quote_state;
		quote_state = quotes_state(str[i], quote_state);
		if (prev_state == CLOSED
			&& (quote_state == SINGLE_OPEN || quote_state == DOUBLE_OPEN))
			nb++;
		else if (quote_state == CLOSED
			&& (prev_state == SINGLE_OPEN || prev_state == DOUBLE_OPEN))
			nb++;
		i++;
	}
	return (nb);
}

// VAR_ENV_COPY INITIAL
/// @brief This function fill the new string with a var_env
/// @param str the old string
/// @param index the index where the var_env begin in the old string
/// @param new the new string
/// @param dest the index where the function should start filling the new string
/// @return Var_env len to keep filling the rest of the string
// int	var_env_copy(char *str, int index, char *new, int dest)
// {
// 	int		start;
// 	int		len;
// 	char	*tmp;
// 	char	*var_env_value;

// 	start = 0;
// 	len = 0;
// 	tmp = NULL;
// 	index++;
// 	if (str[index] == '{')
// 		index++;
// 	start = index;
// 	len = get_var_env_end(str, index) - start;
// 	if (len != 0)
// 		tmp = ft_substr(str, start, len);
// 	if (ft_strlen(tmp) == 0)
// 		return (0);
// 	var_env_value = get_env(tmp);
// 	if (ft_strlen(var_env_value) != 0)
// 		ft_strlcpy(new + dest, var_env_value, ft_strlen(var_env_value) + 1);
// 	if (tmp != NULL)
// 		free(tmp);
// 	return (ft_strlen(var_env_value));
// }

// VAR_ENV_COPY READAPTE
// @brief This function fill the new string with a var_env
// @param str the old string
// @param index the index where the var_env begin in the old string
// @param new the new string
// @param dest the index where the function should start filling the new string
// @return Var_env len to keep filling the rest of the string
int	var_env_copy(t_env *env, char *str, char *new, int dest)
{
	int		start;
	int		len;
	char	*tmp;
	char	*var_env_value;
	int		i;

	i = 1;
	start = 0;
	len = 0;
	tmp = NULL;
	if (str[i] == '{')
		i++;
	start = i;
	len = get_var_env_end(str + i, 0);
	if (len != 0)
		tmp = ft_substr(str + i, 0, len);
	if (ft_strlen(tmp) == 0)
		return (0);
	var_env_value = get_env(env, tmp);
	if (ft_strlen(var_env_value) != 0)
		ft_strlcpy(new + dest, var_env_value, ft_strlen(var_env_value) + 1);
	if (tmp != NULL)
		free(tmp);
	return (ft_strlen(var_env_value));
}

// This function fill the new string with char from the old string, or with
// char from a var_env
void	new_str(t_env *env, char *str, char *new)
{
	int	j;
	int	quote_state;
	int	var_env;
	int	prev_state;
	int	k;

	k = 0;
	quote_state = CLOSED;
	var_env = CLOSED;
	j = 0;
	while (str[j])
	{
		prev_state = var_env;
		quote_state = quotes_state(str[j], quote_state);
		var_env = var_env_state(str, j, var_env, quote_state);
		if (var_env == CLOSED && prev_state == SINGLE_OPEN && str[j] == '$')
			j--;
		else if (var_env == CLOSED)
			new[k++] = str[j];
		else if (var_env == SINGLE_OPEN && prev_state == CLOSED)
			k += var_env_copy(env, str + j, new, k);
		j++;
	}
}
