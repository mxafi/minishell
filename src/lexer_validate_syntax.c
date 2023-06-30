/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/28 14:27:55y lclerc           ###   ########.fr       */
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
 * @brief 	Checks if first or last token is not a pipe
 * @details	If pipe is found,
		error message is printed and token state updated to SYNTAX_ERROR (258)
 * @param 	token_list	The token list carrying list properties
 * @param 	token		The first or last token of the list to be validated
 */
static void	token_is_not_pipe(t_lexer *token_list, t_token *token)
{
	if (token != NULL && token->type == PIPE)
	{
		ft_printf("shellfish> syntax error near unexpected token `|'\n");
		token_list->state = SYNTAX_ERROR;
	}
}

/**
 * @brief	Checks the type of current token and routes to appropriates validation function
 * 
 * @param token_list
 * @param token
 */
static void	check_current_token(t_lexer *token_list, t_token *token)
{
	if (is_token_type_redirector(token_list, token))
		validate_redirector(token_list, token);
	else if (token->type == PIPE)
		validate_pipe(token_list);
	else if (token->type == SPACE)
		token = delete_space_token(token_list, token);

}

/**
 * @brief	token by token validation process
 * @details	1st token can not be a pipe
 * 			last token cannot be a pipe (make sure of that) or a REDIR
 *			calls to validate redirectors, pipes and quotes
 *  
 * @param token_list 
 * @return int 
 */
int	validate_syntax(t_lexer *token_list)
{
	t_token	*token;

	token = token_list->token_list;
	token_list->state = STRING;
	if (validate_quotes(token_list) == VALIDATED)
	{
		token_is_not_pipe(token_list, token);
		while ((token->next != NULL) && (token_list->state != SYNTAX_ERROR))
			check_current_token(token_list, token);
		if (token_is_not_pipe(token_list, token))
			;
	}
	token = NULL;
	if (token_list->state == FAILED_VALIDATION)
		return (FAILED_VALIDATION);
	return (SUCCESS);
}
