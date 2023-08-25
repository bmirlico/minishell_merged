/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:06:43 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/25 13:10:53 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui renvoie le type de token associe a un char
t_token_type	get_token_type(char c)
{
	if (c == '|')
		return (T_PIPE);
	else if (c == '<')
		return (T_LR);
	else if (c == '>')
		return (T_RR);
	else if (c == ' ' || c == '\t')
		return (T_SPACE);
	else if (c == '\'')
		return (T_SINGLEQ);
	else if (c == '"')
		return (T_DOUBLEQ);
	else
		return (T_CMD);
}
