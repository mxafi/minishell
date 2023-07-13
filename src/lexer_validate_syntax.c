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
 * @brief	Expands environment variables within double-quoted strings or 
 *			regular strings	the consecutive chars until the next token. A match in 
 * 			the environment KEYS 
 * @details	This function searches for the occurrence of environment variables indicated
 *			by a `$` symbol within double-quoted strings or regular strings. It 
 *			retrieves the corresponding values from the environment and updates the 
 *			token content accordingly. 
 *
 * @param list	The lexer list containing the tokens to process
 */
static void	expand_from_env(t_lexer *list)
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
				free(current->content);
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
	validate_quotes(token_list);
	expand_from_env(token_list);
	concatenate_adjacent_strings(token_list);
	remove_spaces(token_list);
	validate_pipe(token_list);
	validate_redirectors(token_list);
	return (token_list->error_code);
}
