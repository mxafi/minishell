/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:43:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/07/30 13:11:13 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef enum e_err
{
	ERR_SUCCESS,
	ERR_MALLOC
}	t_err;

t_err	executor(t_ast_node *ast_node);
t_err	execute_pipeline(t_ast_node *node);
t_err	execute_command(t_ast_node *node);
t_err	execute_bi_cmd(t_ast_node *node);

#endif