/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:22 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/23 07:07:01 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ctrl_c_pipeline(int sig)
{
	(void)sig;
	kill(g_minishell->pid_pipeline[0], SIGINT);
	kill(g_minishell->pid_pipeline[1], SIGINT);
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	execute_pipeline(t_ast_node *node)
{
	int		pipe_end[2];

	if (pipe(pipe_end) < 0)
		exit(1);
	if (wrap_fork(&g_minishell->pid_pipeline[0]) == 0)
	{
		if (dup2(pipe_end[WRITING_END], STDOUT_FILENO) < 0)
			exit (1);
		close(pipe_end[READING_END]);
		executor(node->left);
		close(pipe_end[WRITING_END]);
		exit(g_minishell->exit_status);
	}
	close(pipe_end[WRITING_END]);
	if (wrap_fork(&g_minishell->pid_pipeline[1]) == 0)
	{
		if (dup2(pipe_end[READING_END], STDIN_FILENO) < 0)
			exit (1);
		executor(node->right);
		close(pipe_end[READING_END]);
		exit(g_minishell->exit_status);
	}
	close(pipe_end[READING_END]);
	signal(SIGINT, ctrl_c_pipeline);
	waitpid(g_minishell->pid_pipeline[0], &g_minishell->termination_status, 0);
	waitpid(g_minishell->pid_pipeline[1], &g_minishell->termination_status, 0);
	signal(SIGINT, SIG_DFL);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
}
