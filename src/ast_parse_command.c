/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:05:54 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 18:05:58 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_ast_node_type	ast_get_command_type(t_token *token)
{
	while (token->next && token->next->type != PIPE)
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
		if (token->type == HEREDOC
			|| token->type == APPEND_TO
			|| token->type == OUTFILE
			|| token->type == INFILE)
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
	printf("Debug: ast_parse_command: calling ast_create_node\n");
	node = ast_create_node(NULL, AST_UNDEFINED);
	if (!node)
		return (NULL);
	printf("Debug: ast_parse_command: ast_create_node RETURN\n");
	printf("Debug: ast_parse_command: calling ast_get_command_type\n");
	node->type = ast_get_command_type(token);
	printf("Debug: ast_parse_command: calling ast_get_redir_count\n");
	node->redir_count = ast_get_redir_count(token);
	printf("Debug: ast_parse_command: calling ast_get_arg_count\n");
	node->argv_count = ast_get_arg_count(token) - node->redir_count + 1;
	printf("Debug: ast_parse_command: calling ast_create_empty_exec_argv\n");
	node->exec_argv = ast_create_empty_exec_argv(node->argv_count);
	printf("Debug: ast_parse_command: calling ast_create_empty_redirections\n");
	node->redirections = ast_create_empty_redirections(node->redir_count);
	printf("Debug: ast_parse_command: basic stuff parsed\n");
	if (!node->exec_argv || !node->redirections)
		ast_recursive_delete(node);
	ast_parse_argv(node, token);
	printf("Debug: ast_parse_command: argv parsed\n");
	ast_parse_redirections(node, token);
	printf("Debug: ast_parse_command: redirections parsed\n");
	return (node);
}
