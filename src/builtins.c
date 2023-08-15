/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:58:09 by lclerc            #+#    #+#             */
/*   Updated: 2023/08/14 16:38:44by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Execute the pwd built-in command.
 * 
 * This function prints the current working directory to stdout.
 * 
 * @return t_return_value Success or Failure.
 */
void	ft_pwd(void)
{
	char	*working_directory_path;

	working_directory_path = getcwd(NULL, 0);
	if (working_directory_path == NULL)
	{
		perror("getcwd");
		g_minishell->exit_status = FAILURE; // Set exit status
		return ;
	}
	ft_putstr_fd(working_directory_path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(working_directory_path);

	// Set the proper exit status
	g_minishell->exit_status = SUCCESS;
}

/**
 * @brief Execute the echo built-in command.
 * 
 * This function prints the arguments to stdout with an optional newline.
 * 
 * @param current The token representing the echo command.
 */

static void	ft_echo(t_token *current)
{
	t_bool	print_newline;

	print_newline = TRUE;
	if (current->next->type == ARG)
	{
		current = current->next;
		if (current->next != NULL && ft_strncmp(current->content, "-n", 2) == 0)
		{
			print_newline = FALSE;
			current = current->next;
		}
	}
	while (current->type == ARG && current != NULL)
	{
		ft_putstr_fd(current->content, STDOUT_FILENO);
		if (current->next != NULL && current->type == ARG)
		{
			current = current->next;
			ft_putstr_fd(" ", STDOUT_FILENO);
		}
		else
			break ;
	}
	if (print_newline == TRUE)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
/**
 * @brief Execute the cd built-in command.
 * 
 * @param current The token representing the cd command.
 * @return t_return_value Success or Failure.
 */
static t_return_value	ft_cd(t_token *current)
{
	char	*path;

	if (current->next == NULL || current->next->type != ARG)
	{
		ft_putstr_fd("Shellfish☠️> cd: missing directory\n", STDERR_FILENO);
		return (INVALID_ARGUMENT);
	}
	path = current->next->content;
	if (chdir(path) == -1)
	{
		perror("Shellfish> cd");
		return (DIRECTORY_NOT_FOUND);
	}
	return (SUCCESS);
}

void	execute_builtins(t_lexer *token_list)
{
	t_token *current;

	current = token_list->head;
	while (current != NULL)
	{
		if (current->type == CMD)
		{
			if (ft_strncmp(current->content, "pwd", 3) == 0)
			{
				// Execute the pwd built-in
				printf("#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_\n");
				ft_pwd();
				printf("#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_\n");
			}
			else if (ft_strncmp(current->content, "echo", 4) == 0)
			{
				// Execute the pwd built-in
				printf("#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_\n");
				ft_echo(current);
				printf("#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_#_\n");
			}
			else if (ft_strncmp(current->content, "cd", 2) == 0)
			{
				ft_cd(current);
				printf("how to handle errors here\n");
			}
		}
		current = current->next;
	}
}