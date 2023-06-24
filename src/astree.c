/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:33:28 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/24 23:54:46 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/** shellfish grammar
 * 
 * <command_line>			::=	<command>
 * 							|	<command_line> '|' <command>
 * 
 * <command>				::=	<simple_command>
 * 							|	<simple_command> <redirector> <redirector_pipeline>
 * 							|	<command> '<<' <argument>
 * 
 * <simple_command>			::=	<pathname>
 * 							|	<simple_command> <argument>
 * 
 * <redirector>				::=	'<' | '>' | '>>'
 * 
 * <redirector_pipeline>	::=	<filename>
 * 							|	<redirector> <redirector_pipeline>
 * 
 * <argument>				::=	ANY STRING TOKEN
 * 
 */