/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:16 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/08 13:19:57 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	size_t	i;

	g_minishell = ft_calloc(1, sizeof(t_minishell));
	if (!g_minishell)
		exit(1);
	if (init_envp())
		return (1);
	display_prompt();
	i = 0;
	while (g_minishell->envp[i])
		free(g_minishell->envp[i++]);
	vec_free(&g_minishell->env_vec);
	return (0);
}
