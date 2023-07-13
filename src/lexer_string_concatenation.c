/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_concatenation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:44:48 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/13 13:49:38 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

/**
 * @brief	Concatenate current and following token
 * @details	Concatenation results in the deletion of the next token.
 * 
 * @param list			The list of token
 * @param current 		Current token which will hold the new string
 * @param next_token 	Token being deleted after concatenation
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
		ft_strlcpy(new_string, current->content, length);
		ft_strlcat(new_string, next_token->content, length);
		free(current->content);
		current->content = new_string;
		delete_token(list, next_token);
	}
	else
	{
		list->error_code = CALLOC_FAIL;
		return ;
	}
}

/**
 * @brief		Format all string types to STRING
 * @details		In order to save space in the subsequent concatenation of string
 * 				and since all action on specific quotes as SGL or DBL_QUOTE_STR
 * 				have been handled, those latest are now irrelevant.
 *
 * @param list	The list of token
 */
static void	simplify_string_syntax(t_lexer *list)
{
	t_token	*current;

	current = list->head;
	while (current != NULL)
	{
		if (current->type == SGL_QUOTE_STR || current->type == DBL_QUOTE_STR)
			current->type = STRING;
		current = current->next;
	}
}

/**
 * @brief	Expands environment variables within double-quoted strings or 
 *
 * @brief 		Search for concatenable strings
 * @details		Search for consecutive strings for concatenation
 * 
 * @param list	List of token.
 */
void	concatenate_adjacent_strings(t_lexer *list)
{
	t_token	*current;
	t_token	*next_token;

	current = list->head;
	assert(current != NULL);       // del both asserts
	assert(current->next != NULL); // Del both asserts
	simplify_string_syntax(list);
	while (current != NULL && current->next != NULL)
	{
		next_token = current->next;
		if (current->type == STRING)
		{
			while (next_token != NULL && next_token->type == STRING)
			{
				concatenate_strings(list, current, next_token);
				if (list->error_code == CALLOC_FAIL)
					return ;
			}
		}
		current = current->next;
	}
}
