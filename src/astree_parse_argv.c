/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_parse_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:02:31 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/05 23:37:03 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*skip_redirector_and_arg(t_token *token)
{
	if (token->type == REDIR) //assumes there is an argument after the redirector
	{
		token = token->next;
		if (!token || token->type == PIPE)
			return ;
		token = token->next;
		if (!token || token->type == PIPE)
			return ;
	}
	return (token);
}

void	ast_parse_argv(t_ast_node *node, t_token *token)
{
	int	i;

	i = 1;
	while (token && token->type != PIPE)
	{
		token = skip_redirector_and_arg(token);
		if (!token || token->type == PIPE)
			return ;
		if (token->type == CMD || token->type == BI_CMD)
		{
			node->exec_argv[0] = token->data;
			token->data = NULL;
		}
		if (token->type == ARG)
		{
			node->exec_argv[i] = token->data;
			token->data = NULL;
			i++;
		}
		token = token->next;
	}
}
