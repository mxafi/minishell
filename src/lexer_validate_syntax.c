/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/12 11:45:14 by lclerc           ###   ########.fr       */
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
	concatenate_strings(token_list);
	remove_spaces(token_list);
	validate_pipe(token_list);
	validate_redirectors(token_list)
	
}
