/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:18 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 11:38:34 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_real_cmd(t_ast_node *node)
{
	node->exec_file = ft_strdup(node->exec_argv[0]);
	if (is_absolute_path(node) == FALSE)
		parse_path(node);
	if (wrap_fork(NULL) == 0)
	{
		if (execve(node->exec_file, node->exec_argv, g_minishell->envp) == -1)
		{
			ft_putstr_fd("shellfishy: ", 2);
			ft_putstr_fd(node->exec_file, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	wait(&g_minishell->termination_status);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	print_signal(g_minishell->termination_status);
}

int	is_unforkable_builtin(char *cmd)
{
	const char	*unforkable[4] = {"cd", "export", "unset", "exit"};
	const int	unforkable_len = 4;
	int			i;

	i = 0;
	while (i < unforkable_len)
	{
		if (ft_strncmp(cmd, unforkable[i], 7) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	sig_single(int sig)
{
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (sig == SIGINT)
		kill(g_minishell->pid_single, SIGINT);
	else if (sig == SIGQUIT)
	{
		kill(g_minishell->pid_single, SIGQUIT);
		ft_putstr_fd("Quit: 3\n", 1);
	}
}

static void	execute_command_fork_single(t_ast_node *node)
{
	if (wrap_fork(&g_minishell->pid_single) == 0)
	{
		execute_command_redirections(node);
		if (execute_bi_cmd(node) == FALSE)
			execute_real_cmd(node);
		execute_command_redirections_cleanup(node);
		exit(g_minishell->exit_status);
	}
}

void	execute_command(t_ast_node *node)
{
	if (g_minishell->is_pipeline || is_unforkable_builtin(node->exec_argv[0]))
	{
		execute_command_redirections(node);
		if (execute_bi_cmd(node) == FALSE)
			execute_real_cmd(node);
		execute_command_redirections_cleanup(node);
		if (g_minishell->is_pipeline)
			exit(g_minishell->exit_status);
	}
	else
	{
		execute_command_fork_single(node);
		signal(SIGINT, sig_single);
		signal(SIGQUIT, sig_single);
		waitpid(g_minishell->pid_single, &g_minishell->termination_status, 0);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		g_minishell->exit_status = ret_exit_status(
				g_minishell->termination_status);
	}
}
