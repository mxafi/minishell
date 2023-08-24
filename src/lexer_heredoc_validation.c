/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:26:00 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/11 14:10:19by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Handles the child process responsible for reading heredoc input
 *        and writing it to the specified file descriptor.
 * 
 * @param list      The token list.
 * @param token     The current heredoc token.
 * @param fd        The file descriptor to write heredoc content to.
 */
static void	child_processes_heredoc(t_token *token, int fd)
{
	char	*line_read;
	char	*delimiter;
	int		delimiter_length;

	delimiter = token->next->content;
	delimiter_length = ft_strlen(delimiter);
	while (1)
	{
		line_read = heredoc_get_line();
		if (!line_read)
			break ;
		if (ft_strncmp(line_read, delimiter, delimiter_length + 1) == 0)
			break ;
		ft_putstr_fd(line_read, fd);
		ft_putchar_fd('\n', fd);
		free(line_read);
	}
	close(fd);
	exit(0);
}

/**
 * @brief Waits for the child process to complete and examines its exit status.
 * 
 * This function uses the `waitpid` system call to wait for the specified
 * child process to complete its execution. It also examines the exit status
 * of the child process to determine the reason for its termination.
 * 
 * @param list      The token list.
 * @param fd        The file descriptor associated with the child process.
 * @param child_pid The process ID of the child process.
 * @return t_return_value The error code associated with the child process.
 *         If the child process terminated normally, the return value is
 *         the exit status of the child process. If the child process was
 *         terminated by a signal, the return value is the corresponding
 *         signal number.
 */
static t_return_value	parent_wait_for_child(t_lexer *list, int fd,
		int child_pid)
{
	int	exit_status;

	g_minishell->pid_single = child_pid;
	signal(SIGINT, sig_heredoc);
	signal(SIGQUIT, sig_heredoc);
	if (waitpid(child_pid, &exit_status, 0) == -1)
	{
		list->error_code = WAIT_PID_FAIL;
		perror("waitpid");
	}
	else if (WIFEXITED(exit_status))
	{
		list->error_code = WEXITSTATUS(exit_status);
	}
	else if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			ft_putchar_fd('\n', 1);
		list->error_code = WIFSIGNALED(exit_status);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd);
	return (list->error_code);
}

/**
 * @brief Sets up the child process for heredoc input and waits
 * for its completion.
 * 
 * This function creates a child process using the `fork` system call to handle
 * the heredoc input. The child process reads user input until a specified
 * delimiter is encountered and writes the input to the provided file
 * descriptor.
 * 
 * @param list      The token list.
 * @param current   The current token representing the heredoc.
 * @return t_return_value The error code associated with the process.
 */
static t_return_value	get_heredoc_input(t_lexer *list, t_token *current)
{
	int	child_pid;
	int	fd;

	fd = open(current->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		list->error_code = FILE_OPEN_ERROR;
		return (FILE_OPEN_ERROR);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		list->error_code = FORK_FAIL;
		close(fd);
		return (FORK_FAIL);
	}
	if (child_pid == 0)
		child_processes_heredoc(current, fd);
	if (parent_wait_for_child(list, fd, child_pid) != SUCCESS)
		return (WAIT_PID_FAIL);
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Generates a temporary file path for heredoc content
 * based on the pipe counter.
 * 
 * This function constructs a unique temp path for storing heredoc content.
 * The path includes a combination of a base path and a pipe counter to ensure
 * uniqueness for each heredoc instance.
 * 
 * @param list          The token list.
 * @param current       The current token representing the heredoc.
 * @param pipe_counter  The count of pipes encountered so far.
 * @return t_return_value The error code associated with
 * generating the file path.
 */
static t_return_value	get_temp_file_path(t_lexer *list, t_token *current,
		int pipe_counter)
{
	char	*temp_file_path;
	char	*pipe_counter_str;

	pipe_counter_str = ft_itoa(pipe_counter);
	if (!pipe_counter_str)
	{
		list->error_code = MALLOC_FAIL;
		return (list->error_code);
	}
	temp_file_path = ft_strjoin("/tmp/minishell_heredoc.tmp", pipe_counter_str);
	free(pipe_counter_str);
	if (!temp_file_path)
	{
		list->error_code = MALLOC_FAIL;
		return (list->error_code);
	}
	if (current->content)
		free(current->content);
	current->content = temp_file_path;
	return (SUCCESS);
}

/**
 * @brief Processes heredoc tokens by coordinating temporary file creation,
 *        heredoc input handling, and memory cleanup.
 * 
 * @param token_list The token list containing the heredoc tokens.
 * @return t_return_value The final error code of the heredoc processing.
 */
t_return_value	process_heredoc(t_lexer *token_list)
{
	t_token	*current;
	int		pipe_counter;

	current = token_list->head;
	pipe_counter = 1;
	while (current->next != NULL)
	{
		if (current->type == PIPE)
			pipe_counter++;
		if (current->type == HEREDOC)
		{
			if (get_temp_file_path(
					token_list, current, pipe_counter) != SUCCESS)
				return (token_list->error_code);
			if (get_heredoc_input(token_list, current) != SUCCESS)
				return (token_list->error_code);
		}
		current = current->next;
	}
	return (SUCCESS);
}
