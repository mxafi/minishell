/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:43:44 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/13 15:46:52by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief	Checks syntax validity of pipes within the input
 * @details	Pipes have to have valid command on both sides, but from a syntax
 * 			validation perspective only those triggering a syntax error in bash
 * 			are considered as follows:
 * 			- CMD1 || CMD2 -> No syntax error in bash -> here yes
 * 			- CMD1 ||| CMD2 -> Syntax error near unexpected `|'
 * 			- CMD1 |||| CMD2 -> Syntax error near unexpected `||'
 * 			- CMD1 <| CMD2 -> Syntax error near unexpected `|'
 * 			- CMD1 >| CMD2 -> No Syntax error
 * 			- CMD1 >>| CMD2 -> Syntax error near unexpected `|'
 * 			- CMD1 >>>| CMD2 -> Syntax error near unexpected '>|' 
 * 			Also, the first and last token cannot be pipes either.
 * 
 * @param token_list		List of token 
 * @return t_return_value	SUCCESS or EXIT_SYNTAX_ERROR
 */
t_return_value	validate_pipes(t_lexer *token_list)
{
	t_token	*previous;
	t_token	*current;

	previous = NULL;
	current = token_list->head;
	while (current != NULL && token_list->error_code != EXIT_SYNTAX_ERROR)
	{
		if ((current->type == PIPE && previous == NULL) || (current->type == PIPE
				&& (previous->type == PIPE || previous->type == INFILE
					|| previous->type == APPEND_TO)))
		{
			printf("shellfish> syntax error near unexpected token `|'\n");
			token_list->error_code = EXIT_SYNTAX_ERROR;
		}
		else if (current->type == PIPE && current->next == NULL)
		{
			printf("shellfish> syntax error near unexpected token `newline'\n");
			token_list->error_code = EXIT_SYNTAX_ERROR;
		}
		previous = current;
		current = current->next;
	}
	if (token_list->state == SYNTAX_ERROR)
		return (token_list->error_code == EXIT_SYNTAX_ERROR);
	return (token_list->error_code == SUCCESS);
}
