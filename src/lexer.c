/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:45:42 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 18:45:44 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief 	Add new token to the last node of the token list
 * 
 * @param list		token list being populated 
 * @param token		new node to be added to the token list 
 * @param str		input string being tokenized 
 * @param length	length of the string to be tokenized 
 * @return int		SUCCESS or FAILURE 
 */
static t_return_value	tokenize_node(t_lexer *list, t_token *token, char *str,
		int length)
{
	t_token	*last_token;

	token->content = ft_substr(str, 0, length);
	if (token->content == NULL)
	{
		list->error_code = FAILURE;
		return (FAILURE);
	}
	token->next = NULL;
	if (list->head == NULL)
		list->head = token;
	else
	{
		last_token = list->head;
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = token;
	}
	return (SUCCESS);
}

/**
 * @brief Tokenize current string up to null terminator or delimiter
 * 
 * @param token_list	Token and list information placeholder
 * @param input			string to be tokenized 
 * @param delimiter		used to determine string length to be tokenized 
 * @return int			SUCCESS or MALLOC_FAIL 
 */
static t_return_value	string_to_token(t_lexer *token_list, char *input,
		char *delimiter)
{
	t_token	*new_token;
	size_t	length;

	new_token = NULL;
	if (delimiter == NULL)
		length = ft_strlen(input);
	else
		length = delimiter - input;
	if (make_new_node(token_list, &new_token) == MALLOC_FAIL)
		return (token_list->error_code = MALLOC_FAIL);
	if (tokenize_node(token_list, new_token, input, length) == FAILURE)
		return (token_list->error_code = MALLOC_FAIL);
	label_token_type(token_list, new_token, STRING, input);
	input = delimiter;
	token_list->error_code = SUCCESS;
	return (token_list->error_code);
}

/**
 * @brief	Tokenizes delimiters
 * @details	Heredoc and append delimiters are determined separately from the 
 * 			other delimiters. A call to set_token_type_and_quote_state is made
 * 			which will set the token type to the node, as well as an 
 * 			initialization of the token list's state needed by the quote handler
 *			in add_null_string_token_if_empty_quote function.
 *
 * @param token_list	Information and token list placeholder.
 * @param input			Input string from readline being tokenized
 * @return char*		Pointer to string after delimiter 
 */
static char	*delimiter_to_token(t_lexer *token_list, char *input)
{
	t_token	*new_token;
	int		length;

	new_token = NULL;
	if (make_new_node(token_list, &new_token) == MALLOC_FAIL)
		return (NULL);
	if (ft_strncmp(input, "<<", 2) == 0 || ft_strncmp(input, ">>", 2) == 0)
	{
		length = 2;
		if (*input == OUTFILE)
			label_token_type(token_list, new_token, APPEND_TO, input);
		else
			label_token_type(token_list, new_token, HEREDOC, input);
	}
	else
	{
		length = 1;
		label_token_type(token_list, new_token, UNDEFINED_TOKEN, input);
	}
	if (tokenize_node(token_list, new_token, input, length) == FAILURE)
		return (NULL);
	return (input + length);
}

/**
 * @brief 	Readline string is tokenized using a self implemented version 
 * of strpbrk
 * @details	The strpbrk seeks the input string for delimiters: spaces, 
 * 			tabs, redirection, pipes and quotes to output delimited strings in 
 * 			a tokenized linked list. The delimiter itself is then tokenized.
 * 
 * @param token_list	Token list and list information placeholder.
 * @return int			Error code is initialized to 0 and return MALLOC_FAIL
 *						if it occurs
 */
static t_return_value	tokenize_readline(t_lexer *token_list)
{
	char	*input;
	char	*delimiter;

	delimiter = NULL;
	input = token_list->readlined;
	while (input && *input != '\0')
	{
		delimiter = ft_strpbrk(input, DELIMITERS);
		if (!delimiter)
		{
			string_to_token(token_list, input, NULL);
			break ;
		}
		else
		{
			if (input < delimiter)
				string_to_token(token_list, input, delimiter);
			input = delimiter_to_token(token_list, delimiter);
		}
		if (token_list->error_code == MALLOC_FAIL)
			break ;
	}
	return (token_list->error_code);
}

/**
 * @brief 	The lexer prepares the input string from the shell prompt to be 
 *			executed
 * @details	A lexer struct is initialized and serves as a placeholder for 
 *			the tokenized list.
 *			- White spaces are trimmed from both ends of the readline input
 * 			- Input is tokenized
 *			- Syntax is validated
 * 
 * @param input String obtained by user via readline
 * @return t_return_value	Return value is 0 if input was validated and 
 * execution was accomplished properly or an error code is returned.
 */
t_return_value	lexer(char *input)
{
	t_lexer		token_list;
	t_ast_node	*ast_root;

	ft_bzero(&token_list, sizeof(t_lexer));
	if (*input != '\0')
	{
		token_list.readlined = ft_strtrim(input, WHITE_SPACES);
		if (token_list.readlined[0] == '\0')
		{
			free_token_list(&token_list, input);
			return (0);
		}
		tokenize_readline(&token_list);
		if ((validate_syntax(&token_list)) != SUCCESS)
		{
			g_minishell->exit_status = token_list.error_code;
			free_token_list(&token_list, input);
			return (g_minishell->exit_status);
		}
		ast_root = ast_builder(token_list.head);
		executor(ast_root);
		ast_recursive_delete(ast_root);
	}
	free_token_list(&token_list, input);
	return (SUCCESS);
}
