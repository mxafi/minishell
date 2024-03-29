/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:32:41 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 08:09:08 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;

typedef enum e_ast_node_type
{
	AST_PIPE,
	AST_COMMAND,
	AST_UNDEFINED
}	t_ast_node_type;

typedef enum e_ast_redir_type
{
	AST_INFILE,
	AST_OUTFILE,
	AST_APPEND,
	AST_HEREDOC,
	AST_UNKNOWN_REDIR,
	AST_NULL_REDIR
}	t_ast_redir_type;

typedef struct s_redir
{
	t_ast_redir_type	type;
	int					file_descriptor;
	char				*argument;
}						t_redir;

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	t_ast_node_type	type;
	int				argv_count;
	int				redir_count;
	char			**exec_argv;
	char			*exec_file;
	t_redir			**redirections;
	t_ast_node		*left;
	t_ast_node		*right;
}					t_ast_node;

void		ast_recursive_delete(t_ast_node *node);
void		ast_recursive_token_list_delete(t_token *list);
t_token		*free_current_token_return_next(t_token *token);
t_ast_node	*ast_create_node(char **exec_argv, t_ast_node_type type);
char		**ast_create_empty_exec_argv(int length);
t_redir		**ast_create_empty_redirections(int count);
t_ast_node	*ast_parse_command(t_token *token);
void		ast_parse_argv(t_ast_node *node, t_token *token);
void		ast_parse_redirections(t_ast_node *node, t_token *token);
t_ast_node	*ast_builder(t_token *token);

#endif
