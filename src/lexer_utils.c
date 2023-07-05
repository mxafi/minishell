/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:59:04 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/05 19:49:15 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

/**
 * @brief 	Memory allocate a new node and initializes it to zero with calloc
 * 
 * @param token_list 	used as error code placeholder
 * @param new_token		new node being tokenized		
 * @return t_return_value	SUCCESS or CALLOC FAIL 
 */
t_return_value	make_new_node(t_lexer *token_list, t_token **new_token)
{
	if (!(*new_token = (t_token *)ft_calloc(1, sizeof(t_token))))
	{
		token_list->error_code = CALLOC_FAIL;
		return (CALLOC_FAIL);
	}
	return (SUCCESS);
}

void	set_list_quote_state()
{
	
}

/**
 * @brief 
 * 
 * 
 * @param list 
 */
void	add_null_string_token_if_empty_quote(t_lexer *list)
{
	t_token	*current;
	char	*empty_string;

	empty_string = "";
	current = list->head;
	while (current != NULL)
		current = current->next;
	if (current->type == SINGLE_QUOTE || current->type == DOUBLE_QUOTE)
	{
		if (current->type == SINGLE_QUOTE && list->state != NEED_SGL_QUOTE_STR)
			list->state = NEED_SGL_QUOTE_STR;
		else if (current->type == SINGLE_QUOTE)
		 {
			string_to_token(list, empty_string, empty_string);
			list->state == SGL_QUOTE_STR;
		 }
		else if (current->type == DOUBLE_QUOTE && \
			list->state != NEED_DBL_QUOTE_STR)
			list->state = NEED_DBL_QUOTE_STR;
		else if (current->type == DOUBLE_QUOTE)
		 {
			string_to_token(list, empty_string, empty_string);
			list->state == DBL_QUOTE_STR;
		 }
	}
}

/**
 * @brief	Frees the token list
 * 
 * @param delete_me	The list 
 * @return int		error code if called due to a syntax validation error 
 */
int	free_token_list(t_lexer *delete_me)
{
	t_token	*current;
	t_token	*helper;

	current = delete_me->head;
	//del this assert()
	assert(delete_me->head);
	while (current != NULL)
	{
		helper = current->next;
		free(current);
		current = helper;
	}
	delete_me->head = NULL;
	//check if that return is needed
	return (delete_me->error_code);
}

/**
 * @brief 
 * 
 * @param string 
 * @param delimiters
 * @return char* 
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
