/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:59:04 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/11 13:45:09lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Deletes token from the token list.
 * 
 * @param list	The list containing the token to be deleted
 * @param token	The token to be deleted
 */
void	delete_token(t_lexer *list, t_token *token)
{
	t_token	*previous;
	t_token	*current;

	previous = NULL;
	current = list->head;
	while (current != NULL && current != token)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (previous == NULL)
		list->head = token->next;
	else
		previous->next = token->next;
	free(token->content);
	free(token);
}

/**
 * @brief 	Memory allocate a new node and initializes it to zero with calloc
 * 
 * @param token_list 	used as error code placeholder
 * @param new_token		new node being tokenized
 * @return t_return_value	SUCCESS or CALLOC FAIL 
 */
t_return_value	make_new_node(t_lexer *token_list, t_token **new_token)
{
	*new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (*new_token == NULL)
	{
		token_list->error_code = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief	Frees the memory allocation for a token list
 * 
 * @param delete_me	The list to be freed.
 * @return int		The error code associated with the token list.
 */
t_return_value	free_token_list(t_lexer *delete_me, char *input)
{
	t_token			*current;
	t_token			*helper;
	t_return_value	error_code;

	current = delete_me->head;
	error_code = delete_me->error_code;
	while (current != NULL)
	{
		helper = current->next;
		free(current->content);
		free(current);
		current = helper;
	}
	delete_me->head = NULL;
	if (input)
		free (input);
	if (delete_me->readlined != NULL)
		free(delete_me->readlined);
	return (error_code);
}

/**
 * @brief		Searches a string for any of a set of specified delimiters. 
 * 
 * @param string 		The string to search within
 * @param delimiters	A null-terminated string containing the delimiters to 
 * search for.
 * @return char*		A pointer to the first occurrence of any delimiter in 
 * the string, or NULL if no delimiter is found.
 */
char	*ft_strpbrk(const char *string, const char *delimiters)
{
	int	i;
	int	j;

	i = 0;
	while (string[i] != '\0')
	{
		j = 0;
		while (delimiters[j] != '\0')
		{
			if (string[i] == delimiters[j])
				return ((char *)(string + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
