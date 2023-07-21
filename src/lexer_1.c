/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/19 20:23:14 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui regroupe les elements de la liste renvoyee par le lexer_char
// pour avoir cette fois des strings
// la fonction passe les espaces (cf. les cas qui fonctionnent comme >file)
void	lexer_str(t_token **lst, t_token **lst_j)
{
	t_token	*tmp;
	char	*join;

	tmp = *lst;
	while (tmp != NULL)
	{
		join = NULL;
		if (tmp->type == T_CMD || tmp->type == T_SINGLEQ
			|| tmp->type == T_DOUBLEQ)
			group_str(&tmp, lst_j, join);
		else if ((tmp->type == T_LR && tmp->next->type == T_LR)
			|| (tmp->type == T_RR && tmp->next->type == T_RR))
			group_redirs(&tmp, lst_j, join);
		else if (tmp->type == T_SPACE)
			tmp = tmp->next;
		else
			add_char_to_str(&tmp, lst_j, join);
	}
	tokenize_remaining(lst_j);
}

// fonction qui regroupe tout ce qu'il y a entre single ou double quote
// comme un mot de type T_CMD 
void	group_quotes(t_token **tmp, char **join)
{
	t_token_type	limit;

	limit = (*tmp)->type;
	ft_join_free(join, (*tmp)->value);
	*tmp = (*tmp)->next;
	while ((*tmp)->type != limit)
	{
		ft_join_free(join, (*tmp)->value);
		*tmp = (*tmp)->next;
	}
	ft_join_free(join, (*tmp)->value);
	*tmp = (*tmp)->next;
}

// fonction qui va regrouper les characteres du meme type (T_CMD) et
// former une string
void	group_str(t_token **tmp, t_token **lst_j, char *join)
{
	t_token			*new;

	while ((*tmp)->type == T_CMD || (*tmp)->type == T_SINGLEQ
		|| (*tmp)->type == T_DOUBLEQ)
	{
		if ((*tmp)->type == T_SINGLEQ || (*tmp)->type == T_DOUBLEQ)
			group_quotes(tmp, &join);
		else
		{
			ft_join_free(&join, (*tmp)->value);
			*tmp = (*tmp)->next;
		}
	}
	new = create_token(T_CMD, '\0', join);
	push_to_list(lst_j, new);
}

// fonction qui va regrouper les redirections caractere par caractere et
// former une string
void	group_redirs(t_token **tmp, t_token **lst_j, char *join)
{
	t_token	*new;

	ft_join_free(&join, (*tmp)->value);
	ft_join_free(&join, (*tmp)->next->value);
	if ((*tmp)->type == T_LR)
		(*tmp)->type = T_HEREDOC;
	else if ((*tmp)->type == T_RR)
		(*tmp)->type = T_APPEND;
	new = create_token((*tmp)->type, '\0', join);
	push_to_list(lst_j, new);
	*tmp = (*tmp)->next->next;
}

// fonction qui passe sur un caractere seul et le convertir en string
// gere le T_EOF
void	add_char_to_str(t_token **tmp, t_token **lst_j, char *join)
{
	t_token	*new;

	ft_join_free(&join, (*tmp)->value);
	new = create_token((*tmp)->type, '\0', join);
	push_to_list(lst_j, new);
	*tmp = (*tmp)->next;
}
