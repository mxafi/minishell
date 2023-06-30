/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/30 11:34:52 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/** ast_builder
 * transforms a linked list of tokens into an ast meant for easy execution
 * assumes input is valid
 * PIPE, REDIR, CMD, BI_CMD, are seperate nodes, ARG tokens live inside nodes
 * 
 * TODO things:
 * []implement missing functions
 * []check logic, should check for null returns from parse functions or not?
 */
t_ast_node	*ast_recursive_builder(t_token *token, t_ast_node *node)
{
	while (token != NULL)
	{
		if (token->type == PIPE)
			node = parse_pipe(token, node); //TODO
		else if (token->type == REDIR)
			node = parse_redir(token, node); //TODO
		else if (token->type == CMD || token->type == BI_CMD)
			node = parse_cmd(token, node); //TODO
		else if (token->type == ARG)
			node = parse_arg(token, node);
		else
			printf("DEBUG: unexpected type in ast_builder: %i", token->type);
		token = free_current_token_return_next(token);
	}
	return (node);
}
