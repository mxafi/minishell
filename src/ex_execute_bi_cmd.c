/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_bi_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:13 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/08 17:21:21 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	execute_bi_cmd(t_ast_node *node)
{
	if (!ft_strncmp(node->exec_argv[0], "exit", 5))
		//run exit
	else if (!ft_strncmp(node->exec_argv[0], "echo", 5))
		//run echo
	else if (!ft_strncmp(node->exec_argv[0], "cd", 3))
		//run cd
	else if (!ft_strncmp(node->exec_argv[0], "env", 4))
		//run env
	else if (!ft_strncmp(node->exec_argv[0], "export", 7))
		//run export
	else if (!ft_strncmp(node->exec_argv[0], "pwd", 4))
		//run pwd
	else if (!ft_strncmp(node->exec_argv[0], "unset", 6))
		//run unset
	else
		return (FALSE);
	return (TRUE);
}
