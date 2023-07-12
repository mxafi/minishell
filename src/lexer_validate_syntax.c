/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validate_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:59 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/12 17:01:47 by lclerc           ###   ########.fr       */
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
 * @brief		Implement a function that seeks for a $ and string compare 
 * 				the consecutive chars until the next token. A match in the 
 * 				environment KEYS 
 * 
 *
 * @param list 
 */
void	expand_from_env(t_lexer *list)
{
	t_token	*current;
	char	*env_key;
	char	*env_value;

	current = list->head;
	env_key = NULL;
	while (current != NULL)
	{
		if (current->type == DBL_QUOTE_STR || current->type == STRING)
		{
			env_key = ft_strchr(current->content + 1, '$');
			if (env_key != NULL)
			{
				env_value = env_get_value_by_key(env_key + 1);
				if (env_value != NULL)
					current->content = ft_strdup(env_value);
				else
					current->content = ft_strdup("");
			}
		}
		current = current->next;
	}
}

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
	expand_from_env(token_list);
	concatenate_strings(token_list);
	remove_spaces(token_list);
	validate_pipe(token_list);
	validate_redirectors(token_list)
}
