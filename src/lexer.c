/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:26:38 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/26 18:29:20 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief 
 * 
 * @param s 
 * @param start 
 * @param len 
 * @return char* 
 */
char	*ft_test_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	max_sub_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		start = s_len;
	max_sub_len = s_len - start;
	if (len <= max_sub_len)
		sub = malloc(len + 1);
	else
		sub = malloc(max_sub_len + 1);
	if (!sub)
		return (0);
	i = 0;
	while (i < max_sub_len && i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	//printf("Substring created in ft_substr: %s\n", sub);
	return (sub);
}

/**
 * @brief 
 * 
 * @param list 
 * @param token 
 * @param str 
 * @param length 
 * @return int 
 */
static int	tokenize_node(t_lexer *list, t_token *token, char *str, int length)
{
	t_token	*last_token;

	assert(str);
	ft_printf("tokenize_node()");
	ft_printf("token->token before substr is [] length [%d], str[%s]\n", length,
			str);
	ft_printf("strlen(str) [%d]\n", ft_strlen(str));
	if (!(token->token = ft_test_substr(str, 0, length)))
	{
		list->error_code = FAILURE;
		return (FAILURE);
	}
	ft_printf("token->token after substr is [%s] \
			length [%d], str[%s]\n",
				token->token,
				length,
				str);
	token->next = NULL;
	token->token_count = ++list->token_amount;
	if (list->token_list == NULL)
		list->token_list = token;
	else
	{
		last_token = list->token_list;
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = token;
	}
	return (SUCCESS);
}

static int	string_to_token(t_lexer *token_list, char *start, char *delimiter)
{
	t_token	*new_token;
	int		length;

	//ft_printf("string_to_token()\n");
	new_token = NULL;
	if (delimiter == NULL)
	{
		length = ft_strlen(start);
	}
	else
	{
		length = delimiter - start;
		//	ft_printf("length [%d] = delimiter [%s] - start[%s]\n", length,
		//			delimiter , start);
	}
	if (make_new_node(token_list, &new_token) == CALLOC_FAIL)
		return (CALLOC_FAIL);
	//ft_printf("length [%d] start [%s]\n", length, start);
	if (!tokenize_node(token_list, new_token, start, length))
		return (CALLOC_FAIL);
	new_token->type = STRING;
	start = delimiter;
	return (SUCCESS);
}

static char	*delimiter_to_token(t_lexer *token_list, char *start)
{
	t_token	*new_token;
	int		length;

	new_token = NULL;
	if (make_new_node(token_list, &new_token) == CALLOC_FAIL)
		return (NULL);
	if (ft_strncmp(start, "<<", 2) == 0 || ft_strncmp(start, ">>", 2) == 0)
	{
		length = 2;
		if (*start == OUTFILE)
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
		//ft_printf("tokenize_readline -> ft_strpbrk gives delimeter: %s\n",
			//	delimiter);
		if (!delimiter)
		{
			string_to_token(token_list, start, NULL);
			break ;
		}
		else
		{
			if (start < delimiter)
				string_to_token(token_list, start, delimiter);
			start = delimiter_to_token(token_list, delimiter);
		}
		if (token_list->error_code == CALLOC_FAIL)
			break ;
	}
	return (token_list->error_code);
}

int	lexer(char *input)
{
	t_lexer	token_list;

	ft_bzero(&token_list, sizeof(t_lexer));
	if (input)
	{
		token_list.readlined = ft_strtrim(input, WHITE_SPACES);
		if ((validate_syntax(&token_list)) == SYNTAX_ERROR);
		{
			free_token_list(token_list);
			return (SYNTAX_ERROR);
		}
		tokenize_readline(&token_list);
		print_list(&token_list);
	}
	return (0);
}