/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/14 18:09:37 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// VALGRIND
// valgrind --track-fds=yes --leak-check=full
// --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp ./minishell

// Ex. commande : ls > outfile -l -a | wc -l > test | cat

// main du projet minishell
int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*env;

	(void)av;
	env = NULL;
	if (ac > 1)
		return (ft_printf("No arguments required to launch the shell.\n"), 1);
	dup_env(envp, &env);
	while (1)
	{
		signal_action();
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_printf("exit\n");
			free_envlst(&env);
			exit (0);
		}
		minishell(env, input);
		free(input);
		//g_sig = 0;
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

	init_lists(&lst, &lst_j, &cmds);
	if (ft_strlen(input) > 0)
		add_history(input);
	if (check_syntax(input) == 1)
	{
		lexer_char(&lst, input);
		lexer_str(&lst, &lst_j);
		parser(&lst_j, &cmds);
		expand(env, &cmds);
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
