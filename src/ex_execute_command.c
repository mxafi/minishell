/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:18 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 12:57:08 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_signal(int termination_status)
{
	int	sig_num;

	if(WIFEXITED(termination_status) || !WIFSIGNALED(termination_status))
		return ;
	sig_num = WTERMSIG(termination_status);
	if (sig_num == SIGINT)
		ft_putchar_fd('\n', 1);//check this against real behavior
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);//check this against real behavior
}

void	execute_real_cmd(t_ast_node *node)
{
	//determine if cmd is already an absolute path or not
	// if already absolute (contains /), then move on
	// if not absolute (does not contain /), then parse PATH variable and go through each path trying if exists, replace cmd
	node->exec_file = node->exec_argv[0]; // this is temporary, before finding path is implemented
	if (wrap_fork() == 0)
	{
		if (execve(node->exec_file, node->exec_argv, g_minishell->envp) == -1)
		{
			perror(node->exec_file);//check if this is the correct wording??
			exit(127);
		}
	}
	wait(&g_minishell->termination_status);
	g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	print_signal(g_minishell->termination_status);
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
