/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_data_helpers_alloc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:47:24 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/28 20:08:44 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// creates a node with optional data and type of AST_TOKEN_TYPE_UNDEFINED
t_ast	*ast_create_node(char **exec_argv)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->exec_argv = exec_argv;
	node->token_type = AST_TOKEN_TYPE_UNDEFINED;
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
