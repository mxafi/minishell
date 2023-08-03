/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/13 11:29:09by lclerc           ###   ########.fr       */
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
 * @brief	Labels tokens as CMD or ARG based on their position in the token list.
 * 
 * @details	The first encountered STRING tokenS of the input and after each 
 * 			pipes are labeled as CMD, and all subsequent STRING tokens are 
 * 			labeled as ARG. The labeling is performed by modifying the type
 * 			field of the tokens.
 * @param token_list The list to process and label.
 */
void	label_CMDS_and_ARGS(t_lexer *token_list)
{
	t_token	*current;

	current = token_list->head;
	while (current != NULL)
	{
		if (current->type == STRING)
		{
			if (token_list->CMD_found == FOUND)
				current->type = ARG;
			else
			{
				current->type = CMD;
				token_list->CMD_found = FOUND;
			}
		}
		else if (current->type == PIPE)
			token_list->CMD_found = NOT_YET;
		current = current->next;
	}
}

/**
 * @brief		Remove space tokens from the token list.
 * 
 * @param list	The list of tokens to be processed.
 */
static void	remove_spaces(t_lexer *list)
{
	t_token	*current;
	t_token	*next_token;

	current = list->head;
	while (current != NULL && current->next != NULL)
	{
		next_token = current->next;
		if (current->type == SPACE)
			delete_token(list, current);
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
	printf("validate_syntax()\n");
	if (validate_quotes(token_list) == EXIT_SYNTAX_ERROR)
		return (token_list->error_code);
	printf("validate_syntax()quote validated\n");
	print_list(token_list);
	expand_from_env(token_list);
	printf("validate_syntax()expanded\n");
	print_list(token_list);
	concatenate_adjacent_strings(token_list);
	printf("validate_syntax()concatenated\n");
	print_list(token_list);
	remove_spaces(token_list);
	printf("validate_syntax()removed spaces\n");
	print_list(token_list);
	if (validate_pipes(token_list) == EXIT_SYNTAX_ERROR)
		return (token_list->error_code);
	printf("validate_syntax()validated pipes\n");
	print_list(token_list);
	if (token_list->error_code != SUCCESS)
		return (token_list->error_code);
	if (validate_redirectors(token_list) == EXIT_SYNTAX_ERROR)
		return (token_list->error_code);
	printf("validate_syntax()redirector validated\n");
	print_list(token_list);
	label_CMDS_and_ARGS(token_list);
	printf("validate_syntax()token CMD ARGS labelled\n");
	print_list(token_list);
	return (token_list->error_code);
}
