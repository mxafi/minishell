/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:18 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 11:05:16 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_real_cmd(t_ast_node *node)
{
	//
}

void	execute_command(t_ast_node *node)
{
	if (wrap_fork() == 0)
	{
		// exec and handle redirections
		if (execute_bi_cmd(node) == FALSE)
			execute_real_cmd(node);
		// clean up redirections (and heredoc file if exists)
		exit(g_minishell->exit_status);
	}
	wait(&g_minishell->termination_status);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
}
