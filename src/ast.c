/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 18:01:38 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Creates an Abstract Syntax Tree (AST) with top-down recursion.
 * 
 * @param token Head of the linked list of tokens.
 * @return t_ast_node* Head of the AST, a command or a pipe node.
 */
t_ast_node	*ast_builder(t_token *token)
{
	t_ast_node	*node;
	t_ast_node	*tmp;

	if (!token)
		return (NULL);
	printf("Debug: ast_builder: building from token with content::%s::\n", token->content);
	tmp = ast_parse_command(token); //parse everything upto a pipe
	printf("Debug: ast_builder: parsecommand returned\n");
	while (token->next != NULL && token->type != PIPE)
		token = token->next;
	if (token->type != PIPE)
		return (tmp);
	node = ast_create_node(NULL, AST_PIPE);
	printf("Debug: ast_builder: createnodePIPEreturned returned\n");
	node->left = tmp;
	node->right = ast_builder(token->next);
	return (node);
}
