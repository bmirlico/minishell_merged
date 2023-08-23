/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:48:30 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/23 17:34:34 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui initialise la structure t_pipex qui va contenir
// les vars nb_pipes et le tableau de pipes pour l'execution des commandes
void	init_struct(t_pipex *vars)
{
	get_index_cmds(vars->copy_cmds);
	init_fds(vars->copy_cmds);
	vars->path = get_path(vars->copy_env_tmp);
	if (vars->path != NULL)
		vars->paths = ft_split(vars->path, ':');
	else
		vars->paths = NULL;
	vars->nb_cmds = lst_cmd_size(*(vars->copy_cmds));
	vars->nb_pipes = vars->nb_cmds - 1;
	vars->pipefd = init_pipefd(vars->nb_pipes);
	vars->tab_pid = malloc(sizeof(pid_t) * vars->nb_cmds);
	if (!vars->tab_pid)
		return ;
	tcgetattr(0, &(vars->original_attributes));
	vars->badsubst_heredoc = 0;
}

// fonction qui index les éléments de la liste chainée t_command
// sert à garder trace du numéro de la commande pour l'execution
void	get_index_cmds(t_command **cmds)
{
	t_command	*tmp;
	int			i;

	tmp = *cmds;
	i = 0;
	while (tmp != NULL)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

int	lst_cmd_size(t_command *lst)
{
	int			size;
	t_command	*tmp;

	tmp = lst;
	size = 0;
	if (!tmp)
		return (0);
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

//write a function that counts the number of / in the string
// DO NOT KNOW YET IF I WILL USE IT
int	count_slash(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (count);
	while (str[i])
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	return (count);
}

// strjoin modifie avec 3 chaines de caracteres
char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin((const char *)str1, (const char *)str2);
	tmp2 = ft_strjoin((const char *)tmp, (const char *)str3);
	free(tmp);
	return (tmp2);
}
