/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:04:35 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/23 17:39:42 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	var_env_declaration_heredoc(char *str, int i)
{
	if (ft_isalpha(str[i + 1]) == 1)
		return (0);
	if (str[i + 1] == '?')
		return (0);
	if (str[i + 1] == '{' && ft_isalpha(str[i + 2]) == 1)
		return (0);
	if (str[i + 1] == '{' && str[i + 2] == '?')
		return (0);
	return (1);
}

int	get_varenv_value_len_heredoc(t_env *env, char *str)
{
	int	i;
	int	nb;
	int	var_env;
	int	prev_state;

	i = 0;
	nb = 0;
	var_env = CLOSED;
	while (str[i])
	{
		prev_state = var_env;
		var_env = var_env_state(str, i, var_env, CLOSED);
		if (var_env == SINGLE_OPEN && prev_state == CLOSED)
			nb += get_varenv_len(env, str, i);
		if (var_env == CLOSED && prev_state == SINGLE_OPEN && str[i] == '$')
			i--;
		i++;
	}
	return (nb);
}

int	get_varname_len_heredoc(char *str)
{
	int	i;
	int	nb;
	int	var_env;
	int	prev_state;

	i = 0;
	nb = 0;
	var_env = CLOSED;
	while (str[i])
	{
		prev_state = var_env;
		var_env = var_env_state(str, i, var_env, CLOSED);
		if (var_env == SINGLE_OPEN)
			nb++;
		if (var_env == CLOSED && prev_state == SINGLE_OPEN && str[i] == '$')
			i--;
		i++;
	}
	return (nb);
}

void	new_str_heredoc(t_env *env, char *str, char *new)
{
	int	j;
	int	var_env;
	int	prev_state;
	int	k;

	k = 0;
	var_env = CLOSED;
	j = 0;
	while (str[j])
	{
		prev_state = var_env;
		var_env = var_env_state(str, j, var_env, CLOSED);
		if (var_env == CLOSED && prev_state == SINGLE_OPEN && str[j] == '$')
			j--;
		else if (var_env == CLOSED)
			new[k++] = str[j];
		else if (var_env == SINGLE_OPEN && prev_state == CLOSED)
			k += var_env_copy(env, str + j, new, k);
		j++;
	}
}

void	expand_single_quote(char **str, t_pipex *vars)
{
	int		new_len;
	char	*new;
	int		var_env_len;

	new_len = 0;
	new = NULL;
	var_env_len = 0;
	var_env_len = get_varenv_value_len_heredoc(vars->copy_t_env, *str);
	new_len = ft_strlen(*str) - get_varname_len_heredoc(*str) + var_env_len;
	new = ft_calloc(sizeof(char), (new_len + 1));
	if (new == NULL)
		return ;
	new[new_len] = '\0';
	new_str_heredoc(vars->copy_t_env, *str, new);
	if (*str)
		free(*str);
	*str = new;
}
