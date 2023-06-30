/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_data_helpers_alloc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:47:24 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/30 15:00:45 by malaakso         ###   ########.fr       */
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

	array = ft_calloc(1, sizeof(char *) * (length + 1));
	if (!array)
		return (NULL);
	array[length] = NULL;
	return (array);
}
