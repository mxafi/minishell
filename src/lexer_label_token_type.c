/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_label_token_type.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:38:05 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/11 13:16:00 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


/**
 * @brief 
 * 
 * 
 * @param list 
 * @param token 
 * @param input 
 */
static void	add_null_string_token_if_empty_quote(void)
{
	printf("THis was never meant to be read, what are you doing here\n");
//	t_token	*new_token;
//
//	if (input[0] == '\'')
//		token->type = SGL_QUOTE_STR;
//	else if (input[0] == '\"')
//		token->type = DBL_QUOTE_STR;
//	token->string_length = 0;
//	if (tokenize_node(list, token, '\0') == CALLOC_FAIL)
//		return (list->error_code = CALLOC_FAIL);
//	new_token = list->head;
//	while (new_token != NULL)
//		new_token = new_token->next;
//	if (make_new_node(list, &new_token) == CALLOC_FAIL)
//		return (list->error_code = CALLOC_FAIL);
//	if (label_new_token_as_quote(list, new_token, input) == CALLOC_FAIL)
//		return (list->error_code = CALLOC_FAIL);
//	return (SUCCESS);
}
//
/**
 * @brief			Labels token types and token list's state 
 * @details			If empty quotes occur, a QUOTE_NEED_NULL_STR will mark
 * 					the token type that will have it's content written
 * 					with an empty string.
 * 
 * @param list 		Head of token list and information placeholder
 * @param token		Current token 
 * @param state		Current state of the token list (UNDEFINED, QUOTE_OPENED_ QUOTE_CAN_BE_CLOSED) 
 * @param type		Type of token as obtained from ft_strpbrk as QUOTE_NEED_NULL_STR 
 */
static void	set_token_type_and_list_state(t_lexer *list, t_token *token,
		t_token_type type, t_validation_state state)
{
	token->type = type;
	list->state = state;
	if (token->type == QUOTE_NEED_NULL_STR)
		token->token == "";
}

/**
 * @brief		Labels token types and the current state of the token list  
 * @details		Helper function labelling token types, and handles quotes
 *				If a quote (single or double quotes) the state of the list
 *				is changed to (..)QUOTE_OPENED status. 
 *				Any token type being handled while the token list is in opened
 *				quote mode will be labelled as a SGL or DBL_QUOTE_STR.
 *				If the list does not end with an UNDEFINED state, syntax validation
 * 				will rejected the input. See lexer_quote_validation.c
 * 
 * @param list	Head and placeholder for information of the token list 
 * @param token	Current token 
 * @param input Current input string being tokenized 
 */
static void	handle_quotes(t_lexer *list, t_token *token, t_token_type type,
		char *input)
{
	if (list->state == UNDEFINED && input[0] == '\'')
		set_token_type_and_list_state(list, token, SINGLE_QUOTE, \
				SGL_QUOTE_OPENED);
	else if (list->state == UNDEFINED && input[0] == '\"')
		set_token_type_and_list_state(list, token, DOUBLE_QUOTE, \
				DBL_QUOTE_OPENED);
	else if (list->state == SGL_QUOTE_OPENED && input[0] != '\'')
		set_token_type_and_list_state(list, token, SGL_QUOTE_STR, \
				SGL_QUOTE_CAN_BE_CLOSED);
	else if (list->state == DBL_QUOTE_OPENED && input[0] != '\"')
		set_token_type_and_list_state(list, token, DBL_QUOTE_STR, \
				DBL_QUOTE_CAN_BE_CLOSED);
	else if (list->state == SGL_QUOTE_CAN_BE_CLOSED && input[0] == '\'')
		set_token_type_and_list_state(list, token, SINGLE_QUOTE, UNDEFINED);
	else if (list->state == DBL_QUOTE_CAN_BE_CLOSED && input[0] == '\"')
		set_token_type_and_list_state(list, token, DOUBLE_QUOTE, UNDEFINED);
	else if (list->state == SGL_QUOTE_OPENED && input[0] == '\'')
		set_token_type_and_list_state(list, token, QUOTE_NEED_NULL_STR, \
				UNDEFINED);
	else if (list->state == DBL_QUOTE_OPENED && input[0] == '\"')
		set_token_type_and_list_state(list, token, QUOTE_NEED_NULL_STR, \
				UNDEFINED);
	else
		add_null_string_token_if_empty_quotes();
}

/**
 * @brief	Labels the token types and the current state of the token list 
 * @details When initialized the linked list's state is undefined. During the
 * 			tokenization process, only quotes change this state to monitor
 * 			if the following token is to be labelled as found by ft_strpbrk()
 * 			or if it is a quote type of string SGL/DBL_QUOTE_STR.
 *
 * @param list			Head of the token list and placeholder for list information
 * @param token 		The current token being treated
 * @param token_type	The type of token 
 * @param input			The input string currently being handled 
 */
t_return_value	label_token_type(t_lexer *list, t_token *token, \
				t_token_type token_type, char *input)
{
	if (list->state == UNDEFINED)
	{
		if (token_type != UNDEFINED_TOKEN)
			token->type = token_type;
		else
		{
			if (input[0] == '\'' || input[0] == '\"')
				handle_quotes(list, token, token_type, input);
			else if (input[0] == '>')
				token->type = OUTFILE;
			else if (input[0] == '<')
				token->type = INFILE;
			else if (input[0] == '|')
				token->type = PIPE;
			else if (input[0] == ' ')
				token->type = SPACE;
		}
	}
	else if (list->state == SGL_QUOTE_OPENED || list->state == DBL_QUOTE_OPENED \
		|| list->state == SGL_QUOTE_CAN_BE_CLOSED || \
		list->state == DBL_QUOTE_CAN_BE_CLOSED)
		handle_quotes(list, token, token_type, input);
}
