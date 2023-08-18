/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:22 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/18 13:15:56 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(t_ast_node *node)
{
	int	pipe_end[2];

	if (pipe(pipe_end) < 0)
		exit(1);
	// printf("Debug: execute_pipeline: start with read_fd:%i and write_fd:%i\n", pipe_end[0], pipe_end[1]);
	if (wrap_fork() == 0)
	{
		if (dup2(pipe_end[WRITING_END], STDOUT_FILENO) < 0)
			exit (1);
		close(pipe_end[READING_END]);
		executor(node->left);
		exit(g_minishell->exit_status);
	}
	wait(&g_minishell->termination_status);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	// printf("Debug: execute_pipeline: left fork returned!\n");
	close(pipe_end[WRITING_END]);
	if (wrap_fork() == 0)
	{
		if (dup2(pipe_end[READING_END], STDIN_FILENO) < 0)
			exit (1);
		close(pipe_end[WRITING_END]);
		// printf("Debug: execute_pipeline: right fork calling executor!\n");
		executor(node->right);
		// printf("Debug: execute_pipeline: right fork executor call returned!\n");
		exit(g_minishell->exit_status);
	}
	wait(&g_minishell->termination_status);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	// printf("Debug: execute_pipeline: right fork returned!\n");
	close(pipe_end[READING_END]);
	// printf("Debug: execute_pipeline: the end\n");
}
