/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclerc <lclerc@hive.student.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:50:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/16 11:28:13 by lclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

const char	*env_get_value_by_key(const char *key);
int			init_envp(void);
void		env_print_list(void);
void		env_unset_key(char *key);
void		env_set_value_by_key(char *key, char *value);
#endif