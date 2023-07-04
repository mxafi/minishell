/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:41:02 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/04 18:28:41 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief	Checks if the opening quote has a matching closing quote. 
 * @details	Seeks for matching closing quote, every token type iterated through 
 * 			prior quote match is relabeled as SGL or DBL_QUOTE_STR.
 * 			- If a matching quote is found, the token list's state is updated to
 *			IS_STR.
 * 			- If no matching quote is found, the token list's state is updated
 * 			to SYNTAX_ERROR and will terminate further validation of the input
 *
 * @param list		Placeholder for list data
 * @param current	Token of type quote in search of it's closing pair
 * @param quote_type Single (SGL_QUOTE_STR) or double quote (DBL_QUOTE_STR)
 * @return	t_token* Returns the token closing the quote or NULL pointer 
 */
static t_token	*handle_quote(t_lexer *list, t_token *current,
		t_token_type quote_type)
{
	if (current->next != NULL)
	{
		current = current->next;
		if (current->type == quote_type)
		{
			current = empty_paired_quote_add_null_string(list, current);
			current->type == IS_STR;
			// edit the type change in empty_paired_quote...
			if (current->next != NULL)
				current = current->next;
			return (current);
		}
		while (current != NULL && current->type != quote_type)
		{
			current->type = quote_type;
			current = current->next;
		}
		if (current == NULL)
		{
			list->state == SYNTAX_ERROR;
			return (NULL);
		}
	}
	list->state == IS_STR;
	if (current->next != NULL)
		current = current->next;
	return (current);
}

/**
 * @brief	Single and double quotes pair checker.
 * @details Look for an open quote token and handles the quote accordingly.
 * 			Rename token type between matching quotes to single or double quote
 * 			string (SGL / DBL_QUOTE_STR).
 *
 * @param 	token_list List of token being checked
 * @return	t_return_value Failure or Success 
 */
t_return_value	validate_quotes(t_lexer *token_list)
{
	t_token	*current;

	current = token_list->token_list;
	while (current != NULL && token_list->state != SYNTAX_ERROR)
	{
		if (current->type == SINGLE_QUOTE)
			current = handle_quote(token_list, current, SGL_QUOTE_STR);
		else if (current->type == DOUBLE_QUOTE)
			current = handle_quote(token_list, current, DBL_QUOTE_STR);
		else
			current = current->next;
	}
	if (token_list->state == SYNTAX_ERROR)
		return (FAILURE);
	return (SUCCESS);
}
