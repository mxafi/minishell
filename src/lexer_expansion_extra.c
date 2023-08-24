/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:33:51 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/24 18:46:00 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Handles the exit status for environment variables.
 * 
 * @param env_value The environment value to be updated.
 * @param list The lexer list containing the tokens.
 * @param key_value The key value for the environment variable.
 */
static void	handle_exit_status(const char **env_value, t_lexer *list,
		char *key_value)
{
	char	*exit_status_value;

	exit_status_value = ft_itoa(g_minishell->exit_status);
	if (!exit_status_value)
	{
		list->error_code = MALLOC_FAIL;
		free(key_value);
		return ;
	}
	*env_value = exit_status_value;
}

/**
 * @brief Handles environment variable expansion based on key value.
 *
 * @details This function handles environment variable expansion by evaluating
 * the given key value. If the key value is "$", it returns a string containing
 * "$" to represent a literal dollar sign. If the key value is "?", it handles
 * the exit status and updates the env_value accordingly. Otherwise, it looks
 * up the environment value by the key and returns it.
 *
 * @param key_value The key value extracted from the environment variable key.
 * @param list The lexer list containing context information.
 * @return A pointer to the resulting environment value.
 */
const char	*handle_expansion(char *key_value, t_lexer *list)
{
	const char	*env_value;

	if (key_value && ft_strncmp(key_value, "$", 2) == 0)
		env_value = ft_strdup("$");
	else if (ft_strncmp(key_value, "?", 2) == 0)
		handle_exit_status(&env_value, list, key_value);
	else
		env_value = env_get_value_by_key(key_value);
	return (env_value);
}

/**
 * @brief Retrieves the substring of input_string before the dollar sign.
 *
 * @param dollar_sign The position of the dollar sign.
 * @param input_string The input string.
 * @param result_string The result string before the dollar sign.
 * @return A pointer to the extracted substring.
 */
static char	*get_string_before_dollar(char *dollar_sign, char *input_string,
		char *result_string)
{
	char	*tmp;

	if (input_string != dollar_sign && dollar_sign != NULL)
		tmp = ft_substr(input_string, 0, dollar_sign - input_string);
	else
		return (result_string);
	if (result_string)
		free(result_string);
	return (tmp);
}

/**
 * @brief Constructs the result string before the dollar sign.
 *
 * @param input The input string.
 * @param dollar_sign The position of the dollar sign.
 * @param result_string The existing result string.
 * @param handled_pre_string Flag indicating if a string before
 * dollar sign is handled.
 * @return A pointer to the constructed result string.
 */
char	*get_result_string(char *input, char *dollar_sign,
			char *result_string, t_bool handled_pre_string)
{
	char	*tmp;

	if (input < dollar_sign && (handled_pre_string == FALSE))
		tmp = get_string_before_dollar(dollar_sign, input, result_string);
	else if (!result_string && (handled_pre_string == FALSE))
		tmp = ft_strdup("");
	else
		tmp = ft_strdup(result_string);
	if (result_string)
		free(result_string);
	return (tmp);
}
