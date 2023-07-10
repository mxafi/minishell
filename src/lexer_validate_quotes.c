/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:41:02 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/10 14:17:25 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



/**
 * @brief	Single and double quotes pair checker.
 * @details In the tokenization process, in order to label tokens as quoted
 * 			strings the state of opened quotes labelled as single SGL or double
 * 			DBL *_QUOTE_OPENED or *_QUOTE_CAN_BE_CLOSED) is kept in the
 *			token_list->state placeholder. If this state remains, the syntax
 *			validation process is printing a corresponding syntax error, if 
 *			quotes are present, but have matching closing quote, token_list->state
 *			is UNDEFINED. This is not a bash behaviour but a requisite from 
 *			the subject.
 *
 * @param 	token_list List of token being checked
 * @return	t_return_value Failure or Success 
 */
t_return_value	validate_quotes(t_lexer *token_list)
{
	t_token	*last;

	last = token_list->head;
	while (last != NULL)
		current = current->next;
	if (token_list->state == SGL_QUOTE_CAN_BE_CLOSED || \
		token_list->state == SGL_QUOTE_OPENED || \
		{
		printf("Shellfish> syntax error expecting closing single quotes `\''\n");
		token_list-
		return (FAILURE);
		}
	else if (token_list->state == DBL_QUOTE_CAN_BE_CLOSED || \
		token_list->state == DBL_QUOTE_OPENED)
		{
		printf("Shellfish> syntax error expecting closing double quotes `\"'\n");
		return (FAILURE);
		}
	return (SUCCESS);
}
