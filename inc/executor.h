/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:43:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 12:58:45 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define READING_END 0
# define WRITING_END 1

typedef enum e_bool	t_bool;

void	executor(t_ast_node *ast_node);
void	execute_pipeline(t_ast_node *node);
void	execute_command(t_ast_node *node);
t_bool	execute_bi_cmd(t_ast_node *node);
pid_t	wrap_fork(void);
int		ret_exit_status(int termination_status);

#endif