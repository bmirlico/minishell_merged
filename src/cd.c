/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:44:15 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 12:38:32 by bmirlico         ###   ########.fr       */
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
	if (len_tab > 2 || len_tab == 1)
		cd_pb_arguments(len_tab, cwd, vars);
	else if (chdir(tmp->cmd_args[1]) == 0)
		cd_working(str, cwd, vars);
	else if (chdir(tmp->cmd_args[1]) == -1)
		cd_not_working(error_str, cwd, tmp, vars);
}

// fonction qui gere le cas ou cd detient trop peu ou trop d'arguments
void	cd_pb_arguments(int len_tab, char *cwd, t_pipex vars)
{
	if (len_tab > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (len_tab == 1)
		ft_putstr_fd("cd: too few arguments\n", 2);
	new_return_value(vars.copy_t_env, "1");
	free(cwd);
	if (vars.nb_pipes > 0)
	{
		free_and_exit(vars);
		exit(EXIT_FAILURE);
	}
}

// fonction qui gere le cas ou cd fonctionne normalement
void	cd_working(char *str, char *cwd, t_pipex vars)
{
	str = ft_strjoin("OLDPWD=", cwd);
	if (check_existence_in_env("OLDPWD", vars.copy_t_env))
		export(vars.copy_t_env, str);
	free(str);
	getcwd(cwd, PATH_MAX);
	str = ft_strjoin("PWD=", cwd);
	if (check_existence_in_env("PWD", vars.copy_t_env))
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

// fonction qui gere les cas d'erreur de cd lorsque chdir == -1
void	cd_not_working(char *error_str, char *cwd, t_command *tmp,
			t_pipex vars)
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
