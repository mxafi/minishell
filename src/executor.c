/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:44:33 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/21 16:06:53 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ret_exit_status(int termination_status)
{
	int	exit_status;

	exit_status = 1;
	if (WIFEXITED(termination_status))
		exit_status = WEXITSTATUS(termination_status);
	else if (WIFSIGNALED(termination_status))
		exit_status = 128 + WTERMSIG(termination_status);
	exit_status %= 255;
	return (exit_status);
}

/**
 * @brief Forks a process and returns the pid conventionally
 * and additionally with a pointer.
 * @param ext_pid where to write the pid of the resulting fork, can be NULL.
 * @return pid_t - the pid of the resulting fork.
 */
pid_t	wrap_fork(pid_t	*ext_pid)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		write(STDOUT_FILENO, "error", 5);
		perror("error creating a fork");
		exit(1);
	}
	if (ext_pid)
		*ext_pid = pid;
	return (pid);
}

/**
 * @brief Interprets and executes the AST.
 * 
 * @param ast_node the root node of the AST.
 */
void	executor(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == AST_PIPE)
	{
		g_minishell->is_pipeline = 1;
		execute_pipeline(node);
	}
	else if (node->type == AST_COMMAND)
		execute_command(node);
}
