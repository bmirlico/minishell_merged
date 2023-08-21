/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:42:19 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/21 16:07:12 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui ouvre les redirections s'il y en a
int	open_rdirs(t_token **redirections, t_command *tmpc, t_pipex vars)
{
	t_token	*tmp;
	int		ret;

	tmp = *redirections;
	ret = 0;
	while (tmp != NULL)
	{
		if ((tmp->type == T_INFILE || tmp->type == T_OUTFILE
				|| tmp->type == T_OUTFILE_APPEND)
			&& (check_bad_env_variable(tmp->str) == 2 || tmp->str[0] == '\0'
				|| !ft_strncmp(tmp->str, "\"\"", 3)))
		{
			tmp->fd = -2;
			return (0);
		}
		ret = handle_open_rdirs(tmp, tmpc, vars);
		if (ret == 1)
			return (ret);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_open_rdirs(t_token *tmp, t_command *tmpc, t_pipex vars)
{
	int	quotes;

	(void)tmpc;
	(void)vars;
	quotes = nb_quotes(tmp->str);
	if (quotes == 0 && check_spaces(tmp->str) > 1)
	{
		close_rdirs(&(tmpc->redirections), tmpc);
		ft_putstr_fd("Ambiguous redirect\n", 2);
		new_return_value(vars.copy_t_env, "1");
		free_vars(vars);
		return (1);
	}
	else if (quotes != 0)
		quote_removing_rdir(tmp, quotes);
	if (tmp->type == T_INFILE)
		tmp->fd = open(tmp->str, O_RDONLY, S_IRUSR);
	else if (tmp->type == T_OUTFILE)
		tmp->fd = open(tmp->str, O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
	else if (tmp->type == T_OUTFILE_APPEND)
		tmp->fd = open(tmp->str, O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR);
	return (0);
}

int	check_spaces(char *str)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			word_count++;
			while (str[i] != ' ' && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (word_count);
}

// fonction appelée ds le child process qui permet de gére les erreurs de rdir
// i.e. les open qui ont échoué (ou le ambiguous redirect, voir avec Clément)
void	handle_errors_rdirs(t_command *tmpc, t_pipex vars, t_token **rdirs)
{
	t_token	*tmp;

	tmp = *rdirs;
	while (tmp != NULL)
	{
		if ((tmp->type == T_INFILE || tmp->type == T_LIMITOR)
			&& ((tmp->fd != -3) && ((tmp->fd < 0
						&& access(tmp->str, F_OK) == -1)
					|| (tmp->fd < 0))))
			check_error_rdirs(tmpc, vars, tmp, rdirs);
		else if ((tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
			&& tmp->fd != -3 && tmp->fd < 0)
			check_error_rdirs(tmpc, vars, tmp, rdirs);
		tmp = tmp->next;
	}
}

void	check_error_rdirs(t_command *tmpc, t_pipex vars, t_token *tmp,
			t_token **rdirs)
{
	char	*error;

	error = NULL;
	if (check_bad_env_variable(tmp->str) == 2)
	{
		error = ft_strjoin(tmp->str, ": bad substitution\n");
		ft_putstr_fd(error, 2);
		free(error);
	}
	else if (tmp->str[0] == '\0')
		ft_putstr_fd("Ambiguous redirect\n", 2);
	else if (!ft_strncmp(tmp->str, "\"\"", 3))
		ft_putstr_fd(" : No such file or directory\n", 2);
	else
		perror(tmp->str);
	close_rdirs(rdirs, tmpc);
	if (vars.nb_pipes > 0)
		close_previous_pipe(vars, tmpc->index);
	close_pipe_and_free(vars, tmpc->index);
}
