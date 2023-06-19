/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:26:38 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/19 11:56:10 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	tokenize_node(t_lexer *list, t_token *token, char *str, int length)
{
	t_token	*last_token;

	if (!(token->token = ft_substr(str, 0, length)))
	{
		list->calloc_state = FAILURE;
		return (FAILURE);
	}
	last_token = list->token_list;
	while (last_token->next != NULL)
		last_token = last_token->next;
	last_token->next = token;
	token->next = NULL;
	list->token_amount++;
	token->token_count = list->token_amount;
	return (SUCCESS);
}


static int	string_to_token(t_lexer *token_list, char  *start, char *delimiter)
{
	t_token	*new_token;
	int		length;

	new_token = NULL;
	length = delimiter - start;
	if (delimiter == NULL)
		length = ft_strlen(start);
	if (make_new_node(token_list, new_token) == CALLOC_FAIL)
		return (CALLOC_FAIL);
	if (!tokenize_node(token_list, new_token, start, length))
		return (CALLOC_FAIL);
	new_token->type = STRING;
	start = delimiter;
	return (SUCCESS);
}

static char *delimiter_to_token(t_lexer *token_list, char *start)
{
	t_token	*new_token;
	int		length;

	new_token = NULL;
	if (make_new_node(token_list, new_token) == CALLOC_FAIL)
		return (NULL);
	if (ft_strncmp(start, "<<", 2) == 0 || ft_strncmp(start, ">>", 2) == 0)
	{
		length = 2;
		if (*start == LARGER_THAN)
 			new_token->type = APPEND_TO;
		else
			new_token->type = HEREDOC;
	}
	else 
	{
		length = 1;
		new_token->type = *start;
	}
	if (!tokenize_node(token_list, new_token, start, length))
		return (NULL);
	return (start + length);
}

static int	tokenize_readline(t_lexer *token_list)
{
	char	*start;
	char	*delimiter;

	delimiter = NULL;
	start = token_list->readlined;
	while (*start != '\0')
	{
		delimiter = ft_strpbrk(start, DELIMITERS);
		if (!delimiter)
			string_to_token(token_list, start, NULL);
		else 
		{
			if (start < delimiter)
				string_to_token(token_list, start, delimiter);
			start = delimiter_to_token(token_list, delimiter);
		}
		if (token_list->calloc_state == CALLOC_FAIL)
			break;
	}
	return (token_list->calloc_state);
}



int	lexer_main()
{
	t_lexer		token_list;
	char		*test_string = "echo -n \"toto va\" 'a' la peche > outfile | <infile wc -l > amount_of_lines";

	ft_bzero(&token_list, sizeof(t_lexer));
	if (test_string)
	{
		token_list.readlined = test_string;
		// need to trim whitespaces and get rid of those as first char
		// also, do not consider tabs as type, so trim them to single space
		//string_validation(&token_list);
		tokenize_readline(&token_list);
		print_list(&token_list);
	}
	return(0);
} 
