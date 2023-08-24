/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:41:02 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/17 11:08:10by lclerc           ###   ########.fr       */
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
static void	remove_quote_tokens(t_lexer *token_list)
{
	t_token	*current;
	t_token	*temp;

	current = token_list->head;
	while (current != NULL)
	{
		if (current->type == SINGLE_QUOTE || current->type == DOUBLE_QUOTE)
		{
			temp = current->next;
			delete_token(token_list, current);
			current = temp;
		}
		else
			current = current->next;
	}
}

/**
 * @brief Add null string for empty quotes.
 *
 * @param token_list The list being checked and holding list information.
 */
static void	add_null_string_for_empty_quotes(t_lexer *token_list)
{
	t_token	*current;

	current = token_list->head;
	while (current != NULL)
	{
		if (current->type == QUOTE_NEED_NULL_STR)
		{
			current->type = STRING;
			ft_strlcpy(current->content, "", 1);
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
 *			validation process is printing a corresponding syntax error. If 
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
	if (token_list->state == SGL_QUOTE_CAN_BE_CLOSED
		|| token_list->state == SGL_QUOTE_OPENED)
	{
		ft_putstr_fd("☠️  shellfishy ☠️  > syntax error: expecting closing "
			"single quotes `\''\n", STDERR_FILENO);
		token_list->error_code = EXIT_SYNTAX_ERROR;
		return (token_list->error_code);
	}
	else if (token_list->state == DBL_QUOTE_CAN_BE_CLOSED
		|| token_list->state == DBL_QUOTE_OPENED)
	{
		ft_putstr_fd("☠️  shellfishy ☠️  > syntax error: expecting closing "
			"double quotes `\"'\n", STDERR_FILENO);
		token_list->error_code = EXIT_SYNTAX_ERROR;
		return (token_list->error_code);
	}
	remove_quote_tokens(token_list);
	add_null_string_for_empty_quotes(token_list);
	token_list->error_code = SUCCESS;
	return (token_list->error_code);
}
