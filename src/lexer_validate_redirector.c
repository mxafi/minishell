/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_redirector.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:58:31 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/10 16:44:54 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

/**
 * @brief	Checks whether the current token is of redirector type
 * @details	Returns the redirector types if valid, else keeps the current state
 * @param 	token_list	contains the current state of the syntax validation process
 * @param 	token 		token being checked 
 * @return	returns SUCCESS or FAILURE according to validity 
 */
t_return_value	is_token_type_redirector(t_lexer *token_list, t_token *token)
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
void	token_is_redirector(t_lexer *token_list, t_token *token)
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
void	validate_redirector(t_lexer *token_list, t_token *token)
{
	if (token_is_redirector(token_list, token) && \
			(token_list->state != SYNTAX_ERROR))
	{
		token_list->state = token->type;
		if (token->next != NULL)
		{
			token = token->next;
			if (token->type == SPACE)
				delete_space_token(&token_list, token->token_count);
			if (token->type == STRING)
				token_list->state = IS_STR;
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