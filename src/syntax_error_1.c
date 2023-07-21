/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:35:20 by clbernar          #+#    #+#             */
/*   Updated: 2023/07/21 14:57:06 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Cette fonction appelle les differentes fonctions de check syntax
// puis renvoie un message d'erreur si besoin
int	check_syntax(char *input)
{
	if (check_bad_env_variable(input) == 0 || check_pipe_error(input) == 0
		|| check_special_char(input) == 0 || check_redirections(input) == 0)
	{
		ft_printf("Syntax error\n");
		return (0);
	}
	return (1);
}

// Cette fonction check si les redirections ont bien une cible
// c'est a dire que qu'il y ait bien des caracteres autres que des
// espaces apres une redirection jusqu'au prochain pipe ou redirection
// A DOUCLE CHECK LA GESTION DES QUOTES
// A ENVOYE POUR MODIF A BASTIEN CETTE FONCTION +
// check_rdir utilise dans le return
int	check_empty_redirection(char *input)
{
	int	i;
	int	quote_state;
	int	rdir;

	rdir = CLOSED;
	i = 0;
	quote_state = CLOSED;
	while (input[i] != '\0')
	{
		quote_state = quotes_state(input[i], quote_state);
		if (quote_state == CLOSED && rdir == SINGLE_OPEN && (input[i] == '|'
				|| (input[i]) == '<' || (input[i]) == '>'))
			return (0);
		if (quote_state == CLOSED && ((input[i]) == '<' || (input[i]) == '>'))
		{
			rdir = SINGLE_OPEN;
			if (input[i + 1] == '<' || input[i + 1] == '>')
				i++;
		}
		else if (quote_state == CLOSED && rdir == SINGLE_OPEN
			&& ft_isprint(input[i]) == 1 && input[i] != ' ')
			rdir = CLOSED;
		i++;
	}
	return (check_rdir(rdir));
}

// Cette fonction check dans un premier temps les erreurs de syntaxe
// de pipe du style >< <> <<< >>>
// Et dans un second temps, elle appelle une fonction qui check
//si les redirection ont bien chacunes une cible
int	check_redirections(char *input)
{
	int	i;
	int	quote_state;
	int	rdir;

	i = 0;
	quote_state = CLOSED;
	rdir = 0;
	while (input[i] != '\0')
	{
		quote_state = quotes_state(input[i], quote_state);
		if ((quote_state == CLOSED && ((input[i] == '>' && input[i + 1] == '<')
					|| (input[i] == '<' && input[i + 1] == '>'))) || rdir > 2)
			return (0);
		if (quote_state == CLOSED && (input[i] == '<' || input[i] == '>'))
			rdir++;
		else
			rdir = 0;
		i++;
	}
	if (check_empty_redirection(input) == 0)
		return (0);
	return (1);
}

// A làppel de cette fonction, on considere que l'input ne comporte pas
// de caractere speciaux hors de quotes, ni de pipe en debut ou en fin d'input
// les fonctions de check_syntax ont ete appelees avant
// Cette fonction check si || est present dans l'input
// Et si ce qu'il y a entre 2 pipe est vide ou incorrect  cest a dire
// 2 pipes qui ne contiennent pas entre l'un et lautre au moins un caractere
// pouvant correspondre a une commande ou a une cible de redirection
// Le tout en prenant en compte les quotes fermees et ouvertes
int	check_empty_and_double_pipe(char *input)
{
	int	i;
	int	pipe;
	int	quote_state;

	i = 0;
	pipe = CLOSED;
	quote_state = CLOSED;
	while (input[i] != '\0')
	{
		quote_state = quotes_state(input[i], quote_state);
		if (quote_state == CLOSED && input[i] == '|' && input[i + 1] == '|')
			return (0);
		if (quote_state == CLOSED && input[i] == '|')
		{
			if (pipe == CLOSED)
				pipe = SINGLE_OPEN;
			else
				return (0);
		}
		else if (ft_isprint(input[i]) == 1 && input[i] != ' ')
			pipe = CLOSED;
		i++;
	}
	return (1);
}

// Cette fonction check les syntax_error dues aux pipes
// D'abord elle check que le premier carcatere (hors espace) ne soit pas un pipe
// Ensuite elle check que le dernier carcatere(hors espace) ne soit pas un pipe
// Enfin qu'un pipe ne soit pas vide
int	check_pipe_error(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (0);
	i = ft_strlen(input) - 1;
	while (i > 0 && input[i] == ' ')
		i--;
	if (i > 0 && input[i] == '|')
		return (0);
	if (check_empty_and_double_pipe(input) == 0)
		return (0);
	return (1);
}
