/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 08:58:32 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Creates an Abstract Syntax Tree (AST) with top-down recursion.
 * 
 * @param token Head of the linked list of tokens.
 * @return t_ast_node* Head of the AST, a command or a pipe node.
 */
t_ast_node	*ast_builder(t_token *token)
{
	t_ast_node	*node;
	t_ast_node	*tmp;

	if (!token)
		return (NULL);
	tmp = ast_parse_command(token);
	while (token->next != NULL && token->type != PIPE)
		token = token->next;
	if (token->type != PIPE)
		return (tmp);
	node = ast_create_node(NULL, AST_PIPE);
	node->left = tmp;
	node->right = ast_builder(token->next);
	return (node);
}
