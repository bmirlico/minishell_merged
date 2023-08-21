/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs_1bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:06:26 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 16:06:40 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_error_rdirs_builtin(t_command *tmpc, t_pipex vars, t_token *tmp,
			t_token **rdirs)
{
	char	*error;

	error = NULL;
	if (check_bad_env_variable(tmp->str) == 2)
	{
		error = ft_strjoin(tmp->str, ": bad substitution\n");
		ft_putstr_fd(error, 2);
		free(error);
	}
	else if (tmp->str[0] == '\0')
		ft_putstr_fd("Ambiguous redirect\n", 2);
	else if (!ft_strncmp(tmp->str, "\"\"", 3))
		ft_putstr_fd(" : No such file or directory\n", 2);
	else
		perror(tmp->str);
	close_rdirs(rdirs, tmpc);
	if (vars.nb_pipes > 0)
		close_previous_pipe(vars, tmpc->index);
}

// fonction qui ferme le pipe et free le tab de pipes
// en cas d'erreur sur les rdirs (no such file or directory
// ou permission denied)
void	close_pipe_and_free(t_pipex vars, int index)
{
	if (index < vars.nb_pipes)
		close_pipe(vars, index);
	free_and_exit(vars);
	exit(EXIT_FAILURE);
}
