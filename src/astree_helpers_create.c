/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_helpers_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:47:24 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/24 21:52:17 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// creates a node with optional data and type of AST_TOKEN_TYPE_UNDEFINED
t_ast	*ast_create_node(char *data)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->data = data;
	node->type = AST_TOKEN_TYPE_UNDEFINED;
	return (node);
}

void	ast_set_data(t_ast *node, char *data)
{
	assert(node != NULL);
	assert(node->data == NULL);
	node->data = data;
}

void	ast_replace_data(t_ast *node, char *data)
{
	assert(node != NULL);
	assert(node->data != NULL);
	free(node->data);
	node->data = data;
}

void	ast_set_type(t_ast *node, int type)
{
	assert(node != NULL);
	assert(node->type == AST_TOKEN_TYPE_UNDEFINED);
	node->type = type;
}

void	ast_attach(t_ast *root, t_ast *left, t_ast *right)
{
	assert(root != NULL);
	root->left = left;
	root->right = right;
}
