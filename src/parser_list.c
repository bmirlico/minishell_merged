/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:46:08 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/03 15:26:25 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// cree une nouvelle liste de commandes
t_command	*create_list_parser(void)
{
	return (NULL);
}

// fonction qui cree un element t_command avec le tableau contenant
// tous les arguments d'une commande, ainsi que son entree et sortie
t_command	*create_command(char **tab, t_token *redirs)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command) * 1);
	if (!new_command)
		return (NULL);
	new_command->cmd_args = tab;
	new_command->redirections = redirs;
	new_command->next = NULL;
	return (new_command);
}

// ajoute un nouvel element a une liste chainee t_command
void	push_to_parser(t_command **lst, t_command *new)
{
	t_command	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

// fonction qui free la liste du parser de commandes
void	free_parser(t_command **cmds)
{
	t_command	*tmp;

	tmp = *cmds;
	while (*cmds != NULL)
	{
		tmp = (*cmds)->next;
		free_tab((*cmds)->cmd_args);
		free_lexer_str(&((*cmds)->redirections));
		free(*cmds);
		*cmds = tmp;
	}
}

// fonction qui free la liste du lexer_char, la liste du lexer_str
// et la liste du parser
void	free_lists(t_token **lst, t_token **lst_j, t_command **cmds)
{
	free_lexer_char(lst);
	free_lexer_str(lst_j);
	free_parser(cmds);
}
