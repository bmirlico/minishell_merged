/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirs_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:27:11 by bmirlico          #+#    #+#             */
/*   Updated: 2023/08/25 12:20:22 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// fonction qui ferme les redirections
void	close_rdirs(t_token **redirections, t_command *tmp)
{
	t_token	*temp;

	temp = *redirections;
	if (is_bad_subst_cmd(tmp))
		return ;
	while (temp != NULL)
	{
		if (temp->type == T_INFILE || temp->type == T_OUTFILE
			|| temp->type == T_OUTFILE_APPEND || temp->type == T_LIMITOR)
		{
			if (check_bad_env_variable(temp->str) == 2 || temp->str[0] == '\0')
				return ;
			if (temp->fd >= 0)
				close(temp->fd);
		}
		temp = temp->next;
	}
}

// fonction qui ferme les redirections
void	close_rdirs_heredocs(t_pipex vars)
{
	t_command	*tmp;
	t_token		*temp;

	tmp = *(vars.copy_cmds);
	while (tmp != NULL)
	{
		temp = tmp->redirections;
		close_rdirs(&temp, tmp);
		tmp = tmp->next;
	}
}

void	open_heredocs(t_pipex *vars)
{
	t_command	*tmp;
	t_token		*temp;
	int			quotes;

	tmp = *(vars->copy_cmds);
	while (tmp != NULL)
	{
		temp = tmp->redirections;
		while (temp != NULL)
		{
			if (temp->type == T_LIMITOR)
			{
				temp->fd = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR);
				quotes = nb_quotes(temp->str);
				if (quotes != 0)
					quote_removing_rdir(temp, quotes);
				fill_heredoc(temp, tmp, vars, quotes);
				if (g_sig == 1)
					return ;
			}
			temp = temp->next;
		}
		tmp = tmp->next;
	}
}

void	expand_heredoc(char **str, t_pipex *vars)
{
	int		new_len;
	char	*new;
	int		var_env_len;

	new_len = 0;
	new = NULL;
	var_env_len = 0;
	if (*str == NULL)
		return ;
	if (to_be_modified(*str) == 0)
	{
		var_env_len = get_varenv_value_len(vars->copy_t_env, *str);
		new_len = ft_strlen(*str) - get_varname_len(*str) + var_env_len;
		new = ft_calloc(sizeof(char), (new_len + 1));
		if (new == NULL)
			return ;
		new[new_len] = '\0';
		new_str(vars->copy_t_env, *str, new);
		if (*str)
			free(*str);
		*str = new;
	}
	else if (!is_varenv_in_single_quote(*str))
		expand_single_quote(str, vars);
}

// fonction qui remplit le fichier tmp/here_doc avec le contenu du heredoc
void	fill_heredoc(t_token *tmp, t_command *tmpc, t_pipex *vars, int quotes)
{
	char	*str;
	int		fd_tmp;
	int		old_stdin;

	set_heredoc(&fd_tmp, &old_stdin);
	while (1)
	{
		str = readline("> ");
		check_and_expand_heredoc(quotes, vars, &str);
		if (g_sig == 1)
		{
			close_heredoc_sigint(fd_tmp, old_stdin, tmpc);
			new_return_value(vars->copy_t_env, "130");
			return ;
		}
		else if (str == NULL)
			handle_ctrld(fd_tmp, *vars, tmpc, old_stdin);
		else if (!ft_strncmp(str, tmp->str, ft_strlen(tmp->str) + 1))
		{
			close_heredoc_(fd_tmp, tmpc, old_stdin);
			return ;
		}
		put_in_heredoc(&str, fd_tmp);
	}
}
