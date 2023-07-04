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

# include "assert.h"

typedef struct s_token
{
	t_token_type	type;
	int				token_count;
	char			*token;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	int					calloc_count;
	t_validation_state	state;
	t_return_value		error_code;
	int					token_amount;
	char				*readlined;
	t_token				*head;
}	t_lexer;

/*
 * delimiters and their functional properties
 */
# define DELIMITERS " \t<>|\"'"
# define WHITE_SPACES " \t"

typedef enum e_token_type
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	OUTFILE = '>',
	INFILE = '<',
	PIPE = '|',
	SPACE,
	STRING,
	HEREDOC,
	APPEND_TO,
	CMD,
	ARG,
	SGL_QUOTE_STR,
	DBL_QUOTE_STR,
	SYNTAX_ERROR = 258,
}	t_token_type;

typedef enum e_validation_state
{
	IS_STR,
	IS_REDIR,
	IS_PIPE,
	SYNTAX_ERROR = 258,
}	t_validation_state;

/*
 * return values (how to handle those???)
 */
typedef enum e_return_value
{
	FAILURE = 0,
	CALLOC_FAIL ,
	SUCCESS,
	SYNTAX_ERROR = 258,
}	t_return_value;

/*
 * contained in lexer_utils.c
 */
int					free_token_list(t_lexer *token_list);
int					make_new_node(t_lexer *token_to_node, t_token **new_token);
char				*ft_strpbrk(const char *string, const char *delimiters);

/*
 * TODO: contained in DELETE_ME_AND_FCT_HEADER.c
 */
void				print_list(t_lexer *list);

/*
 * contained in lexer_validate_syntax.c
 */
t_return_value		validate_syntax(t_lexer *token_list);

/**
 * contained in lexer_validate_redirector.c 
 */
void				redirector_is_valid(t_lexer *token_list, t_token *token);
void				token_is_redirector(t_lexer *token_list, t_token *token);
t_return_value		is_token_type_redirector(t_lexer *token_list, \
		t_token *token);

/**
 * contained in lexer_validate_pipe.c 
 */
void				pipes_are_valid(t_lexer *token_list, t_token *token);

/**
 * contained in lexer_validate_redirector.c
 */
t_return_value		validate_quotes(t_lexer *token_list);

#endif
