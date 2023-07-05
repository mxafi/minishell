/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:32:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/05 23:44:08 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# define AST_VALUE_NOT_DEFINED	-1

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
	AST_COMMAND,
	AST_BI_CMD,
	AST_UNDEFINED
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

void		ast_recursive_delete(t_ast_node *node);
void		ast_recursive_token_list_delete(t_token *list);
t_token		*free_current_token_return_next(t_token *token);
t_ast_node	*ast_create_node(char **exec_argv, t_ast_node_type type);
char		**ast_create_empty_exec_argv(int length);
t_redir		**ast_create_empty_redirections(int count);
t_ast_node	*ast_parse_command(t_token *token);
void		ast_parse_argv(t_ast_node *node, t_token *token);

#endif