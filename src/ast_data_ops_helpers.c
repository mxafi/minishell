/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_data_ops_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:51:55 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/05 23:47:21 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ast_set_exec_argv(t_ast_node *node, char *string, int position)
{
	assert(node != NULL);
	assert(node->exec_argv != NULL);
	assert(node->exec_argv[position] == NULL);
	node->exec_argv[position] = string;
}

void	ast_set_type(t_ast_node *node, t_ast_node_type type)
{
	assert(node != NULL);
	assert(node->type == AST_VALUE_NOT_DEFINED);
	node->type = type;
}

void	ast_attach(t_ast_node *root, t_ast_node *left, t_ast_node *right)
{
	assert(root != NULL);
	root->left = left;
	root->right = right;
}
