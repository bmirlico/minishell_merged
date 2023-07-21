/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:45:26 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/20 12:48:29 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Commande builtin PWD
void	built_in_pwd(void)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * (PATH_MAX));
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
	free(cwd);
}
