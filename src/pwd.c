/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:45:26 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/24 16:18:47 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Commande builtin PWD
void	built_in_pwd(t_pipex vars)
{
	char	*cwd;
	char	*str;

	cwd = NULL;
	str = NULL;
	cwd = malloc(sizeof(char) * (PATH_MAX));
	if (!cwd)
		return ;
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
	str = ft_strjoin("PWD=", cwd);
	export(vars.copy_t_env, str);
	free(str);
	free(cwd);
	new_return_value(vars.copy_t_env, "0");
	if (vars.nb_pipes > 0)
	{
		free_and_exit(vars);
		exit(EXIT_SUCCESS);
	}
}
