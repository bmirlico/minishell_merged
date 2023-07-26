/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:16:33 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/25 16:10:22 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function check if there is a var_env value specified
// (if a = is present)
int	affectation_is_complete(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

// This function is used in the case the user export a var_env already
// present in the env
void	swap_value(t_env *env, char *declaration)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*tmp;

	i = 0;
	name = NULL;
	tmp = env;
	value = NULL;
	while (declaration[i] != '=')
		i++;
	name = ft_substr(declaration, 0, i);
	i++;
	value = ft_substr(declaration, i, ft_strlen(declaration));
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, name, ft_strlen(name) + 1) == 0)
		{
			free(tmp->var_value);
			tmp->var_value = value;
		}
		tmp = tmp->next;
	}
	if (name != NULL)
		free(name);
}

// This function add a new var_env in the env_list
// if the affectation is complete
void	export(t_env *env, char *declaration)
{
	t_env	*new;

	new = NULL;
	if (affectation_is_complete(declaration) == 1)
	{
		if (already_exist(env, declaration) == 1)
			swap_value(env, declaration);
		else
		{
			new = (t_env *)malloc(sizeof(t_env));
			if (new == NULL)
				return ;
			fill_t_env(new, declaration);
			add_back_to_env(&env, new);
		}
	}
	new_return_value(env, "0");
}

// This function checks if the name of the new var_env is valid
// and display an error message if not
int	check_valid_identifier(t_pipex vars, char *str)
{
	int		i;
	int		affectation;

	i = 0;
	affectation = 0;
	if (str != NULL && str[0] == '\0')
	{
		display_not_a_valid_identifier(str, vars);
		return (0);
	}
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			affectation = 1;
		if ((ft_isalpha(str[0]) == 0 && str[0] != '_')
			|| (i != 0 && (ft_isalnum(str[i]) == 0
					&& str[i] != '_' && affectation == 0)))
		{
			display_not_a_valid_identifier(str, vars);
			return (0);
		}
		i++;
	}
	return (1);
}

// Displays the env if no args, and checks if the varenv name
// that is about to be export is valid
void	built_in_export(t_command *cmd, t_pipex vars)
{
	int	i;

	i = 1;
	if (get_len_tab(cmd->cmd_args) == 1)
		display_export(vars.copy_t_env, vars);
	else
	{
		while (cmd->cmd_args[i] != NULL)
		{
			if (check_valid_identifier(vars, cmd->cmd_args[i]) == 1)
				export(vars.copy_t_env, cmd->cmd_args[i]);
			i++;
		}
		if (vars.nb_pipes > 0)
		{
			free_and_exit(vars);
			exit(EXIT_SUCCESS);
		}
	}
}
