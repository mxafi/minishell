/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:38:05 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/06 17:54:48 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	label_single_quote(t_lexer *list, t_token token)
{
	if (list->state != SGL_QUOTE_OPENED)
		list->state = SGL_QUOTE_OPENED;
	else if (current->type == SINGLE_QUOTE)
	{
		string_to_token(list, empty_string, empty_string);
		list->state == SGL_QUOTE_STR;
	}
}

void	label_double_quote(t_lexer *list, t_token token)
{
	if ( list->state != NEED_DBL_QUOTE_STR)
		list->state = NEED_DBL_QUOTE_STR;
	else if (current->type == DOUBLE_QUOTE)
	{
		string_to_token(list, empty_string, empty_string);
		list->state == DBL_QUOTE_STR;
	}