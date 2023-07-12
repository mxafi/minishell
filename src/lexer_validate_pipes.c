/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:43:44 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/12 11:45:20 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"
/**
 * @brief	Checks syntax validity of pipes within the input
 * @details	Checks for the following situations:
 * 			- CMD1 || CMD2 -> No syntax error in bash -> here yes
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
			previous->type != DBL_QUOTE_STR && next->type != STRING && \
			next->type != SGL_QUOTE_STR && next->type != DBL_QUOTE_STR)
		

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