/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/30 16:56:37 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/** ast_builder
 * transforms a linked list of tokens into an ast meant for easy execution
 * assumes input is valid
 * PIPE, REDIR, CMD, BI_CMD, are seperate nodes, ARG tokens live inside nodes
 * 
 */
t_ast_node	*ast_builder(t_token *token)
{
	t_ast_node	*node;
	t_ast_node	*tmp;

	if (!token)
		return (NULL);
	tmp = parse_command(token); //parse everything upto a pipe, first guard against !token
	while (token->next != NULL && token->type != PIPE)
		token = token->next;
	if (token->type != PIPE)
		return (tmp);
	node = ast_create_node(NULL, AST_PIPE);
	node->left = tmp;
	node->right = ast_builder(token->next);
	return (node);
}
