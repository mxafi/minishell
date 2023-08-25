/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion_process_token_utils.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 06:00:37 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/25 08:57:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_return_value	env_value_exist(
	char **result_string, t_token *current, const char *env_value)
{
	if (*result_string == NULL)
	{
		if (current->content)
			free(current->content);
		current->content = ft_strdup(env_value);
		if (!current->content)
			return (MALLOC_FAIL);
	}
	else
		*result_string = handle_env_value(*result_string,
				env_value, current);
	return (SUCCESS);
}

static t_return_value	env_value_is_null(
	char **result_string, t_token *current)
{
	if (!*result_string)
	{
		*result_string = (char *)ft_calloc(2, sizeof(char));
		if (!*result_string)
			return (MALLOC_FAIL);
	}
	if (current->content)
		free(current->content);
	current->content = ft_strdup(*result_string);
	if (!current->content)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

static t_return_value	init_env_and_key(
	char **key_value, const char **env_value,
	char *dollar_sign)
{
	t_return_value	expansion_ret_val;

	*key_value = extract_value_from_dollar_sign(dollar_sign + 1);
	*env_value = handle_expansion(*key_value, &expansion_ret_val);
	if (expansion_ret_val == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

static void	move_input_free_key(
	char **input, char *key_value, char *dollar_sign)
{
	*input = dollar_sign + 1;
	free(key_value);
}

t_return_value	process_token_single(t_token *current, char **input,
	char **result_string, t_bool *handled_pre_string)
{
	char			*dollar_sign;
	char			*key_value;
	const char		*env_value;

	dollar_sign = ft_strchr(*input, '$');
	if (!dollar_sign)
		return (BREAK);
	*result_string = get_result_string(*input, dollar_sign,
			*result_string, *handled_pre_string);
	if (!*result_string)
		return (MALLOC_FAIL);
	*handled_pre_string = TRUE;
	if (init_env_and_key(&key_value, &env_value, dollar_sign) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (env_value && (
			env_value_exist(result_string, current, env_value) == MALLOC_FAIL))
		return (MALLOC_FAIL);
	else if (env_value_is_null(result_string, current) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((ft_strncmp(key_value, "?", 2) == 0 || ft_strncmp(key_value,
				"$", 2) == 0) && env_value)
		free((void *)env_value);
	if (key_value)
		move_input_free_key(input, key_value, dollar_sign);
	return (SUCCESS);
}
