/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:49:55 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/25 08:32:52 by malaakso         ###   ########.fr       */
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
 * @brief validation state enumerator used in syntax validation
 * and tokenization of single and double quotes
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
	MALLOC_FAIL,
	FORK_FAIL,
	WAIT_PID_FAIL,
	FILE_OPEN_ERROR,
	DIRECTORY_NOT_FOUND,
	INVALID_ARGUMENT,
	INVALID_EXPANSION,
	EXIT_SYNTAX_ERROR = 258,
	BREAK,
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
	char				*content;
	t_token				*next;
}						t_token;

typedef struct s_lexer
{
	t_validation_state	state;
	t_return_value		error_code;
	t_is_found			cmd_found;
	char				*readlined;
	t_token				*head;
}						t_lexer;

/*
 * contained in lexer_utils.c
 */
t_return_value			free_token_list(t_lexer *token_list, char *input);
t_return_value			make_new_node(t_lexer *token_to_node,
							t_token **new_token);
void					delete_token(t_lexer *list, t_token *token);
char					*ft_strpbrk(const char *string, const char *delimiters);

/*
 * contained in lexer_validate_syntax.c
 */
t_return_value			validate_syntax(t_lexer *token_list);

/**
 * contained in lexer_validate_redirector.c 
 */
t_return_value			token_is_redirector(t_token *token);
t_return_value			validate_redirectors(t_lexer *list);

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
void					label_token_type(t_lexer *list, t_token *token,
							t_token_type token_type, char *input);

/**
 * contained in lexer_string_concatenation.c 
 */
t_return_value			concatenate_adjacent_strings(t_lexer *list);

/**
 * Contained in lexer_expansion.c
 */
t_return_value			expand_from_env(t_lexer *list);
t_return_value			process_heredoc(t_lexer *list);
char					*extract_value_from_dollar_sign(
							const char *dollar_sign);
char					*handle_env_value(char *result_string,
							const char *env_value, t_token *current);

// Contained in lexer_heredoc_validation_utils.c
void					sig_heredoc(int sig);
char					*heredoc_get_line(void);

/**
 * Contained in lexer_expansion_extra.c
 */
const char				*handle_expansion(char *key_value,
							t_return_value *ret_val);
char					*get_result_string(char *input, char *dollar_sign,
							char *result_string, t_bool handled_pre_string);

// Contained in lexer_expansion_process_token_utils.c
t_return_value			process_token_single(t_token *current, char **input,
							char **result_string, t_bool *handled_pre_string);

#endif
