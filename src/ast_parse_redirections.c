/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:57:53 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/23 16:29:23 by lclerc           ###   ########.fr       */
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
	if (!token->next || token->next->type != ARG)
		return ;
	if (token->type == HEREDOC)
	{
		node->redirections[i]->argument = token->content;
		token->content = NULL;
	}
	else
	{
		node->redirections[i]->argument = token->next->content;
		token->next->content = NULL;
	}
}

void	ast_parse_redirections(t_ast_node *node, t_token *token)
{
	int	i;

	if (!node || !token)
		return ;
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == HEREDOC
			|| token->type == APPEND_TO
			|| token->type == OUTFILE
			|| token->type == INFILE)
		{
			assign_redir_type(node, token, i);
			set_redir_arg(node, token, i);
			i++;
		}
		token = token->next;
	}
}
