/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/27 18:05:00 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/** shellfish grammar lclerc will implement it in lexing and tagging
 * 
 * <command_line>			OK::=	<command>
 * 							OK|		<command_line> '|' <command>
 * 
 * <command>				OK::=	<simple_command>
 * 							|		<simple_command> <redirector> <redirector_pipeline>
 * 
 * <simple_command>			OK::=	<pathname>
 * 							OK|		<simple_command> <argument>
 * 
 * <redirector>				OK::=	'<' | '>' | '<<' | '>>'
 * 
 * <redirector_pipeline>	OK::=	<filename>
 * 							|		<filename> <redirector> <redirector_pipeline>
 * 
 * <argument>				OK::=	ANY STRING TOKEN
 * 
 */
