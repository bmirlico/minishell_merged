/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:45:26 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 12:28:19 by bmirlico         ###   ########.fr       */
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
	if (check_existence_in_env("PWD", vars.copy_t_env))
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

// fonction qui check l'existence de PWD / OLDPWD ds l'env avant de l'export
// pour coller au comportement de bash dans le cas de UNSET PWD ou UNSET OLDPWD
int	check_existence_in_env(char *str, t_env *env)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	len = ft_strlen(str);
	while (tmp != NULL)
	{
		if (!ft_strncmp(str, tmp->var_name, len + 1))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
