/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:18 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/15 17:12:43 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_bool	is_absolute_path(t_ast_node *node)
{
	int		i;

	i = 0;
	while (node->exec_argv[0][i])
	{
		if (node->exec_argv[0][i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	parse_path(t_ast_node *node)
{
	char	*path;
	char	*tmp_path;
	char	**split_path;
	int		i;
	char	*found_file;

	node->exec_file = ft_strdup(node->exec_argv[0]);
	tmp_path = (char *)env_get_value_by_key("PATH");
	if (tmp_path == NULL)
		return ;
	path = ft_strdup(tmp_path);
	split_path = ft_split(path, ':');
	if (!split_path)
		exit(1);
	free(path);
	i = 0;
	while (split_path[i] != NULL)
	{
		tmp_path = ft_strjoin(split_path[i], "/");
		if (!tmp_path)
			exit(1);
		found_file = ft_strjoin(tmp_path, node->exec_argv[0]);
		if (!found_file)
			exit(1);
		free(tmp_path);
		if (access(found_file, X_OK) == 0)
		{
			free(node->exec_file);
			node->exec_file = found_file;
			break ;
		}
		free(found_file);
		i++;
	}
	i = 0;
	while (split_path[i] != NULL)
		free(split_path[i++]);
	free(split_path);
}

void	print_signal(int termination_status)
{
	int	sig_num;

	if (WIFEXITED(termination_status) || !WIFSIGNALED(termination_status))
		return ;
	sig_num = WTERMSIG(termination_status);
	if (sig_num == SIGINT)
		ft_putchar_fd('\n', 1);//check this against real behavior
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);//check this against real behavior
}

void	execute_real_cmd(t_ast_node *node)
{
	if (is_absolute_path(node) == TRUE)
		node->exec_file = ft_strdup(node->exec_argv[0]);
	else
		parse_path(node);
	if (wrap_fork() == 0)
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

void	execute_command(t_ast_node *node)
{
	if (node->redir_count > 0)
	{
		if (wrap_fork() == 0)
		{
			// exec and handle redirections
			if (execute_bi_cmd(node) == FALSE)
				execute_real_cmd(node);
			// clean up redirections (and heredoc files if exists /tmp/minishell_heredoc.tmp)
			exit(g_minishell->exit_status);
		}
		wait(&g_minishell->termination_status);
		g_minishell->exit_status = ret_exit_status(
			g_minishell->termination_status);
	}
	else
	{
		if (execute_bi_cmd(node) == FALSE)
			execute_real_cmd(node);
	}
}
