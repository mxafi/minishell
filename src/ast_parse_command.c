/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:05:54 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 08:08:12 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_ast_node_type	ast_get_command_type(t_token *token)
{
	while (token->next && token->next->type != PIPE)
	{
		if (token->type == CMD)
			break ;
		token = token->next;
	}
	if (token->type == CMD)
		return (AST_COMMAND);
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
		token = token->next;
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
		token = token->next;
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
	if (!node->exec_argv || (!node->redirections && node->redir_count > 0))
	{
		ast_recursive_delete(node);
		exit(1);
	}
	ast_parse_argv(node, token);
	ast_parse_redirections(node, token);
	return (node);
}
