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

#include "libft/libft.h"

typedef struct s_token
{
	int				type;
	char			*token;
	struct	s_token *next;
}					t_token;	

typedef struct s_lexer 
{
	int				token_amount;
	char			*delimiters;
	t_token			*token_list;
}					t_lexer;


#endif
