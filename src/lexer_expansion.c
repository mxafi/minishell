/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:24:25 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/11 09:42:12 by lclerc           ###   ########.fr       */
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
 * @param env_key The environment variable key to extract from.
 * @return A dynamically allocated string containing the extracted alphanumeric
 * part. The caller is responsible for freeing the memory.
 */
static char	*extract_alphanumeric_part(const char *env_key)
{
	int		i;
	char	*alphanumeric_part;

	if (env_key[0] == '?')
	{
		alphanumeric_part = ft_strdup("?");
		return alphanumeric_part;
	}
	i = 0;
	while (env_key[i] != '\0')
	{
		if (ft_isalnum(env_key[i]) == 0 && env_key[i] != '_')
			break ;
		i++;
	}
	alphanumeric_part = ft_substr(env_key, 0, i);
	return (alphanumeric_part);
}

/**
 * @brief 	Concatenates the expanded content of the token.
 * @details	This function concatenates the expanded content of the token by 
 * 			joining the environment value and the non-alphanumeric part. It 
 * 			updates the content of the token accordingly.
 * 
 * @param current			The current token to process. 
 * @param env_value			The environment value to concatenate.
 * @param non_alnum_part	The non-alphanumeric part of the token.
 */
static void	concatenate_expanded_content(t_token *current,
											const char *env_value,
											const char *non_alnum_part)
{
	char	*expanded_content;
	char	*new_content;

	expanded_content = ft_strjoin(env_value, non_alnum_part);
	new_content = NULL;
	if (expanded_content != NULL)
	{
		new_content = ft_strdup(expanded_content);
		free(expanded_content);
	}
	if (new_content != NULL)
	{
		free(current->content);
		current->content = new_content;
	}
	else
	{
		free(current->content);
		current->content = ft_strdup("");
	}
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
static void	process_token(t_token *current)
{
	char		*env_key;
	char		*alpha_part;
	char		*non_alpha_part;
	const char	*env_value;

	env_key = ft_strchr(current->content, '$');
	if (env_key != NULL)
	{
		alpha_part = extract_alphanumeric_part(env_key + 1);
		printf("\n\nalpha_part is %s\n\n", alpha_part);
		if (ft_strncmp(alpha_part, "?", 1) == 0)
			env_value = ft_itoa(g_minishell->exit_status);
		else
			env_value = env_get_value_by_key(alpha_part);
		non_alpha_part = env_key + 1 + ft_strlen(alpha_part);
		concatenate_expanded_content(current, env_value, non_alpha_part);
		free(alpha_part);
	}
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
void	expand_from_env(t_lexer *list)
{
	t_token	*current;

	current = list->head;
	while (current != NULL)
	{
		if (current->type == DBL_QUOTE_STR || current->type == STRING)
		{
			process_token(current);
		}
		current = current->next;
	}
}
