/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_data_ops_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:01:04 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/29 13:01:31 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ast_recursive_delete(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->exec_argv)
		free(node->exec_argv);
	ast_recursive_delete(node->left);
	ast_recursive_delete(node->right);
	free(node);
}
