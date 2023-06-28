/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:32:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/28 19:54:07 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# define AST_TOKEN_TYPE_UNDEFINED	-1

// e_token_type from lexer.h for DEBUG
enum e_token_list{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	OUTFILE,
	INFILE,
	PIPE,
	SPACE,
	STRING,
	HEREDOC,
	APPEND_TO,
	CMD,
	BI_CMD,
	REDIR,
	ARG
} e_token_type;

// expected input for ast_builder from lexer, here for debug purposes
typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}					t_token;

typedef struct s_ast
{
	int				token_type;
	char			**exec_argv;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;



#endif