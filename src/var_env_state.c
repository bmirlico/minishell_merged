/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:23:59 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/03 15:02:35 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function is similar to quotes_state
// It keeps a state of var_env to know if the actual char is a normal char
// or part of a var_env name
int	var_env_state(char *str, int i, int var_env_state, int q_state)
{
	if (q_state == SINGLE_OPEN)
		return (CLOSED);
	if (str[i] == '$' && var_env_state == CLOSED)
	{
		if (var_env_declaration(str, i, q_state) == 0)
			return (SINGLE_OPEN);
	}
	else if (var_env_state == SINGLE_OPEN)
	{
		if (end_var_env_declaration(str, i) == 0)
			return (CLOSED);
	}
	return (var_env_state);
}

// This function check if the $ sign has to be interpreted
// as a var_enc declaration or not
// Is a var_env declaration a $ followed by a letter or an opening quote
// or ? in format $var_env or ${var_env}
int	var_env_declaration(char *str, int i, int quote_state)
{
	if (ft_isalpha(str[i + 1]) == 1)
		return (0);
	if (str[i + 1] == '"' && quote_state != DOUBLE_OPEN)
		return (0);
	if (str[i + 1] == '\'' || str[i + 1] == '?')
		return (0);
	if (str[i + 1] == '{' && ft_isalpha(str[i + 2]) == 1)
		return (0);
	if (str[i + 1] == '{' && str[i + 2] == '?')
		return (0);
	return (1);
}

// This function is called on a var_env_name and it specifies
// If it is the end of the var_env or not
int	end_var_env_declaration(char *str, int i)
{
	if (str[i - 1] == '}')
		return (0);
	if (str[i] == '}' && is_closing_scope(str, i) == 1)
		return (1);
	if (ft_isalnum(str[i]) == 1 || str[i] == '_')
		return (1);
	if (str[i] == '{' && str[i - 1] == '$')
		return (1);
	if (str[i] == '?' && str[i - 1] == '$')
		return (1);
	if (i > 1 && str[i - 2] == '$' && str[i - 1] == '{'
		&& str[i] == '?' && str[i + 1] == '}')
		return (1);
	return (0);
}

// This function check if a } is a closing of a var_env or just a simple char
// If it is a var_env closing, it has to be considered as part of the var_env
// Ex : ${PATH} => PATH value // $PATH} => NOTHING + } join
int	is_closing_scope(char *str, int index)
{
	while (index != 0)
	{
		if (str[index] == '{' || str[index] == '$')
			return (1);
		index--;
	}
	return (0);
}
