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
}					t_token;

typedef struct s_lexer
{
	int				calloc_count;
	int				state;
	int				error_code;
	int				token_amount;
	char			*readlined;
	t_token			*token_list;
}					t_lexer;

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


typedef enum e_token_state
{
	IS_STR,
	IS_REDIR,
	IS_PIPE,
}	t_token_state;

/*
 * return values (how to handle those???)
 */
# define FAILURE 		0
# define CALLOC_FAIL 	1
# define SUCCESS 		2

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
int					validate_syntax(t_lexer *token_list);

/**
 * contained in lexer_validate_redirector.c 
 */
void			redirector_is_valid(t_lexer *token_list, t_token *token);
void			token_is_redirector(t_lexer *token_list, t_token *token); 
int				is_token_type_redirector(t_lexer *token_list, t_token *token);

/**
 * contained in lexer_validate_pipe.c 
 */
void	pipes_are_valid(t_lexer *token_list, t_token *token);

/**
 * contained in lexer_validate_redirector.c
 */
int		validate_quotes(t_lexer *token_list);

#endif
