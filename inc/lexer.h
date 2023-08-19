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

/*
 * delimiters and their functional properties
 */
# define DELIMITERS " \t<>|\"'"
# define WHITE_SPACES " \t"

typedef enum e_token_type
{
	UNDEFINED_TOKEN,
	MY_SPACE,
	STRING,
	HEREDOC,
	APPEND_TO,
	CMD,
	BI_CMD,
	ARG,
	SGL_QUOTE_STR,
	DBL_QUOTE_STR,
	QUOTE_NEED_NULL_STR,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	OUTFILE = '>',
	INFILE = '<',
	PIPE = '|',
}						t_token_type;

/**
 * @brief validation state enumerator used in syntax validation and tokenization of single and double quotes
 * 
 */
typedef enum e_validation_state
{
	UNDEFINED,
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
	SUCCESS,
	FAILURE,
	CALLOC_FAIL,
	FORK_FAIL,
	WAIT_PID_FAIL,
	FILE_OPEN_ERROR,
	DIRECTORY_NOT_FOUND,
	INVALID_ARGUMENT,
	EXIT_SYNTAX_ERROR = 258,
}						t_return_value;

typedef enum e_is_found
{
	NOT_YET,
	FOUND,
}						t_is_found;

typedef struct s_token	t_token;

typedef struct s_token
{
	t_token_type		type;
	int					token_count; //not used should be removed
	char				*content;
	t_token				*next;
}						t_token;

typedef struct s_lexer
{
	int					calloc_count;
	t_validation_state	state;
	t_return_value		error_code;
	t_is_found			cmd_found;
	int					token_amount; //not used should be removed
	char				*readlined;
	t_token				*head;
}						t_lexer;


/*
 * contained in lexer.c
 */
t_return_value			string_to_token(t_lexer *token_list, char *input,
							char *delimiter);
int						tokenize_node(t_lexer *list, t_token *token, char *str,
							int length);
/*
 * contained in lexer_utils.c
 */
t_return_value			free_token_list(t_lexer *token_list, char *input);
t_return_value			make_new_node(t_lexer *token_to_node, t_token **new_token);
void					delete_token(t_lexer *list, t_token *token);
char					*ft_strpbrk(const char *string, const char *delimiters);

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
t_return_value	token_is_redirector(t_token *token);
t_return_value	validate_redirectors(t_lexer *list);


/**
 * contained in lexer_validate_pipes.c 
 */
t_return_value			validate_pipes(t_lexer *token_list);

/**
 * contained in lexer_validate_quote.c
 */
t_return_value			validate_quotes(t_lexer *token_list);

/**
 * contained in lexer_label_token_type.c
 */
void	label_token_type(t_lexer *list, t_token *token, \
		t_token_type token_type, char *input);

/**
 * contained in lexer_string_concatenation.c 
 */
void					concatenate_adjacent_strings(t_lexer *list);

/**
 * Contained in lexer_expansion.c
 */
t_return_value	expand_from_env(t_lexer *list);

t_return_value			process_heredoc(t_lexer *list);

#endif
