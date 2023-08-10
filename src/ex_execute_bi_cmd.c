/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_bi_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:13 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 22:01:21 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	execute_bi_cmd(t_ast_node *node)
{
	//TODO: create custom function for each that sanitizes and validates input, as well as, does the job
	if (!ft_strncmp(node->exec_argv[0], "exit", 5))
		exit(0);//wip run exit
	else if (!ft_strncmp(node->exec_argv[0], "echo", 5))
		exit(1);//wip run echo
	else if (!ft_strncmp(node->exec_argv[0], "cd", 3))
		exit(69);//wip run cd
	else if (!ft_strncmp(node->exec_argv[0], "env", 4))
		env_print_list();//wip
	else if (!ft_strncmp(node->exec_argv[0], "export", 7))
		exit(1);//wip run export
	else if (!ft_strncmp(node->exec_argv[0], "pwd", 4))
		exit(1);//wip run pwd
	else if (!ft_strncmp(node->exec_argv[0], "unset", 6))
		env_unset_key(node->exec_argv[1]);//wip
	else
		return (FALSE);
	return (TRUE);
}
