/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:14 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/24 19:34:16 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui recupere le path de l'env
char	*get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

// fonction utilise pour gerer le cas de unset $PATH
int	is_path_set(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

// fonction qui recupere la commande et le path concatene
char	*get_cmd_with_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_with_path;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	while (paths[i] != NULL)
	{
		cmd_with_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(cmd_with_path, F_OK) == 0)
			return (cmd_with_path);
		free(cmd_with_path);
		i++;
	}
	return (NULL);
}

// fonction qui copie les listes utilisees dans le lexer et parsing/expand
// pour pouvoir ensuite les free en cas d'exit ds l'execution
void	copy_lists(t_pipex *vars, t_token **lst, t_token **lst_j,
			t_command **cmds)
{
	vars->copy_lst = lst;
	vars->copy_lst_j = lst_j;
	vars->copy_cmds = cmds;
}

// fonction qui free toutes les listes (lexer_char, lexer_str et parser) +
// les elements malloc ds la structure t_pipex (tableau de pipes, path et
// tableau de paths) en cas d'exit dans la fonction d'execution
void	free_and_exit(t_pipex vars)
{
	free_pipex(vars);
	free_lists(vars.copy_lst, vars.copy_lst_j, vars.copy_cmds);
}
