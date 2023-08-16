/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_bi_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:13 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/16 11:26:21 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	execute_bi_cmd(t_ast_node *node)
{
	if (!ft_strncmp(node->exec_argv[0], "exit", 5))
		ft_exit(node);
	else if (!ft_strncmp(node->exec_argv[0], "echo", 5))
		ft_echo(node);
	else if (!ft_strncmp(node->exec_argv[0], "cd", 3))
	 	ft_cd(node);
	else if (!ft_strncmp(node->exec_argv[0], "env", 4))
		env_print_list();//wip
	else if (!ft_strncmp(node->exec_argv[0], "export", 7))
		ft_export(node);
	else if (!ft_strncmp(node->exec_argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(node->exec_argv[0], "unset", 6))
		ft_unset(node);//wip
	else
		return (FALSE);
	return (TRUE);
}
