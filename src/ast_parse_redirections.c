/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:57:53 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/18 20:09:49 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	assign_redir_type(t_ast_node *node, t_token *token, int i)
{
	if (token->type == HEREDOC)
		node->redirections[i]->type = AST_HEREDOC;
	else if (token->type == INFILE)
		node->redirections[i]->type = AST_INFILE;
	else if (token->type == APPEND_TO)
		node->redirections[i]->type = AST_APPEND;
	else if (token->type == OUTFILE)
		node->redirections[i]->type = AST_OUTFILE;
	else
		node->redirections[i]->type = AST_UNKNOWN_REDIR;
}

static void	set_redir_arg(t_ast_node *node, t_token *token, int i)
{
	// printf("Debug: set_redir_arg: start, token.next=%s and type=%i\n", token->next->content, token->next->type);
	if (!token->next || token->next->type != ARG)
	{
		// printf("Debug: set_redir_arg: hit the guard!\n");
		// if (!token->next)
			// printf("Debug: set_redir_arg: token->next is NULL\n");
		// if (token->next)
			// printf("Debug: set_redir_arg: token->next->type is %i\n", token->next->type);
		return ;
	}
	// printf("Debug: set_redir_arg: passed the guard!\n");
	if (token->type == HEREDOC)
	{
		node->redirections[i]->argument = token->content;
		// printf("Debug: set_redir_arg: caseHEREDOC got tokentype:%i and content=%s\n", token->type, token->content);
		token->content = NULL;
	}
	else
	{
		node->redirections[i]->argument = token->next->content;
		// printf("Debug: set_redir_arg: caseNORMALREDIR got tokentype:%i and content=%s\n--next type:%i and content=%s\n", token->type, token->content, token->next->type, token->next->content);
		token->next->content = NULL;
	}
	// printf("Debug: set_redir_arg: the real end\n");
}

void	ast_parse_redirections(t_ast_node *node, t_token *token)
{
	int	i;

	if (!node || !token)
		return ;
	i = 0;
	// printf("Debug: ast_parse_redirections: starting node=%s token=%s\n", node->exec_argv[0], token->content);
	while (token && token->type != PIPE)
	{
		if (token->type == HEREDOC
			|| token->type == APPEND_TO
			|| token->type == OUTFILE
			|| token->type == INFILE)
		{
			assign_redir_type(node, token, i);
			// printf("Debug: ast_parse_redirections: got redir type=%i\n", node->redirections[i]->type);
			set_redir_arg(node, token, i);
			// printf("Debug: ast_parse_redirections: set redir arg=%s\n", node->redirections[i]->argument);
			i++;
		}
		token = token->next;
	}
}
