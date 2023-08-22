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
	printf("\n\t- - - - - - - - - - - - - - - -\n");
	printf("\textract_value_from_dolar_sign:\n\tdollar_sign\t:%s:\n\talphanumeric_part\t:%s:\n",
			dollar_sign, alphanumeric_part);
	printf("\t- - - - - - - - - - - - - - - -\n\n");
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
	if (input_string != dollar_sign && dollar_sign != NULL)
		result_string = ft_substr(input_string, 0, dollar_sign - input_string);
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

	result_string = NULL;
	input = current->content;
	handled_pre_string = FALSE;
	while (input && *input != '\0' && *input != '$')
	{
		printf("________________________________________________________________________________\n");
		dollar_sign = ft_strchr(input, '$');
		if (!dollar_sign)
			break ;
		if (input < dollar_sign && handled_pre_string == FALSE)
		// string before $ is saved here
		{
			result_string = get_string_before_dollar(dollar_sign, input,
					result_string);
			printf("There is a pre_string:\t\n\tdollar_sign\t:%s:\n\tcurrent->content\t:%s:\n\tresult_string\t:%s:\n\n", dollar_sign, current->content, result_string);
			if (!result_string)
				return (CALLOC_FAIL);
		}
		else if (!result_string && handled_pre_string == FALSE)
			result_string = ft_strjoin("", NULL);
		printf("Pres_string handled:\n\tresult_string :%s:\n", result_string); handled_pre_string = TRUE;
		key_value = extract_value_from_dollar_sign(dollar_sign + 1);
			// Returns alphanumeric key including '_' -> excludes $
		printf("Coming from extract_value_from_dollar_sign:\n\tkey_value\t:%s:\n\n", key_value);
		if (ft_strncmp(key_value, "?", 1) == 0) // Handle exit status
		{
			env_value = ft_itoa(g_minishell->exit_status);
			if (env_value == NULL)
			{
				list->error_code = CALLOC_FAIL;
				free(key_value);
				return (CALLOC_FAIL);
			}
		}
		else // get env_value corresponding to the dollar_sign
			env_value = env_get_value_by_key(key_value);
		printf("Returned from env_get_value_by_key:\n\tkey_value\t:%s:\n\tenv_value\t:%s:\n\n", key_value, env_value);
		if (result_string == NULL && env_value)
		{
			current->content = ft_strdup(env_value);
			printf("Result_string == NULL &&  env_value != NULL:\n\tcurrent->content :%s: = ft_strdup(env_value\t:%s:)\n", current->content, env_value);
		}
		else if (result_string && env_value)
		{
			printf("if (result_string && env_value) == TRUE:\n");
			printf("\tBefore ft_strjoin:\tresult_string\t:%s:\n", result_string);
			if (env_value)
				result_string = ft_strjoin(result_string, env_value);
			else
				*result_string = '\0';
			printf("\tAfter ft_strjoin:\tresult_string\t:%s:\n", result_string);
			if (result_string == NULL)
				return (CALLOC_FAIL);
			current->content = ft_strdup(result_string);
			printf("\tcurrent->content\t:%s:\n", current->content);
			if (!current->content)
				return (CALLOC_FAIL);
		}
		else if (!env_value)
		{
			if (!result_string)
			{
				result_string = (char *)ft_calloc(2, sizeof(char));
				if (!result_string)
					return (CALLOC_FAIL);
			}
			current->content = ft_strdup(result_string);
		}
		else
			free(key_value);
		if (ft_strncmp(key_value, "?", 1) == 0)
			free((void *)env_value);
		if (key_value)
			input = dollar_sign + 1;
	}
	//if (key_value)
		//free(key_value);
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
				printf("process_token failed\n");
				list->error_code = CALLOC_FAIL;
				break ;
			}
		}
		current = current->next;
	}
	return (list->error_code);
}
