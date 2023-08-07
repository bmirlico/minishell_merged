/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_special_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:20:53 by clbernar          #+#    #+#             */
/*   Updated: 2023/08/07 20:35:37 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function checks if the varenv value needs
// to be display in an other way
int	check_var_env(char *var)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (var[0] == ' ')
		return (1);
	while (var[i])
	{
		if (var[i] == ' ')
			space++;
		else
			space = 0;
		if (space > 1)
			return (1);
		i++;
	}
	return (0);
}

// This function checks the value of each var_env in the arg
// of echo command to detemine if it is a special varenv
int	is_special_var_env(char *str, int i, t_env *env)
{
	int		end;
	char	*var_name;
	t_env	*tmp;
	int		ret;

	ret = 0;
	tmp = env;
	i++;
	if (str[i] == '{')
		i++;
	end = get_var_env_end(str, i);
	var_name = ft_substr(str, i, end - 1);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, var_name, ft_strlen(tmp->var_name)) == 0)
		{
			if (check_var_env(tmp->var_value) == 1)
				ret = 1;
		}
		tmp = tmp->next;
	}
	if (var_name != NULL)
		free(var_name);
	return (ret);
}

// This function displays the var_env value whithout
// too many spaces
void	print_varenv_no_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0')
				return ;
			i--;
		}
		ft_printf("%c", str[i]);
		i++;
	}
}

// This function looks for the var_env and send its value to
// print_varenv_no_space to be well displayed
int	print_echo_special(t_env *env, char *str)
{
	int		i;
	int		j;
	int		end;
	char	*var_name;
	t_env	*tmp;

	i = 1;
	j = 0;
	tmp = env;
	if (str[i] == '{')
		i++;
	end = get_var_env_end(str, i);
	var_name = ft_substr(str, i, end - 1);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, var_name, ft_strlen(tmp->var_name)) == 0)
			break ;
		tmp = tmp->next;
	}
	print_varenv_no_space(tmp->var_value);
	if (var_name != NULL)
		free(var_name);
	return (end + i);
}

// Doit recevoir l'outfile pour write dans le bon FD !
// This function display each char, and when there is a varenv
// it sends the varenv to print_echo_special to be well displayed
void	print_echo(t_env *env, char *str)
{
	int	i;
	int	var_env;
	int	prev_state;

	i = 0;
	var_env = CLOSED;
	while (str[i])
	{
		prev_state = var_env;
		var_env = var_env_state(str, i, var_env, CLOSED);
		if (var_env == SINGLE_OPEN && prev_state == CLOSED)
			i += print_echo_special(env, str + i);
		else
			ft_printf("%c", str[i]);
		if (i > (int)ft_strlen(str))
			return ;
		i++;
	}
}
