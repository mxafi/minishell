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
#include <complex.h>

/** Syntax check as I have gathered it.. hopefully, nothing is missing:
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
 * @details	If pipe is found, error message is printed and token state updated to SYNTAX_ERROR (258)
 * @param 	token_list	The token list carrying list properties
 * @param 	token		The frist or last token of the list to be validated
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
 * @brief	Checks whether the current token is of redirector type
 * @details	Returns the redirector types if valid, else keeps the current state
 * @param 	token_list	contains the current state of the syntax validation process
 * @param 	token 		token being checked 
 * @return	returns SUCCESS or FAILURE according to validity 
 */
static int	is_token_type_redirector(t_lexer *token_list, t_token *token)
{
	if (token->type == OUTFILE || token->type == INFILE ||
		token->type == HEREDOC || token->type == APPEND_TO)
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Prints syntax error message to standard output
 * 
 * @param error_type	when possible error type is used to print the unexpecterd char
 */
static void	print_syntax_error(int	error_type)
{
	if (token->type == APPEND_TO)
		printf("shellfish> syntax error near unexpected token `>>'\n");
	else if (token->type == HEREDOC)
		printf("shellfish> syntax error near unexpected token `<<'\n");
	else
		printf("shellfish> syntax error near unexpected token `%c'\n", error_type);
}

/**
 * @brief 	Checks whether the current token is a valid redirector
 * @details	Syntax is invalid if validation process is already in IS_REDIR
 *			mode and current token is also a REDIR type.
 *			Valid syntax updates the token_list->state:
 *				to OUTFILE, INFILE, APPEND, HEREDOC if current token is of REDIR type
 *				keeps the current state if current token is not of REDIR type
 * @param 	token_list	contains the current state of validation process
 * @param 	token		token being checked
 */
static void	token_is_redirector(t_lexer *token_list, t_token *token)
{
	if (token_list->state != IS_REDIR)
		if (is_token_type_redirector(token_list, token) == SUCCESS)
			token_list->state = IS_REDIR;
	else
	{
		if (is_token_type_redirector(token_list, token) == SUCCESS)
		 {
			//Should there be state and errorcode..
			token_list->state = SYNTAX_ERROR;
			token_list->error_code = SYNTAX_ERROR;
			print_syntax_error(t_token->type);
		 }
	}
}



/**
 * @brief 	checks
 * 
 * @param token_list 
 * @param token 
 */
static void	redirectors_are_valid(t_lexer *token_list, t_token *token)
{
	if (token_is_redirector(token_list, token) && token->state != SYNTAX_ERROR)
	{
		token_list->state = token->type;
		if (token->next != NULL)
		{
			token = token->next;
			if (token->type == SPACE)
				delete_space_token(&token_list, token->token_count);
			if (token->type == STRING)
				token_list->state = STRING;
			else
			{
				ft_printf("shellfish> syntax error near unexpected token%c\n",
					token->type);
				token_list->state = SYNTAX_ERROR;
			}
		}
		else
		{
			ft_printf("shellfish> syntax error near unexpected token\
				`newline'\n");
		}
	}
}

/**
 * @brief	token by token validation process
 * @details	1st token can not be a pipe
 * 			last token cannot be a pipe (make sure of that) or a REDIR
 * 
 *  
 * @param token_list 
 * @return int 
 */
int	validate_syntax(t_lexer *token_list)
{
	t_token	*token;

	// @id:BeardedBear.beardedtheme
	token = token_list->token_list;
	token_list->state = STRING;
	token_is_not_pipe(token_list, token);
	while (token->next != NULL)
	{
		redirectors_are_valid(token_list, token);
		pipes_are_valid(token_list);
		quotes_are_valid(token_list);
	}
	if (token_is_not_pipe(token_list, token));
	if (token_list->state == FAILED_VALIDATION)
		return (FAILED_VALIDATION);
	return (SUCCESS);
}
