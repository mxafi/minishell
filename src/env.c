/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:30:45 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/07 13:28:56 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief env.c contains functions for interfacing with extern char **environ.
 * List of possible interactions:
 * int	env_get_possible_match_count_by_key(char *key)
 * char	*env_get_value_by_key(char *key)
 * void	env_set_value_by_key(char *key, char *value)
 * void	env_unset_key(char *key)
 * void	env_print_list(void)
 */

int	env_get_possible_match_count_by_key(char *key)
{
	//todo
}

char	*env_get_value_by_key(char *key)
{
	//todo
}

void	env_set_value_by_key(char *key)
{
	//todo
}

void	env_unset_key(char *key)
{
	//todo
}

/**
 * @brief Matches the output of the 'env' command
 * on the standard output. (prints out environ)
 */
void	env_print_list(void)
{
	size_t		i;

	i = 0;
	while (g_minishell->envp[i])
	{
		ft_putstr_fd(g_minishell->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
