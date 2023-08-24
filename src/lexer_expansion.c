/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:24:25 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/18 13:49:03lclerc           ###   ########.fr       */
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
		//printf("________________________________________________________________________________\n");
		dollar_sign = ft_strchr(input, '$');
		if (!dollar_sign)
			break ;
		if (!(result_string = get_result_string(input, dollar_sign,
					result_string, handled_pre_string)))
			return (MALLOC_FAIL);
		//printf("process_token:\n\tget_result_string: result_string :%s:\n", result_string);
		handled_pre_string = TRUE;
		key_value = extract_value_from_dollar_sign(dollar_sign + 1);
		env_value = handle_expansion(key_value, list);
		//printf("check what is in env_value :%s:\n", env_value);
		if (env_value)
		{
			if (result_string == NULL)
			{
				if (current->content)
					free(current->content);
				current->content = ft_strdup(env_value);
			}
			else
				result_string = handle_env_value(result_string, env_value,
						current);
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
		if (ft_strncmp(key_value, "?", 2) == 0 || ft_strncmp(key_value, "$",
				2) == 0)
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
 * @brief	Expands environment variables within double-quoted strings or 
 *			regular strings with KEYs in environment variables.
 * @details	Expands environment variables within double-quoted strings or 
 * regular strings that contain environment keys. It searches for the 
 * occurrence of environment variables indicated by a `$` symbol within 
 * tokens. It retrieves the corresponding values from the environment and
 * updates the token content accordingly. The searched string starts after 
 * the `$` sign and extends until the next token or the next non-alphanumeric 
 * character. If the environment key does not match an existing environment 
 * variable, the expanded content is set to a null string. Some examples:
 *				- echo $USER -> username (expands to)
 * 				- echo $USER123 -> unless USER123 exists, bash returns '\n'
 *				- echo $USER+^ -> username+^ (expands to and concatenate non
 *					alphanumeric char to it)
 *
 * @param list	The lexer list containing the tokens to process
 */
t_return_value	expand_from_env(t_lexer *list)
{
	t_token	*current;
	t_token	*previous;
	t_token	*temp;
	t_bool	delete_null_expanded_token;

	current = list->head;
	previous = NULL;
	delete_null_expanded_token = FALSE;
	while (current != NULL)
	{
		print_list(list);
		if (current->type == DBL_QUOTE_STR || current->type == STRING)
		{
			if (process_token(list, current) != SUCCESS)
			{
				printf("process_token MALLOC_FAIL\n");
				list->error_code = MALLOC_FAIL;
				break ;
			}
			else if (previous == NULL && current->type = MY_SPACE)
			{
				temp = current->next; 
				delete_token(list, current);
				current = temp;
			}
			else if (previous == NULL && ft_strncmp(current->content, "", 1) == 0)
				delete_null_expanded_token = TRUE;
		}
		if (delete_null_expanded_token == TRUE)
		{
			if (current->next)
		 	{
				temp = current->next;
				delete_token(list, current);
				current = temp;
		 	}
			else
			{
				delete_token(list, current);
				return (INVALID_EXPANSION);
			}
		}
		else
		{
			previous = current;
			current = current->next;
		}
		delete_null_expanded_token = FALSE;
	}
	return (list->error_code);
}
