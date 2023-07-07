/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:59:04 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/07 18:27:42 by lclerc           ###   ########.fr       */
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
t_return_value	make_new_node(t_lexer *token_list, t_token *new_token)
{
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
	{
		token_list->error_code = CALLOC_FAIL;
		return (CALLOC_FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief 
 * 
 *
 * @param list 
 * @param token 
 * @param token_type 
 * @param input 
 */
t_return_value	set_token_type_and_quote_state(t_lexer *list, t_token *token,
		t_token_type token_type, char *input)
{
	if (list->state == UNDEFINED)
	{
		if (token_type != UNDEFINED)
			token->type = token_type;
		else
		{
			if (input[0] == '\'' || input[0] == '\"')
				handle_quotes(list, token, token_type, input);
			else if (input[0] == '>')
				token->type = OUTFILE;
			else if (input[0] == '<')
				token->type = INFILE;
			else if (input[0] == '|')
				token->type = PIPE;
			else if (input[0] == ' ')
				token->type = SPACE;
		}
	}
	else if (list->state == SGL_QUOTE_OPENED \
			|| list->state == SGL_QUOTE_CAN_BE_CLOSED \
			|| list->state == DBL_QUOTE_OPENED || \
				list->state == DBL_QUOTE_CAN_BE_CLOSED) \
		handle_quotes(list, token, token_type, input);
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
