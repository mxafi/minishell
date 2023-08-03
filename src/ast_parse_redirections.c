/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:57:53 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/06 13:33:35 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	assign_redir_type(t_ast_node *node, t_token *token, int i)
{ //need to debug strncmp in regards to > and >> checking, false matches?
	if (ft_strncmp("<", token->data, 1) == 0)
		node->redirections[i]->type = AST_INFILE;
	else if (ft_strncmp(">", token->data, 2) == 0)
		node->redirections[i]->type = AST_OUTFILE;
	else
		node->redirections[i]->type = AST_APPEND;
}

static void	set_redir_arg(t_ast_node *node, t_token *token, int i)
{
	if (!token->next || token->next->type != ARG)
		return ;
	node->redirections[i]->argument = token->next->data;
	token->next->data = NULL;
}

void	ast_parse_redirections(t_ast_node *node, t_token *token)
{
	int	i;

	if (!node || !token)
		return ;
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == REDIR)
		{
			assign_redir_type(node, token, i);
			set_redir_arg(node, token, i);
			i++;
		}
		else
			token = token->next;
	}
}
