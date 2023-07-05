/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_data_ops_alloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:47:24 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/05 23:45:18 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast_node	*ast_create_node(char **exec_argv, t_ast_node_type type)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->exec_argv = exec_argv;
	node->type = type;
	return (node);
}

char	**ast_create_empty_exec_argv(int length)
{
	char	**array;

	if (length < 1)
		return (NULL);
	array = ft_calloc(1, sizeof(char *) * (length + 1));
	if (!array)
		return (NULL);
	array[length] = NULL;
	return (array);
}

t_redir	**ast_create_empty_redirections(int count)
{
	t_redir	**array_of_structs;
	int		i;

	if (count < 1)
		return (NULL);
	array_of_structs = ft_calloc(1, sizeof(t_redir *) * (count + 1));
	if (!array_of_structs)
		return (NULL);
	array_of_structs[count] = NULL;
	i = 0;
	while (i < count)
	{
		array_of_structs[i] = ft_calloc(1, sizeof(t_redir));
		if (!array_of_structs[i])
		{
			while (--i >= 0)
				free(array_of_structs[i]);
			free(array_of_structs);
			return (NULL);
		}
		i++;
	}
	return (array_of_structs);
}
