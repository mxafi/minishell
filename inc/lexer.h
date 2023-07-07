/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:48:14 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/29 14:03:48by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	t_token_type		type;
	int					token_count;
	int					string_length;
	char				*token;
	struct s_token		*next;
}						t_token;

typedef struct s_lexer
{
	int					calloc_count;
	t_validation_state	state;
	t_return_value		error_code;
	int					token_amount;
	char				*readlined;
	t_token				*head;
}						t_lexer;

/*
 * delimiters and their functional properties
 */
# define DELIMITERS " \t<>|\"'"
# define WHITE_SPACES " \t"

typedef enum e_token_type
{
	UNDEFINED,
	SPACE,
	STRING,
	HEREDOC,
	APPEND_TO,
	CMD,
	ARG,
	SGL_QUOTE_STR,
	DBL_QUOTE_STR,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	OUTFILE = '>',
	INFILE = '<',
	PIPE = '|',
	SYNTAX_ERROR = 258,
}						t_token_type;

/**

	* @brief validation state enumerator used in syntax validation and tokenization of single and double quotes
 * 
 */
typedef enum e_validation_state
{
	UNDEFINED,
	IS_STR,
	IS_REDIR,
	IS_PIPE,
	SGL_QUOTE_OPENED,
	SGL_QUOTE_CAN_BE_CLOSED,
	DBL_QUOTE_OPENED,
	DBL_QUOTE_CAN_BE_CLOSED,
	SYNTAX_ERROR = 258,
}						t_validation_state;

/*
 * return values (how to handle those???)
 */
typedef enum e_return_value
{
	FAILURE = 0,
	CALLOC_FAIL,
	SUCCESS,
	SYNTAX_ERROR = 258,
}						t_return_value;

/*
 * contained in lexer.c
 */
t_return_value			string_to_token(t_lexer *token_list, char *input,
							char *delimiter);
int						tokenize_node(t_lexer *list, t_token *token, \
							char *str);
/*
 * contained in lexer_utils.c
 */
int						free_token_list(t_lexer *token_list);
int						make_new_node(t_lexer *token_to_node,
							t_token *new_token);
char					*ft_strpbrk(const char *string, const char *delimiters);
void					set_list_quote_state(t_lexer *list, t_token *token,
							t_token_type type, char *input);

/*
 * TODO: contained in DELETE_ME_AND_FCT_HEADER.c
 */
void					print_list(t_lexer *list);

/*
 * contained in lexer_validate_syntax.c
 */
t_return_value			validate_syntax(t_lexer *token_list);

/**
 * contained in lexer_validate_redirector.c 
 */
void					redirector_is_valid(t_lexer *token_list,
							t_token *token);
void					token_is_redirector(t_lexer *token_list,
							t_token *token);
t_return_value			is_token_type_redirector(t_lexer *token_list,
							t_token *token);

/**
 * contained in lexer_validate_pipe.c 
 */
void					pipes_are_valid(t_lexer *token_list, t_token *token);

/**
 * contained in lexer_validate_redirector.c
 */
t_return_value			validate_quotes(t_lexer *token_list);

/**
 * contained in lexer_quote_handling.c
 */
void					label_single_quote(t_lexer *list);
void					label_double_quote(t_lexer *list);
void					handle_quotes(t_lexer *list, t_token *token,
							t_token_type type, char *input);

#endif
