/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:47:05 by clbernar          #+#    #+#             */
/*   Updated: 2023/08/07 15:45:36 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function checks if the arg needs to be expand or
// if it's a var_env with a value that needs to be changed
int	no_expand_needed(char *str, t_env *env)
{
	int	i;
	int	quote_state;
	int	var_env;
	int	prev_state;

	i = 0;
	quote_state = CLOSED;
	var_env = CLOSED;
	while (str[i])
	{
		prev_state = var_env;
		quote_state = quotes_state(str[i], quote_state);
		var_env = var_env_state(str, i, var_env, quote_state);
		if (var_env == SINGLE_OPEN
			&& prev_state == CLOSED && quote_state == CLOSED)
		{
			if (is_special_var_env(str, i, env) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

// This function expand the arg of the echo command and display
// it or send it to a spcecial case echo function
// The variable option allows us to display -n when it's not
// considered as an option -n
void	echo(t_command *cmd, t_env *env)
{
	int	i;
	int	option;

	option = 0;
	i = 1;
	while (is_option_n(cmd->cmd_args[i]) == 1)
		i++;
	while (cmd->cmd_args[i] != NULL)
	{
		if (no_expand_needed(cmd->cmd_args[i], env) == 1)
			print_echo(env, cmd->cmd_args[i]);
		else
		{
			if (to_be_modified(cmd->cmd_args[i]) == 0)
				expand_str_tab(env, cmd->cmd_args, i);
			if (nb_quotes(cmd->cmd_args[i]) > 0)
				quote_removing_tab(cmd->cmd_args, i,
					nb_quotes(cmd->cmd_args[i]));
			if (!is_option_n(cmd->cmd_args[i]))
				option++;
			if (option != 0 && ft_strlen(cmd->cmd_args[i]) != 0)
				ft_printf("%s ", cmd->cmd_args[i]);
		}
		i++;
	}
}

// This function checks if the arg is a n option (-n or -nnnnnnnn is similar)
int	is_option_n(char *str)
{
	int	i;

	i = 0;
	if (str != NULL && str[0] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// This function calls echo if needed ans display a '\n'
// if the otpion -n is not present
void	built_in_echo(t_command *cmd, t_pipex vars)
{
	if (get_len_tab(cmd->cmd_args) > 1)
		echo(cmd, vars.copy_t_env);
	new_return_value(vars.copy_t_env, "0");
	if (get_len_tab(cmd->cmd_args) > 1 && is_option_n(cmd->cmd_args[1]) == 1)
		return ;
	ft_printf("\n");
	if (vars.nb_pipes > 0)
	{
		free_and_exit(vars);
		exit(EXIT_SUCCESS);
	}
}
