/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:38:05 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/07 13:28:41 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	label_single_quote(t_lexer *list, t_token token)
{
	if (list->state != SGL_QUOTE_OPENED)
		list->state = SGL_QUOTE_OPENED;
	else if (current->type == SINGLE_QUOTE)
	{
		string_to_token(list, empty_string, empty_string);
		list->state == SGL_QUOTE_STR;
	}
}

void	label_double_quote(t_lexer *list, t_token token)
{
	if (list->state != NEED_DBL_QUOTE_STR)
		list->state = NEED_DBL_QUOTE_STR;
	else if (current->type == DOUBLE_QUOTE)
	{
		string_to_token(list, empty_string, empty_string);
		list->state == DBL_QUOTE_STR;
	}
}

/**
 * @brief	Checks
 * 
 * @param list 
 */
void	add_null_string_token_if_empty_quote(t_lexer *list, t_token *token,
		char *input)
{
	t_token	*new_token;
	char	*empty_string;

	empty_string = "";
	new_token = list->head;
	while (new_token != NULL)
		new_token = new_token->next;
	if (make_new_node(list, new_token) == CALLOC_FAIL)
		return (list->error_code = CALLOC_FAIL);
	if (input[0] == '\'')
	{
		token->type = SGL_QUOTE_STR;
		token->token = empty_string;
		if (tokenize_node(list, new_token, input, 1) == FAILURE)
			return (token_list->error_code = CALLOC_FAIL);
		new_token->type = SINGLE_QUOTE;
		list->state = UNDEFINED;
	}
}

void	handle_quotes(t_lexer *list, t_token *token, char *input)
{
	if (list_state == UNDEFINED && input[0] == '\'')
	{
		token->type = SINGLE_QUOTE;
		list->state = SGL_QUOTE_OPENED;
	}
	else if (list_state == UNDEFINED && input[0] == '\"')
	{
		token->type = DOUBLE_QUOTE;
		list->state = DBL_QUOTE_OPENED;
	}
	else if ((list->state == SGL_QUOTE_OPENED ||
				list->state == SGL_QUOTE_CAN_BE_CLOSED) &&
				input[0] != '\'')
	{
		token->type = SGL_QUOTE_STR;
		list->state = SGL_QUOTE_CAN_BE_CLOSED;
	}
	else if ((list->state == DBL_QUOTE_OPENED ||
				list->state == DBL_QUOTE_CAN_BE_CLOSED) &&
				input[0] != '\"')
	{
		token->type = DBL_QUOTE_STR;
		list->state = DBL_QUOTE_CAN_BE_CLOSED;
	}
	else if (list->state == SGL_QUOTE_CAN_BE_CLOSED && input[0] == '\'')
	{
		token->type == SINGLE_QUOTE;
		list->state == UNDEFINED;
	}
	else if (list->state == DBL_QUOTE_CAN_BE_CLOSED && input[0] == '\"')
	{
		token->type == DOUBLE_QUOTE;
		list->state == UNDEFINED;
	}
	else
		add_null_string_token_to_empty_quotes(list, token, input);
}
