/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:01:18 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/23 16:27:51 by lclerc           ###   ########.fr       */
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

int	open_redir_file(const char *file_path, int flags)
{
	const int	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int	file = open(file_path, flags, mode);

	if (file == -1)
	{
		ft_putstr_fd("shellfishy: ", 2);
		perror(file_path);
	}
	return (file);
}

void	execute_command_redirections_cleanup(t_ast_node *node)
{
	int					current_redir_idx;
	t_ast_redir_type	c_type;
	t_redir				*c_redir;

	current_redir_idx = 0;
	while (current_redir_idx < node->redir_count)
	{
		c_redir = node->redirections[current_redir_idx];
		c_type = c_redir->type;
		close(c_redir->file_descriptor);
		if (c_type == AST_HEREDOC)
			unlink(c_redir->argument);
		else if (c_type == AST_NULL_REDIR)
		{
			unlink(c_redir->argument);
			g_minishell->exit_status = 1;
		}
		if (c_redir->file_descriptor == -1)
			exit(1);
		current_redir_idx++;
	}
}

void	execute_command_redirections(t_ast_node *node)
{
	int					current_redir_idx;
	t_ast_redir_type	c_type;
	t_redir				*c_redir;

	current_redir_idx = 0;
	while (current_redir_idx < node->redir_count)
	{
		c_redir = node->redirections[current_redir_idx];
		c_type = c_redir->type;
		if (c_type == AST_INFILE)
		{
			c_redir->file_descriptor = open_redir_file(c_redir->argument, O_RDONLY);
			dup2(c_redir->file_descriptor, STDIN_FILENO);
		}
		else if (c_type == AST_OUTFILE)
		{
			c_redir->file_descriptor = open_redir_file(c_redir->argument, O_CREAT | O_WRONLY | O_TRUNC);
			dup2(c_redir->file_descriptor, STDOUT_FILENO);
		}
		else if (c_type == AST_APPEND)
		{
			c_redir->file_descriptor = open_redir_file(c_redir->argument, O_CREAT | O_WRONLY | O_APPEND);
			dup2(c_redir->file_descriptor, STDOUT_FILENO);
		}
		else if (c_type == AST_HEREDOC)
		{
			c_redir->file_descriptor = open_redir_file(c_redir->argument, O_RDONLY);
			dup2(c_redir->file_descriptor, STDIN_FILENO);
		}
		else
		{
			ft_putstr_fd("error: execute_command_redirections\n", 2);
			exit(1);
		}
		if (c_redir->file_descriptor == -1)// && (c_type == AST_OUTFILE || c_type == AST_APPEND)
		{
			//free(c_redir->argument);
			//c_redir->argument = ft_strdup("/tmp/minishell_null_redirection");
			//c_redir->file_descriptor = open_redir_file(c_redir->argument, O_CREAT | O_WRONLY | O_TRUNC);
			//dup2(c_redir->file_descriptor, STDOUT_FILENO);
			//c_type = AST_NULL_REDIR;
			execute_command_redirections_cleanup(node);
			break ;
		}
		current_redir_idx++;
	}
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

void	ctrl_c_single(int sig)
{
	(void)sig;
	kill(g_minishell->pid_single, SIGINT);
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
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
		if (wrap_fork(&g_minishell->pid_single) == 0)
		{
			execute_command_redirections(node);
			if (execute_bi_cmd(node) == FALSE)
				execute_real_cmd(node);
			execute_command_redirections_cleanup(node);
			exit(g_minishell->exit_status);
		}
		signal(SIGINT, ctrl_c_single);
		waitpid(g_minishell->pid_single, &g_minishell->termination_status, 0);
		signal(SIGINT, SIG_DFL);
		g_minishell->exit_status = ret_exit_status(
				g_minishell->termination_status);
	}
}
