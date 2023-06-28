/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:59:04 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/29 00:24:51 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/lexer.h"

/**
 * @brief 	Memory allocate a new node and initializes it to zero with callot
 * 
 * @param token_list 	used as error code placeholder
 * @param new_token		new node being tokenized	 
 * @return int			SUCCESS or CALLOC FAIL 
 */
int	make_new_node(t_lexer *token_list, t_token **new_token)
{
	
	if (!(*new_token = (t_token *)ft_calloc(1, sizeof(t_token))))
	{
		token_list->error_code = CALLOC_FAIL;
		return (CALLOC_FAIL);
	}
	return (SUCCESS);
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

	current = delete_me->token_list;
	//del this assert()
	assert(delete_me->token_list);
	while (current != NULL)
		{
			helper = current->next;
			free (current);
			current = helper;
		}
	delete_me->token_list = NULL;
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
char	*ft_strpbrk(const char	*string, const char	*delimiters)
{
	int			i;
	int			j;

	i = 0;
	while (string[i] != '\0')
	{
		j = 0;
		while (delimiters[j] != '\0')
		{
			if (string[i] == delimiters[j])
				return ((char *) (string + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

