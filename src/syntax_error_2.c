/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:19:04 by clbernar          #+#    #+#             */
/*   Updated: 2023/08/25 13:25:44 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Cette fonction check si il y a une syntax_error
// du a un backslash , a un ou plusieurs carcteres speciaux
// en dehors de quotes, ou un a des quotes non fermees
int	check_special_char(char *input)
{
	int	i;
	int	prev_state;

	prev_state = CLOSED;
	i = 0;
	while (input[i])
	{
		prev_state = quotes_state(input[i], prev_state);
		i++;
	}
	if (prev_state != CLOSED)
		return (0);
	return (1);
}

// Check la syntax des var_env
int	check_bad_env_variable(char *input)
{
	int	i;
	int	var_env;

	init_bad_env_var(&i, &var_env);
	while (input != NULL && input[++i])
	{
		if (input[i] == '$' && input[i + 1] == '{' && input[i + 2] == '}')
			return (2);
		else if ((input[i] == '$' && input[i + 1] == '{')
			&& (ft_isalnum(input[i + 2]) || input[i + 2] == '?'))
		{
			var_env = SINGLE_OPEN;
			i++;
			if (check_last_exitcode_case(input, i + 1) != 1)
				return (check_last_exitcode_case(input, i));
		}
		else if (var_env == SINGLE_OPEN && input[i] == '}')
			var_env = CLOSED;
		else if (var_env == SINGLE_OPEN
			&& (ft_isalnum(input[i]) != 1 && input[i] != '?'))
			return (2);
	}
	if (var_env == SINGLE_OPEN)
		return (0);
	return (1);
}

// This function allow only the syntax ${?} in the ? case
int	check_last_exitcode_case(char *input, int index)
{
	int	other_char;
	int	closed;
	int	check;

	check = 0;
	closed = 0;
	other_char = 0;
	while (input[index])
	{
		if (input[index] == '}')
		{
			closed = 1;
			break ;
		}
		if (input[index] != '?')
			other_char = 1;
		else if (input[index] == '?')
			check++;
		index++;
	}
	if (closed != 1)
		return (0);
	if ((other_char == 1 && check != 0) || check > 1)
		return (2);
	return (1);
}

// This function is just the end of check_empty_redirection (norm issue)
int	check_rdir(int rdir)
{
	if (rdir != CLOSED)
		return (0);
	else
		return (1);
}
