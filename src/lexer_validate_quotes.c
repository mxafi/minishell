/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:41:02 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/12 15:41:48 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief	Check for quote tokens and delete them
 * @details	If empty quotes were tokenized, a QUOTE_NEED_NULL_STR token type
 * 			was made in place of the closing quote. This particular token type
 * 			is now arbitrarily renamed to STRING and the token content is now 
 *			an empty string.
 *
 * @param token_list The list being checked and holding list information.
 */
void	remove_quote_tokens(t_lexer *token_list)
{
	t_token	*current;
	t_token	*next_token;

	current = token_list->head;
	while (current != NULL)
	{
		next_token = current->next;
		if (current->type == SINGLE_QUOTE || current->type == DOUBLE_QUOTE)
			delete_token(token_list, current);
		if (current->type == QUOTE_NEED_NULL_STR)
		{
			current->type = STRING;
			ft_strlcpy(current->content, "", 1);
		}
		current = current->next;
	}
}
void	expand_env(t_lexer *list, t_token *token, char *env_name)
{
	char	*env_value;
	int		i;
	int		length;

	env_value = NULL;
	i = 0;
	length = ft_strlen(env_name);
	while (environment[i] != NULL)
	{
		if (ft_strncmp(environment[i], env_name, length) == 0)
		{
			if (environment[i][length] == '=')
			{
				env_value = environment[i][length];
				break ;
			}
		}
		i++;
	}
	if (env_value != NULL)
	{
		
	}
}

/**
 * @brief		Implement a function that seeks for a $ and string compare 
 * 				the consecutive chars until the next token. A match in the 
 * 				environment KEYS 
 * 
 *
 * @param list 
 */
void	check_for_double_quote_expansion(t_lexer *list)
{
	t_token	*current;
	char	*env_start;

	current = list->head;
	env_start = NULL;
	while (current != NULL)
	{
		if (current->type == DBL_QUOTE_STR)
		{
			env_start = ft_strchr(current->content + 1, '$');
			if (env_start != NULL)
				expand_env(list, current, env_start + 1);
		}
		current = current->next;
	}
}

/**
 * @brief	Single and double quotes pair checker.
 * @details In the tokenization process, in order to label tokens as quoted
 * 			strings the state of opened quotes labelled as single SGL or double
 * 			DBL *_QUOTE_OPENED or *_QUOTE_CAN_BE_CLOSED) is kept in the
 *			token_list->state placeholder. If this state remains, the syntax
 *			validation process is printing a corresponding syntax error, if 
 *			quotes are present, but have matching closing quote,
 *			token_list->state is UNDEFINED. This is not a bash behaviour but
 *			a requisite from the subject.
 *			- Checks for empty quotes to insert null string
 *			- Checks double quote for expansion
 * @param 	token_list List of token being checked
 * @return	t_return_value Failure or Success 
 */
t_return_value	validate_quotes(t_lexer *token_list)
{
	if (token_list->state == SGL_QUOTE_CAN_BE_CLOSED ||
		token_list->state == SGL_QUOTE_OPENED)
	{
		printf("Shellfish> syntax error expecting closing single quotes `\''\n");
		token_list -
			return (FAILURE);
	}
	else if (token_list->state == DBL_QUOTE_CAN_BE_CLOSED ||
				token_list->state == DBL_QUOTE_OPENED)
	{
		printf("Shellfish> syntax error expecting closing double quotes `\"'\n");
		return (FAILURE);
	}
	remove_quote_tokens(token_list);
	check_for_double_quote_expansion(token_list);
	return (SUCCESS);
}
