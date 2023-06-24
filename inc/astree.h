/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:32:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/24 13:18:03 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# define AST_TOKEN_TYPE_UNDEFINED	-1

// e_token_type from lexer.h for DEBUG
enum e_token_list{
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
} e_token_type;

typedef struct s_ast
{
	int				type;
	char			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

#endif