/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malaakso <malaakso@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:50:39 by malaakso          #+#    #+#             */
/*   Updated: 2023/08/24 09:35:05 by malaakso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

const char	*env_get_value_by_key(const char *key);
int			init_envp(void);
void		env_print_list(void);
void		env_unset_key(char *key);
void		env_set_value_by_key(char *key, char *value);
char		*env_split_value(char *env_var);
char		*env_utils_join_three_str(char *s1, char *s2, char *s3);
size_t		env_utils_ret_key_idx(char *key);
void		envp_init_vars(size_t i);

#endif