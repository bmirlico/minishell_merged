/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:45:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/03 15:26:09 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction de parsings de commandes qui regroupe les T_CMD dans un
// tableau de tableaux et associe a chaque commande une liste de redirections
void	parser(t_token **lst_j, t_command **cmds)
{
	t_token		*tmp;
	char		**tab;
	t_token		*redirs;

	tmp = *lst_j;
	tab = NULL;
	redirs = create_list_lexer();
	while (tmp != NULL)
	{
		if (tmp->type == T_LR || tmp->type == T_RR
			|| tmp->type == T_HEREDOC || tmp->type == T_APPEND
			|| tmp->type == T_INFILE || tmp->type == T_LIMITOR
			|| tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
			add_redirs(&tmp, &redirs);
		else if (tmp->type == T_CMD)
			add_command_to_tab(&tmp, &tab);
		else if (tmp->type == T_PIPE || tmp->type == T_EOF)
			add_command_to_list(&tmp, &redirs, &tab, cmds);
	}
}

// fonction qui cree un element d'une liste de redirections
// et l'ajoute dans la liste de redirections
void	add_redirs(t_token **tmp, t_token **redirs)
{
	t_token		*redirs_elem;
	char		*rdir;

	rdir = ft_strdup((*tmp)->str);
	redirs_elem = create_token((*tmp)->type, (*tmp)->value, rdir);
	push_to_list(redirs, redirs_elem);
	*tmp = (*tmp)->next;
}

// fonction qui ajoute une commande (type T_CMD) dans un tableau de tableaux
void	add_command_to_tab(t_token **tmp, char ***tab)
{
	while ((*tmp)->type == T_CMD)
	{
		fill_tab_free(tab, (*tmp)->str);
		*tmp = (*tmp)->next;
	}
}

// fonction qui cree une element de la liste de commandes
// et l'ajoute a la liste
void	add_command_to_list(t_token **tmp, t_token **redirs, char ***tab,
		t_command **cmds)
{
	t_command	*new;

	new = create_command(*tab, *redirs);
	push_to_parser(cmds, new);
	*tab = NULL;
	*redirs = create_list_lexer();
	*tmp = (*tmp)->next;
}

// fonction qui remplit mon tableau de commandes (la cmd + ses args)
void	fill_tab_free(char ***tab, char *str)
{
	char	**tmp;
	int		len_tab;
	int		len;
	int		i;

	len_tab = get_len_tab(*tab);
	len = ft_strlen(str);
	tmp = malloc(sizeof(char *) * (len_tab + 2));
	if (!tmp)
		return ;
	fill_in_tmp(tmp, *tab, len_tab);
	i = len_tab;
	tmp[i] = malloc(sizeof(char) * (len + 1));
	if (!tmp[i])
	{
		free_previous_str(*tab, i);
		return ;
	}
	ft_strncpy(tmp[i], str, len);
	tmp[++i] = NULL;
	free(*tab);
	*tab = tmp;
}
