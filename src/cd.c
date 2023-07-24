/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:44:15 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/24 14:41:18 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Commande builtin CD
// Cas non gere : cd - (qui retourne ds le $OLDPWD)
// ATTENTION a l'env, PWD et OLDPWD a modifier
void	built_in_cd(t_command *tmp, t_pipex vars)
{
	int		len_tab;
	char	*error_str;
	char	*str;
	char	*cwd;

	len_tab = get_len_tab(tmp->cmd_args);
	error_str = NULL;
	str = NULL;
	cwd = malloc(sizeof(char) * (PATH_MAX));
	if (!cwd)
		return ;
	getcwd(cwd, PATH_MAX);
	if (len_tab > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		new_return_value(vars.copy_t_env, "1");
		free(cwd);
		if (vars.nb_pipes > 0)
		{
			free_and_exit(vars);
			exit(EXIT_FAILURE);
		}
	}
	else if (len_tab == 1)
	{
		ft_putstr_fd("cd: too few arguments\n", 2);
		new_return_value(vars.copy_t_env, "1");
		free(cwd);
		if (vars.nb_pipes > 0)
		{
			free_and_exit(vars);
			exit(EXIT_FAILURE);
		}
	}
	else if (chdir(tmp->cmd_args[1]) == 0)
	{
		str = ft_strjoin("OLDPWD=", cwd);
		export(vars.copy_t_env, str);
		free(str);
		getcwd(cwd, PATH_MAX);
		str = ft_strjoin("PWD=", cwd);
		export(vars.copy_t_env, str);
		free(cwd);
		free(str);
		new_return_value(vars.copy_t_env, "0");
		if (vars.nb_pipes > 0)
		{
			free_and_exit(vars);
			exit(EXIT_SUCCESS);
		}
	}
	else if (chdir(tmp->cmd_args[1]) == -1)
	{
		error_str = ft_strjoin("cd: ", tmp->cmd_args[1]);
		perror(error_str);
		new_return_value(vars.copy_t_env, "1");
		free(error_str);
		free(cwd);
		if (vars.nb_pipes > 0)
		{
			free_and_exit(vars);
			exit(EXIT_FAILURE);
		}
	}
}
