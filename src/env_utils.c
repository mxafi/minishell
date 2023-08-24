/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:30:46 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 11:11:58 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*env_utils_join_three_str(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
	{
		perror("shellfishy: ");
		exit(1);
	}
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	if (!ret)
	{
		perror("shellfishy: ");
		exit(1);
	}
	return (ret);
}

size_t	env_utils_ret_key_idx(char *key)
{
	size_t	i;
	int		key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (g_minishell->envp[i])
	{
		if (ft_strncmp(g_minishell->envp[i], key, key_len) == 0
			&& g_minishell->envp[i][key_len] == '=')
			break ;
		i++;
	}
	return (i);
}

void	envp_init_vars(size_t i)
{
	g_minishell->env_vec.len = i + 1;
	g_minishell->envp = (char **)g_minishell->env_vec.memory;
	g_minishell->envp[i] = NULL;
}
