/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:44:33 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/17 17:02:14 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Interprets and executes the AST.
 * 
 * @param ast_node the root node of the AST.
 */
t_err	executor(t_ast_node *node)
{
	if (node->type == AST_PIPE)
	{
		execute_pipeline(node);
	}
	if (node->type == AST_COMMAND)
	{
		execute_command(node);
	}
	if (node->type == AST_BI_CMD)
	{
		execute_bi_cmd(node);
	}
}
