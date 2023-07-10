/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/10 18:24:25 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Syntax check as I have gathered it.. hopefully, nothing is missing:
1/ Check first character -> cannot be pipe
2/ Redirectors < < , <>,
	> > and pipes | | (beware of non combinable delimiters else than << and >>) have to be followed with at least one non-delimiter chars on each side (yeah,
		spaces can be in between)
3/ check quotes are closing 
4/ Last char cannot be redirector or pipe
Any syntax error exits back to prompt with "return FAILED_VALIDATION = 258"
*/

/**
 * @brief	Checks syntax validity of pipes within the input
 * @details	Checks for the following situations:
 * 			- CMD1 || CMD2 -> No syntax error
 * 			- CMD1 ||| CMD2 -> Syntax error near unexpected `|'
 * 			- CMD1 |||| CMD2 -> Syntax error near unexpected `||'
 * 			- CMD1 <| CMD2 -> Syntax error near unexpected `|'
 * 			- CMD1 >| CMD2 -> No Syntax error
 * 			- CMD1 >>| CMD2 -> Syntax error near unexpected `|'
 * 			- CMD1 >>>| CMD2 -> Syntax error near unexpected '>|'
 * 			For simplicity, only "Syntax error" is printed
 * @param token_list 
 * @param previous 
 * @param current 
 * @param next 
 * @return 
 */
static t_return_value	check_if_pipe_is_surrounded_by_strings(
	t_lexer *token_list, t_token *previous, t_token *current, t_token *next)
{
	if (current->type == PIPE)
	{
		if (previous->type != STRING && previous->type != SGL_QUOTE_STR && \
			previous->type != DBL_QUOTE_STR && \
			previous->type != QUOTE_NEED_NULL_STR && next->type != STRING && \
			next->type != SGL_QUOTE_STR && next->type != DBL_QUOTE_STR && \
			next->type != QUOTE_NEED_NULL_STR && next->type != PIPE)
			;
	}
}

/**
 * @brief 
 * 
 * 
 * @param token_list 
 * @return 
 */
static t_return_value	validate_pipe(t_lexer *token_list)
{
	t_token	*previous;
	t_token	*current;
	t_token	*next;

	previous = token_list->head;
	current = token_list->head;
	if (current->next != NULL)
		next = token_list->head;
	if (current->type == PIPE)
	{
		printf("shellfish> syntax error near unexpected token `|'\n");
		token_list->state = SYNTAX_ERROR;
	}
	while (current->next != NULL)
	{
		previous->next = current;
		next = current->next;
		if (check_if_pipe_is_surrounded_by_strings(token_list, previous,
				current, next) == FAILURE)
			return (FAILURE);
		current = current->next;
	}
	if (current->type == PIPE)
	{
		printf("shellfish> syntax error near unexpected token `newline'\n");
		token_list->state = SYNTAX_ERROR;
	}
}

/**
 * @brief	token by token validation process
 * @details	1st token can not be a pipe
 * 			last token cannot be a pipe (make sure of that) or a REDIR
 *			calls to validate redirectors, pipes and quotes
 *  
 * @param	token_list 
 * @return	t_return_value		Return value
 */
t_return_value	validate_syntax(t_lexer *token_list)
{
	t_token	*token;

	token = token_list->head;
	token_list->state = IS_STR;
	validate_quotes(token_list);
	validate_pipe(token_list);
	if
	{
		token_is_not_pipe(token_list, token);
		while ((token->next != NULL) && (token_list->state != SYNTAX_ERROR))
			check_current_token(token_list, token);
		if (token_is_not_pipe(token_list, token))
			;
	}
	token = NULL;
	if (token_list->state == SYNTAX_ERROR)
		return (EXIT_SYNTAX_ERROR);
	return (SUCCESS);
}
