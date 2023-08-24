/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:02:31 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 08:58:49 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*skip_redirector_and_arg(t_token *token)
{
	if (token->type == HEREDOC
		|| token->type == APPEND_TO
		|| token->type == OUTFILE
		|| token->type == INFILE)
	{
		token = token->next;
		if (!token || token->type == PIPE)
			return (NULL);
		token = token->next;
		if (!token || token->type == PIPE)
			return (NULL);
	}
	return (token);
}

void	ast_parse_argv(t_ast_node *node, t_token *token)
{
	int	i;

	if (!node || !token)
		return ;
	i = 0;
	while (token && token->type != PIPE)
	{
		token = skip_redirector_and_arg(token);
		if (!token || token->type == PIPE)
			return ;
		if (token->type == CMD || token->type == ARG)
		{
			node->exec_argv[i] = token->content;
			token->content = NULL;
			i++;
		}
		if (token->type != HEREDOC
			&& token->type != APPEND_TO
			&& token->type != OUTFILE
			&& token->type != INFILE)
			token = token->next;
	}
}
