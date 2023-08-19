/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_redirectors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:58:31 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/18 15:37:29 by lclerc           ###   ########.fr       */
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
 * @brief	Checks whether the current token is of redirector type
 *
 * @param 	token	token being checked 
 * @return			SUCCESS or FAILURE according to validity 
 */
t_return_value	token_is_redirector(t_token *token)
{
	if (token->type == OUTFILE || token->type == INFILE ||
		token->type == HEREDOC || token->type == APPEND_TO)
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Prints syntax error message to standard output
 * 
 * @param unexpected_token	The unexpected token causing the syntax error
 */
static void	print_syntax_error(char *unexpected_token)
{
	if (!unexpected_token)
		printf("☠️  shellfishy ☠️  > syntax error near unexpected token `newline'\n");
	else
		printf("☠️  shellfishy ☠️  > syntax error near unexpected token `%s'\n",
				unexpected_token);
}

/**
 * @brief 	Validates the syntax of redirectors within the input
 * @details	Following conditions lead to syntax errors:
 * 			- Redirector must be followed by non-empty string
 * 			- The last token of the list cannot be a redirector
 * 			A syntax error message is printed if necessary and an error
 * 			code is returned.
 * 
 * @param token_list		Token list to validate
 * @return t_return_value 	SUCCESS or EXIT_SYNTAX_ERROR
 */
t_return_value	validate_redirectors(t_lexer *list)
{
	t_token	*current;
	t_token	*next_token;

	current = list->head;
	while (current->next != NULL)
	{
		if (token_is_redirector(current) == SUCCESS)
		{
			next_token = current->next;
			if (current->next != NULL && next_token->type != STRING)
			{
				print_syntax_error(next_token->content);
				list->error_code = EXIT_SYNTAX_ERROR;
				return (EXIT_SYNTAX_ERROR);
			}
		}
		current = current->next;
	}
	if (current->next == NULL && (token_is_redirector(current) == SUCCESS))
	{
		print_syntax_error(NULL);
		list->error_code = EXIT_SYNTAX_ERROR;
		return (EXIT_SYNTAX_ERROR);
	}
	return (SUCCESS);
}
