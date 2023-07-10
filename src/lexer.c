/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:26:38 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/10 16:49:16 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief  CANT RECALL WHY I USED THIS instead of libft, to be checked
 * 
 * @param s 
 * @param input 
 * @param len 
 * @return char* 
 */
char	*ft_test_substr(const char *s, unsigned int input, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	max_sub_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (input > s_len)
		input = s_len;
	max_sub_len = s_len - input;
	if (len <= max_sub_len)
		sub = malloc(len + 1);
	else
		sub = malloc(max_sub_len + 1);
	if (!sub)
		return (0);
	i = 0;
	while (i < max_sub_len && i < len)
	{
		sub[i] = s[i + input];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/**
 * @brief 	Add new token to the last node of the token list
 * 
 * @param list		token list being populated 
 * @param token		new node to be added to the token list 
 * @param str		input string being tokenized 
 * @param length	length of the string to be tokenized 
 * @return int		SUCCESS or FAILURE 
 */
int	tokenize_node(t_lexer *list, t_token *token, char *str, int length)
{
	t_token	*last_token;

	assert(str);
	// uses some test substr, see below and above function, check
	if (!(token->token = ft_test_substr(str, 0, length)) == FAILURE)
	{
		list->error_code = FAILURE;
		return (FAILURE);
	}
	token->next = NULL;
	token->token_count = ++list->token_amount;
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
 * @return int			SUCCESS or CALLOC_FAIL 
 */
t_return_value	string_to_token(t_lexer *token_list, char *input,
		char *delimiter)
{
	t_token	*new_token;
	int		length;

	new_token = NULL;
	if (delimiter == NULL)
		length = ft_strlen(input);
	else
		length = delimiter - input;
	if (make_new_node(token_list, new_token) == CALLOC_FAIL)
		return (token_list->error_code = CALLOC_FAIL);
	if (tokenize_node(token_list, new_token, input, length) == FAILURE)
		return (token_list->error_code = CALLOC_FAIL);
	label_token_type(token_list, new_token, STRING, input);
	input = delimiter;
	// CHECK IF RETURN VALUES ARE USED
	return (token_list->error_code = SUCCESS);}

/**
 * @brief	Tokenizes delimiters
 * @details	Heredoc and append delimiters are determined separately from the 
 * 			other delimiters. A call to set_token_type_and_quote_state is made
 * 			which will set the token type to the node, as well as an 
 * 			initialization of the token list's state needed by the quote handlers
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
	if (make_new_node(token_list, &new_token) == CALLOC_FAIL)
		return (NULL);
	if (ft_strncmp(input, "<<", 2) == 0 || ft_strncmp(input, ">>", 2) == 0)
	{
		length = 2;
		if (*input == OUTFILE)
			label_token_type(token_list, new_token, \
			APPEND_TO, input);
		else
			label_token_type(token_list, new_token, \
			HEREDOC, input);
	}
	else
	{
		length = 1;
		label_token_type(token_list, new_token, UNDEFINED, input);
	}
	if (tokenize_node(token_list, new_token, input, length) == FAILURE)
		return (NULL);
	return (input + length);
}

/**
 * @brief 	Readline string is tokenized using a self implemented version 
 * 			of strpbrk
 * @details	The strpbrk seeks the input string for delimiters: spaces, 
 * 			tabs, redirection pipes and quotes to output delimited strings in 
 * 			a tokenized linked list. The delimiter itself is then tokenized.
 * 
 * @param token_list	Token list and list information placeholder.
 * @return int			Error code is initialized to 0 and return CALLOC_FAIL
 *						if it occurs
 */
static int	tokenize_readline(t_lexer *token_list)
{
	char	*input;
	char	*delimiter;

	delimiter = NULL;
	input = token_list->readlined;
	while (*input != '\0')
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
		if (token_list->error_code == CALLOC_FAIL)
			break ;
	}
	return (token_list->error_code);
}

/**
 * @brief 	The lexer prepares the input string from the shell prompt to be 
 *				executed
 * @details	A lexer struct is initialized and serves as a placeholder for 
 *			the tokenized list.
 *			- White spaces are trimmed from both ends of the readline input
 * 			- Input is tokenized
 *			- Syntax is validated
 * 
 * @param input String obtained by user via readline
 * @return int	Return value is 0 if input was validated and execution was 
 * 				accomplished properly or an error code is returned.
 */
int	lexer(char *input)
{
	t_lexer	token_list;

	ft_bzero(&token_list, sizeof(t_lexer));
	if (input)
	{
		token_list.readlined = ft_strtrim(input, WHITE_SPACES);
		tokenize_readline(&token_list);
		print_list(&token_list);
		if ((validate_syntax(&token_list)) == FAILURE)
		{
			free_token_list(&token_list);
			return (EXIT_SYNTAX_ERROR);
		}
	}
	return (0);
}
