/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:43:44 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/24 10:28:56 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Sets and prints syntax error message.
 * 
 * @param token_list The lexer token list.
 * @param pipe_error Indicates if the error is related to a pipe.
 * @param new_line_error Indicates if the error is related to a newline.
 */
static void	set_and_print_syntax_error_message(t_lexer *token_list,
												t_bool pipe_error,
												t_bool new_line_error)
{
	if (pipe_error == TRUE)
		printf("☠️  shellfishy ☠️ > syntax error near unexpected token `|'\n");
	else if (new_line_error == TRUE)
		printf("☠️  shellfishy ☠️ > syntax error near unexpected token " \
		"`newline'\n");
	token_list->error_code = EXIT_SYNTAX_ERROR;
}

/**
 * @brief Checks syntax validity of pipes within the input.
 * 
 * @param token_list The lexer token list.
 * @param current The current token being analyzed.
 * @param previous The previous token.
 */
static void	check_pipes(t_lexer *token_list, t_token *current,
		t_token *previous)
{
	t_bool	pipe_error;
	t_bool	line_error;

	pipe_error = FALSE;
	line_error = FALSE;
	if ((current->type == PIPE && previous == NULL) || (current->type == PIPE
			&& (previous->type == PIPE || previous->type == INFILE
				|| previous->type == APPEND_TO)))
		pipe_error = TRUE;
	else if (current->type == PIPE && current->next == NULL)
		line_error = TRUE;
	if (pipe_error == TRUE || line_error == TRUE)
		set_and_print_syntax_error_message(token_list, pipe_error, line_error);
}

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
 * 			- First and last token cannot be pipes either.
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
		check_pipes(token_list, current, previous);
		previous = current;
		current = current->next;
	}
	if (token_list->state == SYNTAX_ERROR)
		token_list->error_code = EXIT_SYNTAX_ERROR;
	return (token_list->error_code);
}
