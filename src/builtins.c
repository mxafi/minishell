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

t_return_value	ft_pwd(void)
{
	char	*working_directory_path;

	working_directory_path = getcwd(NULL, 0);
	if (working_directory_path == NULL)
	{
		perror("getcwd");
		return (FAILURE);
	}
	printf("%s\n", working_directory_path);
	free(working_directory_path);
	return (SUCCESS);
}

void	execute_builtins(t_lexer *token_list)
{
	t_token *current = token_list->head;

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
			// Add more if statements for other built-ins here
		}
		current = current->next;
	}
}