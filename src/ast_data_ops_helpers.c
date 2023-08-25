/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_data_ops_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:51:55 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/25 10:56:35 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ast_set_exec_argv(t_ast_node *node, char *string, int position)
{
	node->exec_argv[position] = string;
}

void	ast_set_type(t_ast_node *node, t_ast_node_type type)
{
	node->type = type;
}

void	ast_attach(t_ast_node *root, t_ast_node *left, t_ast_node *right)
{
	root->left = left;
	root->right = right;
}
