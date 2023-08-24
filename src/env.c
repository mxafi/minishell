/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:30:45 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 09:34:40 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Finds a value for a specific key.
 * 
 * @param key the key of the environment variable.
 * @return const char* the value of the environment variable,
 * it must not be freed or modified.
 */
const char	*env_get_value_by_key(const char *key)
{
	size_t	i;
	int		key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (g_minishell->envp[i])
	{
		if (ft_strncmp(g_minishell->envp[i], key, key_len) == 0
			&& g_minishell->envp[i][key_len] == '=')
		{
			return (env_split_value(g_minishell->envp[i]));
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief Sets an environment variable to a specific value.
 * 
 * 
 * @param key 
 * @param value 
 */
void	env_set_value_by_key(char *key, char *value)
{
	size_t	i;
	char	*new;

	if (!key || !value)
		return ;
	i = env_utils_ret_key_idx(key);
	if (!g_minishell->envp[i])
	{
		new = env_utils_join_three_str(key, "=", value);
		if (vec_insert(&g_minishell->env_vec,
				&new, g_minishell->env_vec.len - 1) < 1)
			exit(1);
		g_minishell->envp = (char **)g_minishell->env_vec.memory;
		return ;
	}
	new = env_utils_join_three_str(key, "=", value);
	free(g_minishell->envp[i]);
	g_minishell->envp[i] = new;
}

void	env_unset_key(char *key)
{
	size_t	i;
	int		key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (g_minishell->envp[i])
	{
		if (ft_strncmp(g_minishell->envp[i], key, key_len) == 0
			&& g_minishell->envp[i][key_len] == '=')
		{
			break ;
		}
		i++;
	}
	if (!g_minishell->envp[i])
		return ;
	free(g_minishell->envp[i]);
	vec_remove(&g_minishell->env_vec, i);
	g_minishell->envp = (char **)g_minishell->env_vec.memory;
}

/**
 * @brief Matches the output of the 'env' command
 * on the standard output. (prints out environ)
 */
void	env_print_list(void)
{
	size_t	i;

	i = 0;
	while (g_minishell->envp[i])
	{
		ft_putstr_fd(g_minishell->envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

/**
 * @brief Takes the extern char** environ and copies it to a vector.
 * The char** envp is also set to point to the created vector's memory.
 * 
 * @return int 0 on success, 1 on fail.
 */
int	init_envp(void)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	while (environ[i])
		i++;
	if (vec_new(&g_minishell->env_vec, i + 1, sizeof(char *)) < 1)
	{
		perror("init_envp");
		return (1);
	}
	envp_init_vars(i);
	i = 0;
	while (environ[i])
	{
		g_minishell->envp[i] = ft_strdup(environ[i]);
		if (!g_minishell->envp[i])
		{
			perror("init_envp");
			return (1);
		}
		i++;
	}
	return (0);
}
