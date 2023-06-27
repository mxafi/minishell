/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:16 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/27 16:36:56 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*g_minishell;

void	display_prompt(void)
{
	char	*input;

	while (1)
	{
		input = get_input();
		if (!input)
			return ;
		lexer(input);
		free(input);
	}
}

int	main(void)
{
	g_minishell = ft_calloc(1, sizeof(t_minishell));
	if (!g_minishell)
		exit(1); //display an error of some kind before exiting and set errno?
	display_prompt();
	return (0);
}
