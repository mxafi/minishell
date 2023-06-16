/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:48:14 by lclerc            #+#    #+#             */
/*   Updated: 2023/06/13 16:48:16 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEXER_H
# define LEXER_H

#include "../libft/libft.h"

typedef struct s_token
{
	int				type;
	int				token_count;
	char			*token;
	struct	s_token *next;
}					t_token;	

typedef struct s_lexer 
{
	int				calloc_state;
	int				calloc_count;
	int				token_amount;
	char			*readlined;
	t_token			*token_list;
}					t_lexer;

/*
 * delimiters and their functional properties
 */
# define	DELIMITERS		" \t<>|\"'"
typedef enum {
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
    LARGER_THAN = '>',
    SMALLER_THAN = '<',
    PIPE_SYM = '|',
	SPACE  ,
    STRING ,
	INFILE,
    OUTFILE,
    HEREDOC,
	APPEND_TO,
	CMD 
} e_token_type;


/*
 * return values (how to handle those???)
 */
# define	FAILURE			0
# define	CALLOC_FAIL		1
# define	SUCCESS			2

/*
 * contained in lexer_utils.c
 */
int		make_new_node(t_lexer *token_to_node, t_token *new_token);
char	*ft_strpbrk(const	char *string, const char *delimiters);

/*
 * TODO: contained in DELETE_ME_AND_FCT_HEADER.c
 */
void	print_list(t_lexer *list);


#endif
