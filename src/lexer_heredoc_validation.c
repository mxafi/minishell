/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:26:00 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/10 18:17:35 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

static char	*get_heredoc_input(t_lexer *list, t_token *current,
		const char *file_path)
{
	int	child_pid;
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ((char *) 0);
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return ((char *) 0);
	}
	if (child_pid == 0)
	{
		set_child_signals();
		child_process_heredoc(list, fd);
		
	}
	parent_wait_for_child(list, fd, child_pid);
}
static void	get_temp_file_path(t_token *current, char *filename,
		int pipe_counter)
{
}

t_return_value	process_heredoc(t_lexer *token_list)
{
	t_token	*current;
	char	*temp_file_path;
	int		pipe_counter;

	current = token_list->head;
	pipe_counter = 0;
	temp_file_path = (char *)0;
	while (current != NULL && current->next != NULL)
	{
		if (current->type == PIPE)
			pipe_counter++;
		if (current->type == HEREDOC)
		{
			assert(current->next->type == STRING); //DEL ME
			get_temp_file_path(current->next->content, *temp_file_path,
					pipe_counter);
			get_heredoc_input(current->next->content, current, temp_file_path);
			free(current->content);
			current->content = ft_strdup(temp_file_path);
			free(temp_file_path);
			temp_file_path = NULL;
		}
		current = current->next;
	}
	return (SUCCESS);
}
