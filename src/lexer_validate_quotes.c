/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:41:02 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/30 18:06:55 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*handle_quote(t_lexer *list, t_token *current, int quote_type)
{
	if (current->next != NULL)
	{
		current = current->next;
		// Do we need to handle adjacent quote_type "" or '' -> (null)?
		//	if (current->type == quote_type)
		//	{
		//		make_null_terminated_string()
		//	}
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
	list->state == STRING;
	return (current);
}

int	validate_quotes(t_lexer *token_list)
{
	t_token	*current;

	current = token_list->token_list;
	while (current->next != NULL && token_list->state != SYNTAX_ERROR)
	{
		if (current->type == SINGLE_QUOTE)
			current = handle_quote(token_list, current, SGL_QUOTE_STR);
		else if (current->type == DOUBLE_QUOTE)
			current = handle_quote(token_list, current, DBL_QUOTE_STR);
		else
			current = current->next;
	}
	if (token_list->state == SYNTAX_ERROR)
		return (FAILED);
	return (VALIDATED);
}
