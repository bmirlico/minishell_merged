/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:44:15 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/20 12:44:40 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Commande builtin CD
// Cas non gere : cd - (qui retourne ds le $OLDPWD)
// ATTENTION a l'env, PWD et OLDPWD a modifier
void	built_in_cd(t_command *tmp)
{
	int		len_tab;
	char	*error_str;

	len_tab = get_len_tab(tmp->cmd_args);
	error_str = ft_strjoin("cd: ", tmp->cmd_args[1]);
	if (len_tab > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (chdir(tmp->cmd_args[1]) == -1)
		perror(error_str);
	free(error_str);
}
