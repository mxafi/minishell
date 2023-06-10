/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:16 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/10 13:05:49 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(void)
{
	char	*line_read;

	line_read = readline("shellfish🦞>");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	main(void)
{
	char	*input;

	// init_shell();
	while (1)
	{
		// display_prompt();
		input = get_input();
		if (input)
		{
		// 	lexer(input);
			ft_printf(">>>>%s<<<<\n", input);
			free(input);
		}
	}
	return (0);
}
