/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:38:05 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/07 18:39:16 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief 
 * 
 * 
 * @param list 
 * @param token 
 * @param new_token 
 * @param input 
 */
t_return_value	label_new_token_as_quote(t_lexer *list, t_token *new_token,
		char *input)
{
	new_token->string_length = 1;
	if (input[0] == '\'')
	{
		new_token->type = SINGLE_QUOTE;
		if (tokenize_node(list, new_token, "\'") == CALLOC_FAIL)
			return (list->error_code = CALLOC_FAIL);
	}
	else if (input[0] == '\"')
	{
		new_token->type = DOUBLE_QUOTE;
		if (tokenize_node(list, new_token, "\"") == CALLOC_FAIL)
			return (list->error_code = CALLOC_FAIL);
	}
}

/**
 * @brief 
 * 
 * 
 * @param list 
 * @param token 
 * @param input 
 */
t_return_value	add_null_string_token_if_empty_quote(t_lexer *list,
													t_token *token,
													char *input)
{
	t_token	*new_token;

	if (input[0] == '\'')
		token->type = SGL_QUOTE_STR;
	else if (input[0] == '\"')
		token->type = DBL_QUOTE_STR;
	token->string_length = 0;
	if (tokenize_node(list, token, '\0') == CALLOC_FAIL)
		return (list->error_code = CALLOC_FAIL);
	new_token = list->head;
	while (new_token != NULL)
		new_token = new_token->next;
	if (make_new_node(list, &new_token) == CALLOC_FAIL)
		return (list->error_code = CALLOC_FAIL);
	if (label_new_token_as_quote(list, new_token, input) == CALLOC_FAIL)
		return (list->error_code = CALLOC_FAIL);
	return (SUCCESS);
}

/**
 * @brief 
 * 
 *
 * @param list 
 * @param token 
 * @param state 
 * @param type 
 */
static void	set_token_type_and_list_state(t_lexer *list, t_token *token,
		t_validation_state state, t_token_type type)
{
	token->type = type;
	list->state = state;
}

/**
 * @brief 
 * 
 * 
 * @param list 
 * @param token 
 * @param input 
 */
void	handle_quotes(t_lexer *list, t_token *token, t_token_type type,
		char *input)
{
	if (list->state == UNDEFINED && input[0] == '\'')
		set_token_type_and_list_state(list, token, SINGLE_QUOTE, \
				SGL_QUOTE_OPENED);
	else if (list->state == UNDEFINED && input[0] == '\"')
		set_token_type_and_list_state(list, token, DOUBLE_QUOTE, \
				DBL_QUOTE_OPENED);
	else if ((list->state == SGL_QUOTE_OPENED || \
				list->state == SGL_QUOTE_CAN_BE_CLOSED) && \
				input[0] != '\'')
		set_token_type_and_list_state(list, token, SGL_QUOTE_STR, \
				SGL_QUOTE_CAN_BE_CLOSED);
	else if ((list->state == DBL_QUOTE_OPENED || \
				list->state == DBL_QUOTE_CAN_BE_CLOSED) && \
				input[0] != '\"')
		set_token_type_and_list_state(list, token, DBL_QUOTE_STR, \
				DBL_QUOTE_CAN_BE_CLOSED);
	else if (list->state == SGL_QUOTE_CAN_BE_CLOSED && input[0] == '\'')
		set_token_type_and_list_state(list, token, SINGLE_QUOTE, UNDEFINED);
	else if (list->state == DBL_QUOTE_CAN_BE_CLOSED && input[0] == '\"')
		set_token_type_and_list_state(list, token, DOUBLE_QUOTE, UNDEFINED);
	else
		add_null_string_token_if_empty_quotes(list, token, input);
}
