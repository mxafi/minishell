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
			// Characters test fails
			break ;
		i++;
	}
	alphanumeric_part = ft_substr(dollar_sign, 0, i);
	//printf("\n<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-\n");
	//printf("extract_value_from_dolar_sign:\n\tdollar_sign\t\t:%s:\n\talphanumeric_part\t:%s:\n", dollar_sign, alphanumeric_part);
	//printf("<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-<>-\n");
	return (alphanumeric_part);
}

/**
 * @brief 
 * 
 * 
 * @param dollar_sign 
 * @param input_string 
 * @param result_string 
 * @return 
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
 * @brief 
 * 
 * 
 * @param input 
 * @param dollar_sign 
 * @param result_string 
 * @param handled_pre_string 
 * @return 
 */
static char	*get_result_string(char *input, char *dollar_sign,
		char *result_string, t_bool handled_pre_string)
{
	char	*tmp;

	//printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	//printf("get_result_string:\n\tinput\t\t\t:%s:\n\tdollar_sign\t\t:%s:\n\tresult_string\t\t:%s:\nhandled_pres_string\t:%u:\n", input, dollar_sign, result_string, handled_pre_string);
	if (input < dollar_sign && (handled_pre_string == FALSE))
		tmp = get_string_before_dollar(dollar_sign, input, result_string);
	else if (!result_string && (handled_pre_string == FALSE))
		tmp = ft_strdup("");
	else
		tmp = ft_strdup(result_string);
	//printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	if (result_string)
		free(result_string);
	return (tmp);
}

/**
 * @brief 
 * 
 * 
 * @param result_string 
 * @param env_value 
 * @param current 
 * @return 
 */
static char	*handle_env_value(char *result_string, const char *env_value,
		t_token *current)
{
	char	*tmp;

	//printf("Handle_env_value:\n\tresult_string\t:%s:\n\tenv_value\t:%s:\n\tcurrent->content\t:%s:\n", result_string, env_value, current->content);
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
 * @brief 
 * 
 * 
 * @param env_value 
 * @param list 
 * @param key_value 
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

static const char	*handle_expansion(char *key_value, t_lexer *list)
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
		if (!(result_string = get_result_string(input, dollar_sign, result_string, handled_pre_string)))
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
				result_string = handle_env_value(result_string, env_value, current);
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
				return(MALLOC_FAIL);
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

	current = list->head;
	while (current != NULL)
	{
		if (current->type == DBL_QUOTE_STR || current->type == STRING)
		{
			if (process_token(list, current) != SUCCESS)
			{
				printf("process_token MALLOC_FAIL\n");
				list->error_code = MALLOC_FAIL;
				break ;
			}
		}
		current = current->next;
	}
	return (list->error_code);
}
