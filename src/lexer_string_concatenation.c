/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_concatenation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:44:48 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/25 13:03:53 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

/**
 * @brief Concatenates the content of current and following tokens.
 * @details This function concatenates the content of the current token and the
 * following token, resulting in the deletion of the next token. The content of
 * the current token is updated with the concatenated string
 * 
 * @param list       The list of tokens.
 * @param current    The current token that will hold the new string.
 * @param next_token The token to be deleted after concatenation.
 */
static void	concatenate_strings(t_lexer *list, t_token *current,
		t_token *next_token)
{
	size_t	length;
	char	*new_string;

	length = ft_strlen(current->content) + ft_strlen(next_token->content);
	new_string = (char *)ft_calloc(length + 1, sizeof(char));
	if (new_string != NULL)
	{
		ft_strlcpy(new_string, current->content, length + 1);
		ft_strlcat(new_string, next_token->content, length + 1);
		free(current->content);
		current->content = new_string;
		delete_token(list, next_token);
	}
	else
	{
		list->error_code = MALLOC_FAIL;
		return ;
	}
}

/**
 * @brief Simplifies the syntax of string tokens.
 * @details This function traverses the token list and converts single-quoted 
 * and double-quoted string tokens into regular string tokens. This is done
 * to simplify the handling of string concatenation.
 * 
 * @param list List of tokens to process.
 */
static void	simplify_string_syntax(t_lexer *list)
{
	t_token	*current;

	current = list->head;
	while (current != NULL)
	{
		if (current->type == SGL_QUOTE_STR || current->type == DBL_QUOTE_STR
			|| current->type == QUOTE_NEED_NULL_STR)
			current->type = STRING;
		current = current->next;
	}
}

/**
 * @brief Concatenates adjacent string tokens into a single token.
 *
 * @details This function searches for consecutive string tokens and 
 * concatenates them into a single token. The resulting token will have the 
 * combined content of all consecutive string tokens.
 * 
 * @param list List of tokens to process.
 */
t_return_value	concatenate_adjacent_strings(t_lexer *list)
{
	t_token	*current;
	t_token	*next_token;

	current = list->head;
	simplify_string_syntax(list);
	while (current != NULL && current->next != NULL)
	{
		next_token = current->next;
		if (current->type == STRING)
		{
			while (next_token != NULL && next_token->type == STRING)
			{
				concatenate_strings(list, current, next_token);
				if (list->error_code == MALLOC_FAIL)
					return (list->error_code);
				next_token = current->next;
			}
		}
		current = current->next;
	}
	return (list->error_code);
}
