/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/24 13:35:51 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Creates a new node with optional data and returns the new node.
 * 
 * @param data Either token's contents, or NULL if nothing.
 * @return t_ast* Newly created node, type of the node is
 * always AST_TOKEN_TYPE_UNDEFINED when created, function ast_set_type
 * should be used to set the type.
 */
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

void	ast_recursive_delete(t_ast *node)
{
	if (!node)
		return ;
	if (node->data)
		free(node->data);
	ast_recursive_delete(node->left);
	ast_recursive_delete(node->right);
	free(node);
}

void	ast_attach(t_ast *root, t_ast *left, t_ast *right)
{
	assert(root != NULL);
	root->left = left;
	root->right = right;
}
