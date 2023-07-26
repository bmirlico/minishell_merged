/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/26 17:37:49 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// VALGRIND
// valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp ./minishell

// Ex. commande : ls > outfile -l -a | wc -l > test | cat

// main du projet minishell
int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*env;
	char		*exit_sig;

	(void)av;
	env = NULL;
	if (ac > 1)
		return (ft_printf("No arguments required to launch the shell.\n"), 1);
	dup_env(envp, &env);
	while (1)
	{
		signal_action();
		input = readline("minishell$ ");
		exit_sig = ft_itoa(g_sig);
		if (g_sig == 130 || g_sig == 131)
			new_return_value(env, exit_sig);
		free(exit_sig);
		if (input == NULL)
		{
			ft_printf("exit\n");
			free_envlst(&env);
			exit (0);
		}
		minishell(env, input);
		free(input);
	}
	free_envlst(&env);
	return (0);
}

// fonction minishell qui cree tokenise l'input et cree les listes
void	minishell(t_env *env, char *input)
{
	t_token		*lst;
	t_token		*lst_j;
	t_command	*cmds;
	t_pipex		vars;

	lst = create_list_lexer();
	lst_j = create_list_lexer();
	cmds = create_list_parser();
	if (ft_strlen(input) > 0)
		add_history(input);
	if (check_syntax(input) == 1)
	{
		if (!ft_strncmp(input, "stop", ft_strlen(input) + 1))
		{
			free(input);
			free_envlst(&env);
			exit (0);
		}
		lexer_char(&lst, input);
		lexer_str(&lst, &lst_j);
		parser(&lst_j, &cmds);
		expand(env, &cmds);
		//display_parser(&cmds);
		vars.copy_t_env = env;
		vars.copy_env_tmp = create_env_tab(env);
		copy_lists(&vars, &lst, &lst_j, &cmds);
		if (input != NULL)
			execution(vars);
		free_lists(&lst, &lst_j, &cmds);
	}
	else
		new_return_value(env, "2");
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
