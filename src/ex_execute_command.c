/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:18 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/08 16:54:08 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_err	execute_real_cmd(t_ast_node *node)
{
	//
}

t_err	execute_command(t_ast_node *node)
{
	t_err	ret;

	ret = FAILURE;
	if (wrap_fork() == 0)
	{
		// exec and handle redirections
		if (execute_bi_cmd(node) == FALSE)
			ret = execute_real_cmd(node); //setting ret in child will not work!!!
		// clean up redirections (and heredoc file if exists)
		exit(g_minishell->exit_status);
	}
	wait(&g_minishell->exit_status);
	return (ret); //ret is changed in child!!!!
}
