/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:32:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/29 12:53:21 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# define AST_TOKEN_TYPE_UNDEFINED	-1

// e_token_type from lexer.h for DEBUG
typedef enum e_token_list{
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
}	t_token_type;

// expected input for ast_builder from lexer, here for debug purposes
typedef struct s_token
{
	t_token_type	type;
	char			*data;
	struct s_token	*next;
}					t_token;

typedef enum e_ast_node_type
{
	AST_PIPE,
	AST_COMMAND
}	t_ast_node_type;

typedef enum e_ast_redir_type
{
	AST_INFILE,
	AST_OUTFILE,
	AST_APPEND
}	t_ast_redir_type;

typedef struct s_redir
{
	t_ast_redir_type	type;
	int					file_descriptor;
	char				*argument;
}						t_redir;

typedef struct s_ast_node
{
	t_ast_node_type	type;
	int				argv_count;
	int				redir_count;
	char			**exec_argv;
	t_redir			**redirections;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast_node;

#endif