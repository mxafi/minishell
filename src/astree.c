/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/05 23:01:22 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_ast_node_type	ast_get_command_type(t_token *token)
{
	while (token->next && token->next != PIPE)
	{
		if (token->type == CMD || token->type == BI_CMD)
			break ;
		token = token->next;
	}
	if (token->type == CMD)
		return (AST_COMMAND);
	if (token->type == BI_CMD)
		return (AST_BI_CMD);
	return (AST_UNDEFINED);
}

static int	ast_get_arg_count(t_token *token)
{
	int	all_arg_c;

	all_arg_c = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == ARG)
			all_arg_c++;
	}
	return (all_arg_c);
}

static int	ast_get_redir_count(t_token *token)
{
	int	redir_c;

	redir_c = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR)
			redir_c++;
	}
	return (redir_c);
}

/**
 * @brief Parses a command with it's arguments, redirectors,
 * and their arguments.
 * 
 * @param token Token that marks the start of a command,
 * the end is a pipe token or the end of the linked list.
 * @return t_ast_node* Command node for the AST.
 */
t_ast_node	*ast_parse_command(t_token *token)
{
	t_ast_node	*node;

	if (!token)
		return (NULL);
	node = ast_create_node(NULL, AST_UNDEFINED);
	if (!node)
		return (NULL);
	node->type = ast_get_command_type(token);
	node->redir_count = ast_get_redir_count(token);
	node->argv_count = ast_get_arg_count(token) - node->redir_count + 1;
	node->exec_argv = ast_create_empty_exec_argv(node->argv_count);
	node->redirections = ast_create_empty_redirections(node->redir_count);
	if (!node->exec_argv || !node->redirections)
		ast_recursive_delete(node);
	ast_parse_argv(node, token);//TODO
	ast_parse_redirections(node, token);//TODO
	return (node);
}

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
	tmp = ast_parse_command(token); //parse everything upto a pipe
	while (token->next != NULL && token->type != PIPE)
		token = token->next;
	if (token->type != PIPE)
		return (tmp);
	node = ast_create_node(NULL, AST_PIPE);
	node->left = tmp;
	node->right = ast_builder(token->next);
	return (node);
}
