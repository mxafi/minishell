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

#include "../inc/lexer.h"

static t_return_value	child_processes_heredoc(t_lexer *list, t_token *token,
		int fd)
{
	char	*line_read;
	char	*delimiter;
	int		delimiter_length;

	ignore_signals();
	toggle_echoctl();
	delimiter = token->next->content;
	delimiter_length = ft_strlen(delimiter);
	line_read = readline("> ");
	while (line_read)
	{
		if (ft_strncmp(line_read, delimiter, delimiter_length) == 0)
			break ;
		if (*line_read)
			write(fd, line_read, ft_strlen(line_read));
		write(fd, "\n", 1);
		free(line_read);
		line_read = readline("> ");
	}
	restore_signal_defaults();
	toggle_echoctl();
	close(fd);
	exit(0);
}

static t_return_value	parent_wait_for_child(list, fd, child_pid)
{
	int	status;

	// Wait for the child process to finish
	if (waitpid(child_pid, &status, 0) == -1)
	{
		perror("waitpid");
		return ;
	}
	// Check if the child process exited normally
	if (WIFEXITED(status))
	{
		// Handle the child's exit status if needed
	}
	else if (WIFSIGNALED(status))
	{
		// Handle the case where the child was terminated by a signal
	}
	// Close the file descriptor
	close(fd);
}

static t_return_value	get_heredoc_input(t_lexer *list, t_token *current)
{
	int	child_pid;
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		list->error_code = FILE_OPEN_ERROR;
		return (list->error_code);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		list->error_code = FORK_FAIL;
		return (list->error_code);
	}
	if (child_pid == 0)
		child_processes_heredoc(list, current, fd);
	if (parent_wait_for_child(fd, child_pid) != SUCCESS)
	{
		list->error_code = WAIT_FAIL;
		return (list->error_code);
	}
	close(fd);
	return (list->error_code);
}

static t_return_value	get_temp_file_path(t_lexer *list, t_token *current,
		int pipe_counter)
{
	char	*temp_file_path;
	char	*pipe_counter_str;

	pipe_counter_str = ft_itoa(pipe_counter);
	if (!pipe_counter_str)
	{
		list->error_code = CALLOC_FAIL;
		return (list->error_code);
	}
	temp_file_path = ft_strjoin("/tmp/minishell_heredoc.tmp", pipe_counter_str);
	free(pipe_counter_str);
	if (!temp_file_path)
	{
		list->error_code = CALLOC_FAIL;
		return (list->error_code);
	}
	current->content = temp_file_path;
	return (SUCCESS);
}

t_return_value	process_heredoc(t_lexer *token_list)
{
	t_token	*current;
	int		pipe_counter;

	current = token_list->head;
	pipe_counter = 0;
	while (current != NULL && current->next != NULL)
	{
		if (current->type == PIPE)
			pipe_counter++;
		if (current->type == HEREDOC)
		{
			if (get_temp_file_path(token_list, current,
					pipe_counter) != SUCCESS)
				return (CALLOC_FAIL);
			if (get_heredoc_input(token_list, current) != SUCCESS)
				return (CALLOC_FAIL);
			free(current->content);
		}
		current = current->next;
	}
	return (SUCCESS);
}
