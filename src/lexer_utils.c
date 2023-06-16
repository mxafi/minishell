/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:59:04 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/15 13:59:06 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/lexer.h"

int	make_new_node(t_lexer *token_list, t_token *new_token)
{
	
	if (!(new_token = (t_token *)calloc(1, sizeof(t_token))))
	{
		token_list->calloc_state = CALLOC_FAIL;
		return (CALLOC_FAIL);
	}
	return (SUCCESS);
}

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
				return ((char *) (string + i - 1));
			j++;
		}
		i++;
	}
	return (NULL);
}

