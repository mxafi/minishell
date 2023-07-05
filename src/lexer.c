/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:26:38 by lclerc            #+#    #+#             */
/*   Updated: 2023/07/05 18:41:25 by lclerc           ###   ########.fr       */
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
 // @brief  CANT RECALL WHY I USED THIS instead of libft, to be checked
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
	//printf("Substring created in ft_substr: %s\n", sub);
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
static int	tokenize_node(t_lexer *list, t_token *token, char *str, int length)
{
	t_token	*last_token;

	assert(str);
	ft_printf("tokenize_node()");
	ft_printf("token->token before substr is [] length [%d], str[%s]\n", length,
			str);
	ft_printf("strlen(str) [%d]\n", ft_strlen(str));
	// uses some test substr, see below, check!
	if ((token->token = ft_test_substr(str, 0, length)) == FAILURE)
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
t_return_value	string_to_token(t_lexer *token_list, char *input, char *delimiter)
{
	t_token	*new_token;
	int		length;

	//ft_printf("string_to_token()\n");
	new_token = NULL;
	if (delimiter == NULL)
		length = ft_strlen(input);
	else
		length = delimiter - input;
		//	ft_printf("length [%d] = delimiter [%s] - input[%s]\n", length,
		//			delimiter , input);
	if (make_new_node(token_list, &new_token) == CALLOC_FAIL)
		return (token_list->error_code = CALLOC_FAIL);
	//ft_printf("length [%d] input [%s]\n", length, input);
	if (!tokenize_node(token_list, new_token, input, length))
	 	// below is CALLOC_FAIL if memalloc fails, but it is malloc... should we care about that?
		return (token_list->error_code = CALLOC_FAIL);
	new_token->type = STRING;
	input = delimiter;
	// CHECK IF RETURN VALUES ARE USED
	return (token_list->error_code = SUCCESS);
}

/**
 * @brief	Tokenizes delimeters
 * @details	The current char in input string is used as token type except for << and >>
 * 			which require manual depiction due to the two characters identification.
 * 
 * @param token_list  	Information and token list placeholder.
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
			new_token->type = APPEND_TO;
		else
			new_token->type = HEREDOC;
	}
	else
	{
		length = 1;
		//Will need to make proper function to handle the input type here
		new_token->type = *input;
	}
	if (!tokenize_node(token_list, new_token, input, length))
		return (NULL);
	return (input + length);
}

/**
 * @brief 	Readline string is tokenized using a self implemented version of strpbrk
 * @details	The strpbrk seeks the input string for delimiters: spaces, tabs, redirection
 * 			pipes and quotes to output delimited strings a tokenized linked list. The 
 * 			delimiter itself is then tokenized.
 * 			A call to check whether quotes are empty or not is made, with the aim 
 * 			to tokenize a null string in between if it is the case.
 * 
 * @param token_list	Token list and list information placeholder.
 * @return int			Error code is initialized to 0 and return CALLOC_FAIL if it occurs
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
		//ft_printf("tokenize_readline -> ft_strpbrk gives delimeter: %s\n",
			//	delimiter);
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
			add_null_string_token_if_empty_quote(token_list);
		}
		if (token_list->error_code == CALLOC_FAIL)
			break ;
	}
	return (token_list->error_code);
}

/**
 * @brief 	The lexer prepares the input string from the shell prompt to be executed
 * @details	A lexer struct is initialized and serves as a placeholder for the tokenized
 *			list.
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
		if ((validate_syntax(&token_list)) == SYNTAX_ERROR)
		{
			free_token_list(token_list);
			return (SYNTAX_ERROR);
		}
	}
	return (0);
}
