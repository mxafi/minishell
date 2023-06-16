/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:32:46 by malaakso          #+#    #+#             */
/*   Updated: 2023/06/16 12:40:14 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

char	*get_input(void);
void	ignore_signals(void);
void	restore_signal_defaults(void);
void	toggle_echoctl(void);

#endif