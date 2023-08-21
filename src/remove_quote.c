/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:05:59 by clbernar          #+#    #+#             */
/*   Updated: 2023/08/21 18:17:35 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// This function removes quotes opening and closing quotes from a string
void	quote_removing_tab(char **tab, int index, int quotes)
{
	int		i;
	int		j;
	char	*new;
	int		quote_state;
	int		prev_state;

	i = 0;
	j = 0;
	quote_state = CLOSED;
	new = malloc(sizeof(char *) * (ft_strlen(tab[index]) - quotes + 1));
	if (new == NULL)
		return ;
	while (tab[index][i])
	{
		prev_state = quote_state;
		quote_state = quotes_state(tab[index][i], quote_state);
		if ((quote_state == CLOSED && prev_state == CLOSED)
			|| (quote_state != CLOSED && prev_state != CLOSED))
			new[j++] = tab[index][i];
		i++;
	}
	new[j] = '\0';
	if (tab[index] != NULL)
		free(tab[index]);
	tab[index] = new;
}

// This function checks in **tab args all the string to determine
// if they need to be modified (removing quotes)
void	remove_quotes_tab(char **tab)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	if (tab == NULL)
		return ;
	if (ft_strlen(tab[0]) != 0
		&& ft_strncmp(tab[0], "echo", ft_strlen(tab[0])) == 0)
		return ;
	while (tab[i])
	{
		quotes = nb_quotes(tab[i]);
		if (quotes != 0)
			quote_removing_tab(tab, i, quotes);
		i++;
	}
}

// This function replaces a string by a copy of it whithout the quotes
void	quote_removing_rdir(t_token *rdir, int quotes)
{
	int		i;
	int		j;
	char	*new;
	int		quote_state;
	int		prev_state;

	i = 0;
	j = 0;
	quote_state = CLOSED;
	new = malloc(sizeof(char) * (ft_strlen(rdir->str) - quotes + 1));
	if (new == NULL)
		return ;
	while (rdir->str[i])
	{
		prev_state = quote_state;
		quote_state = quotes_state(rdir->str[i], quote_state);
		if ((quote_state == CLOSED && prev_state == CLOSED)
			|| (quote_state != CLOSED && prev_state != CLOSED))
			new[j++] = rdir->str[i];
		i++;
	}
	new[j] = '\0';
	if (rdir->str != NULL)
		free(rdir->str);
	rdir->str = new;
}

// This function checks in the rdir lst all the string to determine
// if they need to be modified (removing quotes)
void	remove_quotes_rdir(t_token	*redirections)
{
	t_token	*tmp;
	int		quotes;

	quotes = 0;
	tmp = redirections;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		quotes = nb_quotes(tmp->str);
		if (quotes != 0)
			quote_removing_rdir(tmp, quotes);
		tmp = tmp->next;
	}
}

// This function replaces a string by a copy of it whithout the quotes
void	quote_removing_str(char **str, int quotes)
{
	int		i;
	int		j;
	char	*new;
	int		quote_state;
	int		prev_state;

	i = 0;
	j = 0;
	quote_state = CLOSED;
	new = malloc(sizeof(char) * (ft_strlen(*str) - quotes + 1));
	if (new == NULL)
		return ;
	while ((*str)[i])
	{
		prev_state = quote_state;
		quote_state = quotes_state((*str)[i], quote_state);
		if ((quote_state == CLOSED && prev_state == CLOSED)
			|| (quote_state != CLOSED && prev_state != CLOSED))
			new[j++] = (*str)[i];
		i++;
	}
	new[j] = '\0';
	if (*str != NULL)
		free(*str);
	*str = new;
}
