/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:22 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/21 18:22:06 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(t_ast_node *node)
{
	int		pipe_end[2];
	pid_t	pid[2];

	if (pipe(pipe_end) < 0)
		exit(1);
	printf("Debug: execute_pipeline: fork left\n");
	if (wrap_fork(&pid[0]) == 0)
	{
		if (dup2(pipe_end[WRITING_END], STDOUT_FILENO) < 0)
			exit (1);
		close(pipe_end[READING_END]);
		printf("Debug: execute_pipeline: fork left call executor\n");
		executor(node->left);
		printf("Debug: execute_pipeline: fork left return from executor\n");
		close(pipe_end[WRITING_END]);
		printf("Debug: execute_pipeline: fork left exiting\n");
		exit(g_minishell->exit_status);
	}
	printf("Debug: execute_pipeline: fork right\n");
	if (wrap_fork(&pid[1]) == 0)
	{
		if (dup2(pipe_end[READING_END], STDIN_FILENO) < 0)
			exit (1);
		close(pipe_end[WRITING_END]);
		printf("Debug: execute_pipeline: fork right call executor\n");
		executor(node->right);
		printf("Debug: execute_pipeline: fork right return from executor\n");
		close(pipe_end[READING_END]);
		printf("Debug: execute_pipeline: fork right exiting\n");
		exit(g_minishell->exit_status);
	}
	waitpid(pid[0], &g_minishell->termination_status, 0);
	waitpid(pid[1], &g_minishell->termination_status, 0);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	close(pipe_end[READING_END]);
	close(pipe_end[WRITING_END]);
}
