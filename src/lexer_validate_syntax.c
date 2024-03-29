/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/24 18:47:47 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief	Labels tokens as CMD or ARG based on their position in the token 
 *	list.
 * 
 * @details	The first encountered STRING tokenS of the input and after each 
 * 			pipes are labeled as CMD, and all subsequent STRING tokens are 
 * 			labeled as ARG. The labeling is performed by modifying the type
 * 			field of the tokens.
 * @param token_list The list to process and label.
 */
static void	label_cmds_and_args(t_lexer *token_list)
{
	t_token	*current;
	t_token	*prev_token;

	current = token_list->head;
	prev_token = NULL;
	while (current != NULL)
	{
		if (current->type == STRING)
		{
			if (prev_token != NULL
				&& token_is_redirector(prev_token) == SUCCESS)
				current->type = ARG;
			else if (token_list->cmd_found == FOUND)
				current->type = ARG;
			else
			{
				current->type = CMD;
				token_list->cmd_found = FOUND;
			}
		}
		else if (current->type == PIPE)
			token_list->cmd_found = NOT_YET;
		prev_token = current;
		current = current->next;
	}
}

/**
 * @brief Removes space tokens from the token list.
 *
 * This function iterates through the token list and removes tokens of type
 * `MY_SPACE`. It updates the list pointers and frees the memory associated
 * with the removed tokens.
 *
 * @param list The list of tokens to be processed.
 */
static void	remove_spaces(t_lexer *list)
{
	t_token	*current;
	t_token	*temp;

	current = list->head;
	while (current != NULL && current->next != NULL)
	{
		if (current->type == MY_SPACE)
		{
			temp = current->next;
			delete_token(list, current);
			current = temp;
		}
		else
			current = current->next;
	}
}

/**
 * @brief	Validates the syntax of the token list
 * @details	This function performs a series of syntax validations on the token
 * 			list. It checks for the correctness of quotes, expands environment 
 * 			variables, concatenates adjacent strings, removes spaces, validates 
 * 			pipe usage, validates redirectors, and labels CMD and ARG tokens.	
 *
 * @param token_list	Token list being validated
 * @return				SUCCESS or EXIT_SYNTAX_ERROR 
 */
t_return_value	validate_syntax(t_lexer *token_list)
{
	if (validate_quotes(token_list) == EXIT_SYNTAX_ERROR)
		return (token_list->error_code);
	if (expand_from_env(token_list) != SUCCESS)
		return (token_list->error_code);
	if (concatenate_adjacent_strings(token_list) == MALLOC_FAIL)
		return (token_list->error_code);
	remove_spaces(token_list);
	if (validate_pipes(token_list) == EXIT_SYNTAX_ERROR)
		return (token_list->error_code);
	if (token_list->error_code != SUCCESS)
		return (token_list->error_code);
	if (validate_redirectors(token_list) == EXIT_SYNTAX_ERROR)
		return (token_list->error_code);
	if (process_heredoc(token_list) != SUCCESS)
		return (token_list->error_code);
	label_cmds_and_args(token_list);
	return (token_list->error_code);
}
