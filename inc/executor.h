/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:43:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 15:55:52 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define READING_END 0
# define WRITING_END 1

typedef enum e_bool	t_bool;

void	executor(t_ast_node *node);
void	execute_pipeline(t_ast_node *node);
void	execute_command(t_ast_node *node);
t_bool	execute_bi_cmd(t_ast_node *node);
pid_t	wrap_fork(pid_t	*ext_pid);
int		ret_exit_status(int termination_status);
int		open_redir_file(const char *file_path, int flags);
void	execute_command_redirections_cleanup(t_ast_node *node);
void	execute_command_redirections(t_ast_node *node);
void	execute_command_redirections_infile(t_redir *c_redir);
void	execute_command_redirections_outfile(t_redir *c_redir);
void	execute_command_redirections_append(t_redir *c_redir);
void	execute_command_redirections_heredoc(t_redir *c_redir);
t_bool	is_absolute_path(t_ast_node *node);
void	parse_path(t_ast_node *node);

#endif