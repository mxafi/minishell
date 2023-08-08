/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:44:33 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/08 15:56:25 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	wrap_fork()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		write(STDOUT_FILENO, "error", 5);
		perror("error creating a fork");
		exit(1);
	}
	return (pid);
}

/**
 * @brief Interprets and executes the AST.
 * 
 * @param ast_node the root node of the AST.
 */
t_err	executor(t_ast_node *node)
{
	t_err	ret;

	if (!node)
		return (FAILURE);
	ret = SUCCESS;
	if (node->type == AST_PIPE)
		ret = execute_pipeline(node);
	else if (node->type == AST_COMMAND)
		ret = execute_command(node);
	g_minishell->exit_status = g_minishell->exit_status % 255; //remember to use WIFEXISTED and WEXITSTATUS
	return (ret);
}
