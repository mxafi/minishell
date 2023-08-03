/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:30:45 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/03 14:48:01 by malaakso         ###   ########.fr       */
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

// int	env_get_possible_match_count_by_key(char *key)
// {
// 	//todo
// }

/**
 * @brief Finds the value part from the given env_var.
 * 
 * @param env_var an environment variable string, with key=value syntax.
 * @return char* to the value part of env_var, or null if value is empty.
 */
char	*env_split_value(char *env_var)
{
	char	*ret;

	ret = ft_strchr(env_var, '=');
	if (!ret)
		return (NULL);
	ret++;
	return (ret);
}

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
	int		key_len;
	char	*tmp;
	char	*new;

	if (!key || !value)
		return ;
	key_len = ft_strlen(key);
	i = 0;
	while (g_minishell->envp[i])
	{
		if (ft_strncmp(g_minishell->envp[i], key, key_len) == 0
			&& g_minishell->envp[i][key_len] == '=')
			break ;
		i++;
	}
	if (!g_minishell->envp[i])
	{
		tmp = ft_strjoin(key, "=");
		if (!tmp)
			exit (1);
		new = ft_strjoin(tmp, value);
		if (!new)
			exit (1);
		free(tmp);
		if (vec_push(&g_minishell->env_vec, new) < 1)
			exit (1);
		return ;
	}
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		exit (1);
	new = ft_strjoin(tmp, value);
	if (!new)
		exit (1);
	free(tmp);
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
	g_minishell->envp = (char **)g_minishell->env_vec.memory;
	g_minishell->envp[i] = NULL;
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
