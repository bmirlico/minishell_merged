/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:12:41 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/07 21:17:30 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_lists(t_token	**lst, t_token **lst_j, t_command **cmds)
{
	*lst = create_list_lexer();
	*lst_j = create_list_lexer();
	*cmds = create_list_parser();
}

// fonction qui affiche les elements du la liste du parser a savoir
// le tableau de tableau (qu'on envoie ensuite a execve) et la liste de redirs
// associee a la commande
void	display_parser(t_command **cmds)
{
	int			i;
	int			j;
	t_command	*tmp;

	j = 0;
	tmp = *cmds;
	while (tmp != NULL)
	{
		printf("\n---NODE no: %d----\n", j);
		i = 0;
		if (tmp->cmd_args != NULL)
		{
			while (tmp->cmd_args[i] != NULL)
			{
				ft_printf("CMD_ARGS: %s\n", tmp->cmd_args[i]);
				i++;
			}
		}
		display_lexer(&(tmp->redirections));
		printf("\n");
		j++;
		tmp = tmp->next;
	}
}

// fonction qui affiche les elements du la liste du lexer
void	display_lexer(t_token **lst)
{
	t_token	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		ft_printf("Type: %d ; Value: %c ; Str: %s\n", tmp->type,
			tmp->value, tmp->str);
		tmp = tmp->next;
	}
}

// fonction qui affiche les elements du la liste du lexer par char
// et du lexer par str
void	display_lexers(t_token **lst, t_token **lst_j)
{
	display_lexer(lst);
	ft_printf("\n----------\n\n");
	display_lexer(lst_j);
}
