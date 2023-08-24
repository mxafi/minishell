/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:33:51 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/24 14:34:33 by lclerc           ###   ########.fr       */
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