/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:48:14 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/23 12:04:19 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../inc/minishell.h"
# include "assert.h"

typedef struct s_token
{
	int				type;
	int				token_count;
	char			*token;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	int				calloc_state;
	int				calloc_count;
	int				state;
	int				token_amount;
	char			*readlined;
	t_token			*token_list;
}					t_lexer;

/*
 * delimiters and their functional properties
 */
# define DELIMITERS " \t<>|\"'"
# define WHITE_SPACES " \t"

enum e_token_type {
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	OUTFILE = '>',
	INFILE = '<',
	PIPE = '|',
	SPACE,
	STRING,
	HEREDOC,
	APPEND_TO,
	CMD
};

/*
 * return values (how to handle those???)
 */
# define FAILURE 0
# define CALLOC_FAIL 1
# define SUCCESS 2

/*
 * contained in lexer_utils.c
 */
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

#endif

