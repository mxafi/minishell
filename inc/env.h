/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:50:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/10 17:29:34 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

const char	*env_get_value_by_key(const char *key);
int			init_envp(void);
void		env_print_list(void);
void		env_unset_key(char *key);

#endif