/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:32:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/24 21:53:30 by malaakso         ###   ########.fr       */
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

t_ast	*ast_create_node(char *data);
void	ast_set_data(t_ast *node, char *data);
void	ast_replace_data(t_ast *node, char *data);
void	ast_set_type(t_ast *node, int type);
void	ast_attach(t_ast *root, t_ast *left, t_ast *right);
void	ast_recursive_delete(t_ast *node);

#endif