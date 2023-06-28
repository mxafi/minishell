/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_data_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:51:55 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/28 20:08:46 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ast_recursive_delete(t_ast *node)
{
	if (!node)
		return ;
	if (node->exec_argv)
		free(node->exec_argv);
	ast_recursive_delete(node->left);
	ast_recursive_delete(node->right);
	free(node);
}

void	ast_set_exec_argv(t_ast *node, char *string, int position)
{
	assert(node != NULL);
	assert(node->exec_argv != NULL);
	assert(node->exec_argv[position] == NULL);
	node->exec_argv[position] = string;
}

void	ast_set_type(t_ast *node, int token_type)
{
	assert(node != NULL);
	assert(node->token_type == AST_TOKEN_TYPE_UNDEFINED);
	node->token_type = token_type;
}

void	ast_attach(t_ast *root, t_ast *left, t_ast *right)
{
	assert(root != NULL);
	root->left = left;
	root->right = right;
}
