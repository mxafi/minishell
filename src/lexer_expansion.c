/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:24:25 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/24 19:04:45 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Extracts the alphanumeric part of an environment variable key.
 * 
 * @details This function extracts the alphanumeric part of an environment
 * variable key, which is used for variable expansion. If the key starts with
 * '?', it returns a string containing '?' to represent the exit status. If the
 * key is alphanumeric, including underscores, it extracts the continuous
 * alphanumeric characters until a non-alphanumeric character is encountered.
 * 
 * @param dollar_sign The environment variable key to extract from.
 * @return A dynamically allocated string containing the extracted alphanumeric
 * part. The caller is responsible for freeing the memory.
 */
static char	*extract_value_from_dollar_sign(const char *dollar_sign)
{
	int		i;
	char	*alphanumeric_part;

	if (dollar_sign[0] == '\0')
	{
		alphanumeric_part = ft_strdup("$");
		return (alphanumeric_part);
	}
	if (dollar_sign[0] == '?')
	{
		alphanumeric_part = ft_strdup("?");
		return (alphanumeric_part);
	}
	i = 0;
	while (dollar_sign[i] != '\0')
	{
		if (ft_isalnum(dollar_sign[i]) == 0 && dollar_sign[i] != '_')
			break ;
		i++;
	}
	alphanumeric_part = ft_substr(dollar_sign, 0, i);
	return (alphanumeric_part);
}

/**
 * @brief Handles the concatenation of environment value with result string.
 * 
 * @param result_string The string to which the environment value is appended.
 * @param env_value The environment value to append.
 * @param current The current token.
 * @return char* The updated result string.
 */
static char	*handle_env_value(char *result_string, const char *env_value,
		t_token *current)
{
	char	*tmp;

	if (result_string && env_value)
	{
		tmp = ft_strjoin(result_string, env_value);
		if (!tmp)
			return (NULL);
		free(result_string);
		result_string = tmp;
	}
	else
	{
		if (result_string)
			free(result_string);
		result_string = ft_strdup("");
		if (!result_string)
			return (NULL);
	}
	if (current->content)
		free(current->content);
	current->content = ft_strdup(result_string);
	if (!current->content)
		return (NULL);
	return (result_string);
}

/**
 * @brief Processes a token for environment variable expansion.
 * 
 * @details This function processes a token for environment variable expansion.
 * It checks if the token contains a '$' symbol and if so, extracts the
 * alphanumeric part of the environment variable key. If the extracted part is
 * '?', it replaces it with the exit status value. Otherwise, it retrieves the
 * environment value by the key and concatenates the expanded content. It frees
 * the memory of the extracted alphanumeric part.
 * 
 * @param current The current token to process.
 */
static t_return_value	process_token(t_lexer *list, t_token *current)
{
	char		*dollar_sign;
	char		*key_value;
	char		*result_string;
	char		*input;
	const char	*env_value;
	t_bool		handled_pre_string;
	char		*input_origin;

	result_string = NULL;
	input = ft_strdup(current->content);
	if (!input)
		return (MALLOC_FAIL);
	input_origin = input;
	handled_pre_string = FALSE;
	while (input && *input != '\0')
	{
		dollar_sign = ft_strchr(input, '$');
		if (!dollar_sign)
			break ;
		if (!(result_string = get_result_string(input, dollar_sign,
					result_string, handled_pre_string)))
			return (MALLOC_FAIL);
				handled_pre_string = TRUE;
				key_value = extract_value_from_dollar_sign(dollar_sign + 1);
				env_value = handle_expansion(key_value, list);
				if (env_value)
				{
					if (result_string == NULL)
					{
						if (current->content)
							free(current->content);
						current->content = ft_strdup(env_value);
					}
					else
						result_string = handle_env_value(result_string,
								env_value, current);
				}
				else if (!env_value)
				{
					if (!result_string)
					{
						result_string = (char *)ft_calloc(2, sizeof(char));
						if (!result_string)
							return (MALLOC_FAIL);
					}
					if (current->content)
						free(current->content);
					current->content = ft_strdup(result_string);
					if (!current->content)
						return (MALLOC_FAIL);
				}
				else
				{
					if (key_value)
						free(key_value);
				}
				if (ft_strncmp(key_value, "?", 2) == 0 || ft_strncmp(key_value,
						"$", 2) == 0)
				{
					if (env_value)
						free((void *)env_value);
				}
				if (key_value)
				{
					input = dollar_sign + 1;
					free(key_value);
				}
	}
	if (input_origin)
		free(input_origin);
	if (result_string)
		free(result_string);
	return (SUCCESS);
}

/**
 * @brief Deletes a token with null content from the token list and updates 
 * error code.
 *
 * @details Deletes the given token from the token list and updates the error 
 * code if needed. If the token is not the last one, it's replaced with the 
 * following token. If it's the last token, the error code is set to 
 * `INVALID_EXPANSION`.
 *
 * @param list The lexer list containing the tokens.
 * @param current The token to be deleted.
 * @return The updated error code.
 */

static t_return_value	delete_null_expanded_token(t_lexer *list, t_token *current)
{
	t_token	*temp;

	if (current->next)
	{
		temp = current->next;
		delete_token(list, current);
		current = temp;
	}
	else if (list->head != current)
		delete_token(list, current);
	else
	{
		delete_token(list, current);
		list->error_code = INVALID_EXPANSION;
	}
	return (list->error_code);
}

/**
 * @brief Expands environment variables within double-quoted strings or regular
 * strings with keys from environment variables.
 *
 * @details This function processes the tokens in the lexer list, searching for
 * double-quoted strings or regular strings containing environment variable 
 * keys. It expands environment variables indicated by a `$` symbol within 
 * tokens. The expanded content is retrieved from the environment and updates 
 * the token content accordingly. The search for the environment key starts 
 * after the `$` sign and extends until the next token or the next non-
 * alphanumeric character. If the environment key does not match an existing 
 * environment variable, the expanded content is set to an empty string.
 *
 * @param list The lexer list containing the tokens to process.
 * @return The return value indicating the success or failure of the expansion.
 */
t_return_value	expand_from_env(t_lexer *list)
{
	t_token	*current;

	current = list->head;
	while (current != NULL)
	{
		if (current->type == DBL_QUOTE_STR || current->type == STRING)
		{
			if (process_token(list, current) != SUCCESS)
			{
				list->error_code = MALLOC_FAIL;
				break ;
			}
			else if (ft_strncmp(current->content, "", 1) == 0)
			{
				if (delete_null_expanded_token(list, current) != SUCCESS)
					return (list->error_code);
			}
		}
		current = current->next;
	}
	return (list->error_code);
}
