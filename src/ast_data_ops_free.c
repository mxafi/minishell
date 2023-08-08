/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_data_ops_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:01:04 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/03 16:23:27 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	delete_argv(char **argv, int argc)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (i < argc)
	{
		if (argv[i] != NULL)
			free(argv[i]);
		i++;
	}
	assert(argv[i] == NULL);
	free(argv);
}

static void	delete_redirections(t_redir **redirections, int count)
{
	int	i;

	if (!redirections)
		return ;
	i = 0;
	while (i < count)
	{
		if (redirections[i]->argument != NULL)
			free(redirections[i]->argument);
		if (redirections[i] != NULL)
			free(redirections[i]);
		i++;
	}
	free(redirections);
}

void	ast_recursive_delete(t_ast_node *node)
{
	if (!node)
		return ;
	delete_argv(node->exec_argv, node->argv_count);
	delete_redirections(node->redirections, node->argv_count);
	ast_recursive_delete(node->left);
	ast_recursive_delete(node->right);
	free(node);
}

void	ast_recursive_token_list_delete(t_token *list)
{
	if (!list)
		return ;
	if (list->content != NULL)
		free(list->content);
	ast_recursive_token_list_delete(list->next);
	free(list);
}

t_token	*free_current_token_return_next(t_token *token)
{
	t_token	*ret;

	assert(token != NULL);
	ret = token->next;
	free(token->content);
	free(token);
	return (ret);
}
