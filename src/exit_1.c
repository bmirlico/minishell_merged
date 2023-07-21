/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:05:01 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/03 16:10:11 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Commande builtin EXIT
void	built_in_exit(t_command *tmp)
{
	int			len_tab;
	long long	exit_code;
	char		*error_str;

	len_tab = get_len_tab(tmp->cmd_args);
	exit_code = ft_strtoll(tmp->cmd_args[1]);
	error_str = NULL;
	ft_printf("exit\n");
	conditions_exit(tmp, exit_code, error_str, len_tab);
}

// fonction qui regroupe tous les cas d'exit à gérer
// faite pour passer la norminette
void	conditions_exit(t_command *tmp, long long exit_code, char *error_str,
		int len_tab)
{
	if (len_tab == 1)
		exit(0);
	else if (is_out_of_range(exit_code, tmp->cmd_args[1])
		|| is_numeric(tmp->cmd_args[1]) == 0)
	{
		exit_non_numeric(&error_str, tmp->cmd_args[1]);
		ft_putstr_fd(error_str, 2);
		exit(2);
	}
	else if (len_tab > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		errno = 1;
	}
	else
	{
		if (!(exit_code >= 0 && exit_code <= 255))
			exit_code %= 256;
		exit(exit_code);
	}
}

// fonction qui check si l'argument d'exit est bien un nombre
int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if ((str[i] == '-' && str[i + 1] == '-')
			|| (str[i] == '-' && str[i + 1] == '+')
			|| (str[i] == '+' && str[i + 1] == '-')
			|| (str[i] == '+' && str[i + 1] == '+'))
			return (0);
		else if ((str[i] == '-' || str[i] == '+')
			&& str[i + 1] == '\0')
			return (0);
		else if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

// fonction qui concatene le message d'erreur dans le cas ou
// l'argument d'exit n'est pas un nombre
void	exit_non_numeric(char **error, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(str, ": numeric argument required\n");
	*error = ft_strjoin("exit: ", tmp);
	free(tmp);
}

// fonction qui check bien que si on dépasse LONG_MAX ou LONG_MIN
// on rentre dans un cas d'erreur d'exit
int	is_out_of_range(long long exit_code, char *str)
{
	int	len;

	len = ft_strlen(str);
	if ((exit_code == LONG_MAX
			&& ft_strncmp(str, "9223372036854775807", len + 1))
		|| (exit_code == LONG_MIN
			&& ft_strncmp(str, "-9223372036854775808", len + 1)))
		return (1);
	else
		return (0);
}
