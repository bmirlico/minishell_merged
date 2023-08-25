/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:42 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/25 17:50:07 by bmirlico         ###   ########.fr       */
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
	g_sig = 0;
	while (1)
	{
		signal_action();
		input = readline("minishell$ ");
		ctrld(input, &env);
		reset_global_var(&g_sig, env);
		minishell(env, input);
		free(input);
	}
	free_envlst(&env);
	return (0);
}

void	reset_global_var(int *g_sig, t_env *env)
{
	if (*g_sig == 130)
		new_return_value(env, "130");
	*g_sig = 0;
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
		check_execution(input, vars);
		free_lists(&lst, &lst_j, &cmds);
	}
	else
		new_return_value(env, "2");
}

// pour la norme ds la fonction minishell
void	check_execution(char *input, t_pipex vars)
{
	if (input != NULL && ft_strlen(input) > 0)
		execution(vars);
	else
	{
		g_sig = 0;
		free_tab(vars.copy_env_tmp);
	}
}

// gestion du CTRL + D
void	ctrld(char *input, t_env **env)
{
	int	dollar;

	dollar = 0;
	if (input == NULL)
	{
		ft_printf("exit\n");
		dollar = ft_atoi(get_env(*env, "?"));
		free_envlst(env);
		if (g_sig == 130 || g_sig == 1)
			exit (130);
		else
			exit (dollar);
	}
}
