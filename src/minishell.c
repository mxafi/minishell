/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:34:16 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/30 13:50:41 by malaakso         ###   ########.fr       */
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
		exit(1); //display an error of some kind before exiting and set errno (set by malloc already tho)?
	if (init_envp())
		return (1);
	//display_prompt();
	env_print_list();
	i = 0;
	while (g_minishell->envp[i])
		free(g_minishell->envp[i++]);
	vec_free(&g_minishell->env_vec);
	return (0);
}
