/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/28 20:08:37 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*free_current_token_return_next(t_token *token)
{
	t_token	*ret;

	assert(token != NULL);
	ret = token->next;
	free(token->data);
	free(token);
	return (ret);
}

/** ast_builder
 * transforms a linked list of tokens into an ast meant for easy execution
 * assumes input is valid
 * PIPE, REDIR, CMD, BI_CMD, are seperate nodes, ARG tokens live inside nodes
 * 
 * TODO things:
 * []implement missing functions
 * []check logic, should check for null returns from parse functions or not?
 */
t_ast	*ast_builder(t_token *token)
{
	t_ast	*ret;

	assert(token != NULL);
	ret = NULL;
	while (token != NULL)
	{
		if (token->type == PIPE)
			ret = parse_pipe(token, ret); //TODO
		else if (token->type == REDIR)
			ret = parse_redir(token, ret); //TODO
		else if (token->type == CMD || token->type == BI_CMD)
			ret = parse_cmd(token, ret); //TODO
		else if (token->type != ARG)
			printf("DEBUG: unexpected type in ast_builder: %i", token->type);
		token = free_current_token_return_next(token);
	}
	return (ret);
}
